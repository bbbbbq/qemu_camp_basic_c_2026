/**
 * checker.c
 *
 * C 语言练习题检查器 - 合并基础阶段与专业阶段，共 40 题
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_EXERCISES 40
#define MAX_NAME_LEN 64
#define SCORE_PER_EXERCISE 5
#define TOTAL_SCORE 200
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

typedef struct {
    char name[MAX_NAME_LEN];
    int completed;
} exercise_t;

typedef struct {
    exercise_t exercises[MAX_EXERCISES];
    int count;
    int total_passed;
    int total_failed;
} checker_t;

static void generate_overall_json_report(checker_t *checker);

static int file_contains_marker(const char *filename, const char *marker) {
    FILE *file = fopen(filename, "r");
    char line[256];

    if (file == NULL) {
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, marker) != NULL) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

static void get_primary_source_path(const char *exercise_name, char *filepath, size_t filepath_size) {
    if (strcmp(exercise_name, "20_mybash") == 0) {
        snprintf(filepath, filepath_size, "exercises/20_mybash/src/mybash/main.c");
        return;
    }

    snprintf(filepath, filepath_size, "exercises/%s/%s.c", exercise_name, exercise_name);
}

static int run_test(const char *exercise_name) {
    char test_path[256];
    char compile_cmd[512];
    char run_cmd[256];
    char cleanup_cmd[256];
    int compile_result;
    int test_result;

    snprintf(test_path, sizeof(test_path), "tests/test_%s.c", exercise_name);
    if (access(test_path, F_OK) != 0) {
        printf(COLOR_YELLOW "⚠️  没有找到测试文件: %s" COLOR_RESET "\n", test_path);
        return -1;
    }

    snprintf(
        compile_cmd,
        sizeof(compile_cmd),
        "cd tests && gcc -Wall -Wextra -std=c11 -o test_%s test_%s.c ../checker/test_framework.c -I../checker "
        "2>/dev/null",
        exercise_name,
        exercise_name);
    compile_result = system(compile_cmd);
    if (compile_result != 0) {
        printf(COLOR_RED "❌ 测试编译失败: %s" COLOR_RESET "\n", exercise_name);
        return -1;
    }

    snprintf(run_cmd, sizeof(run_cmd), "cd tests && ./test_%s", exercise_name);
    test_result = system(run_cmd);

    snprintf(cleanup_cmd, sizeof(cleanup_cmd), "cd tests && rm -f test_%s", exercise_name);
    system(cleanup_cmd);

    return test_result == 0 ? 0 : 1;
}

static int check_exercise(const char *exercise_name) {
    char filepath[256];
    int test_result;

    get_primary_source_path(exercise_name, filepath, sizeof(filepath));

    printf("\n" COLOR_BLUE "🔍 检查练习题: %s" COLOR_RESET "\n", exercise_name);
    printf("================================================\n");

    if (access(filepath, F_OK) != 0) {
        printf(COLOR_RED "❌ 文件不存在: %s" COLOR_RESET "\n", filepath);
        return 0;
    }

    if (file_contains_marker(filepath, "I AM NOT DONE")) {
        printf(COLOR_YELLOW "⏳ 练习题尚未完成，请移除 'I AM NOT DONE' 标记" COLOR_RESET "\n");
        return 0;
    }

    test_result = run_test(exercise_name);
    if (test_result == 0) {
        printf(COLOR_GREEN "✅ 练习题通过所有测试！" COLOR_RESET "\n");
        return 1;
    }
    if (test_result == 1) {
        printf(COLOR_RED "❌ 练习题测试失败" COLOR_RESET "\n");
        return -1;
    }

    printf(COLOR_YELLOW "⚠️  无法运行测试" COLOR_RESET "\n");
    return 0;
}

static void list_exercises(checker_t *checker) {
    int i;

    printf(COLOR_BLUE "📚 可用的练习题:" COLOR_RESET "\n");
    printf("================================================\n");

    for (i = 0; i < checker->count; i++) {
        char filepath[256];

        get_primary_source_path(checker->exercises[i].name, filepath, sizeof(filepath));
        if (file_contains_marker(filepath, "I AM NOT DONE")) {
            printf("  %s - " COLOR_RED "❌ 未完成" COLOR_RESET "\n", checker->exercises[i].name);
        } else {
            printf("  %s - " COLOR_GREEN "✅ 已完成" COLOR_RESET "\n", checker->exercises[i].name);
        }
    }
}

static void check_all_exercises(checker_t *checker) {
    int i;
    int total_score;

    printf(COLOR_BLUE "🧪 C 语言练习题检查器" COLOR_RESET "\n");
    printf("================================================\n");

    checker->total_passed = 0;
    checker->total_failed = 0;

    for (i = 0; i < checker->count; i++) {
        int result = check_exercise(checker->exercises[i].name);
        if (result == 1) {
            checker->total_passed++;
            checker->exercises[i].completed = 1;
        } else if (result == -1) {
            checker->total_failed++;
            checker->exercises[i].completed = -1;
        } else {
            checker->exercises[i].completed = 0;
        }
    }

    total_score = checker->total_passed * SCORE_PER_EXERCISE;
    printf("\n" COLOR_BLUE "📊 总结:" COLOR_RESET "\n");
    printf("总共 %d 道练习题\n", checker->count);
    printf(COLOR_GREEN "通过 %d 道" COLOR_RESET "\n", checker->total_passed);
    printf(COLOR_RED "失败 %d 道" COLOR_RESET "\n", checker->total_failed);
    printf(COLOR_BLUE "🏆 总分数: %d/%d" COLOR_RESET "\n", total_score, TOTAL_SCORE);

    generate_overall_json_report(checker);

    if (checker->total_failed == 0) {
        printf("\n" COLOR_GREEN "🎉 恭喜！所有练习题都通过了！" COLOR_RESET "\n");
    } else {
        printf("\n" COLOR_YELLOW "还有 %d 道练习题需要完成" COLOR_RESET "\n", checker->count - checker->total_passed)
;    }
}

static void show_hint(const char *exercise_name) {
    char source_path[256];
    char test_path[256];
    char readme_path[256];

    get_primary_source_path(exercise_name, source_path, sizeof(source_path));
    snprintf(test_path, sizeof(test_path), "tests/test_%s.c", exercise_name);
    snprintf(readme_path, sizeof(readme_path), "exercises/%s/readme.md", exercise_name);

    printf(COLOR_BLUE "💡 练习题提示: %s" COLOR_RESET "\n", exercise_name);
    printf("================================================\n");
    printf("- 源码入口: %s\n", source_path);
    printf("- 测试文件: %s\n", test_path);
    if (access(readme_path, F_OK) == 0) {
        printf("- 题目说明: %s\n", readme_path);
    }
    printf("- 先移除源码里的 'I AM NOT DONE' 标记\n");
    printf("- 再阅读测试文件，按断言要求补齐实现\n");
    if (strcmp(exercise_name, "20_mybash") == 0) {
        printf("- 20_mybash 包含多个子模块，需一起通过 Makefile 构建和测试\n");
    }
}

static void generate_overall_json_report(checker_t *checker) {
    FILE *file;
    time_t now;
    struct tm *tm_info;
    char timestamp[64];
    int total_score;
    int i;
    double success_rate;

    file = fopen("test_results_summary.json", "w");
    if (file == NULL) {
        printf(COLOR_RED "警告: 无法创建总体 JSON 报告文件" COLOR_RESET "\n");
        return;
    }

    now = time(NULL);
    tm_info = gmtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", tm_info);

    total_score = checker->total_passed * SCORE_PER_EXERCISE;
    success_rate = checker->count > 0 ? ((double)checker->total_passed / checker->count) * 100.0 : 0.0;

    fprintf(file, "{\n");
    fprintf(file, "  \"test_summary\": {\n");
    fprintf(file, "    \"timestamp\": \"%s\",\n", timestamp);
    fprintf(file, "    \"total_exercises\": %d,\n", checker->count);
    fprintf(file, "    \"passed_exercises\": %d,\n", checker->total_passed);
    fprintf(file, "    \"failed_exercises\": %d,\n", checker->total_failed);
    fprintf(file, "    \"not_completed_exercises\": %d,\n", checker->count - checker->total_passed - checker->total_failed);
    fprintf(file, "    \"total_score\": %d,\n", total_score);
    fprintf(file, "    \"max_score\": %d,\n", TOTAL_SCORE);
    fprintf(file, "    \"success_rate\": %.1f,\n", success_rate);
    fprintf(file, "    \"score_per_exercise\": %d\n", SCORE_PER_EXERCISE);
    fprintf(file, "  },\n");
    fprintf(file, "  \"exercises\": [\n");

    for (i = 0; i < checker->count; i++) {
        exercise_t *exercise = &checker->exercises[i];
        fprintf(file, "    {\n");
        fprintf(file, "      \"name\": \"%s\",\n", exercise->name);
        if (exercise->completed == 1) {
            fprintf(file, "      \"status\": \"PASSED\",\n");
            fprintf(file, "      \"score\": %d\n", SCORE_PER_EXERCISE);
        } else if (exercise->completed == -1) {
            fprintf(file, "      \"status\": \"FAILED\",\n");
            fprintf(file, "      \"score\": 0\n");
        } else {
            fprintf(file, "      \"status\": \"NOT_COMPLETED\",\n");
            fprintf(file, "      \"score\": 0\n");
        }
        fprintf(file, "    }");
        if (i < checker->count - 1) {
            fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fprintf(file, "  ]\n");
    fprintf(file, "}\n");
    fclose(file);
    printf(COLOR_GREEN "📝 总体 JSON 报告已生成: test_results_summary.json" COLOR_RESET "\n");
}

static const char *find_exercise_by_number(checker_t *checker, const char *number) {
    int i;

    for (i = 0; i < checker->count; i++) {
        if (strcmp(checker->exercises[i].name, number) == 0) {
            return checker->exercises[i].name;
        }
    }

    for (i = 0; i < checker->count; i++) {
        char prefix[3];
        strncpy(prefix, checker->exercises[i].name, 2);
        prefix[2] = '\0';
        if (strcmp(prefix, number) == 0) {
            return checker->exercises[i].name;
        }
    }

    return NULL;
}

static void init_exercises(checker_t *checker) {
    const char *exercise_names[] = {
        "01_insert_sort",
        "02_merge_sort",
        "03_quick_sort",
        "04_linear_search",
        "05_binary_search",
        "06_stack_maze",
        "07_queue_maze",
        "08_circular_queue",
        "09_word_counter",
        "10_my_strcpy",
        "11_command_interpreter",
        "12_student_management",
        "13_universal_sorter",
        "14_calculator",
        "15_url_parser",
        "16_mysed",
        "17_myfile",
        "18_mywc",
        "19_mytrans",
        "20_mybash",
        "21_singly_linked_list_josephus",
        "22_doubly_circular_queue",
        "23_circular_linked_list_josephus",
        "24_prev_binary_tree",
        "25_counter_letter",
        "26_hash_counter",
        "27_asm_gcd",
        "28_operator_overflow",
        "29_swap_endian",
        "30_debug_print",
        "31_event_handler",
        "32_container_of_macro",
        "33_garray_dynamic_array",
        "34_protocol_header_parser",
        "35_elf_info_parser",
        "36_lru_cache",
        "37_bitmap_operations",
        "38_thread_safe_ring_buffer",
        "39_strtok_r_thread_safe",
        "40_bloom_filter_bitmap",
    };
    int i;

    checker->count = (int)(sizeof(exercise_names) / sizeof(exercise_names[0]));
    checker->total_passed = 0;
    checker->total_failed = 0;

    for (i = 0; i < checker->count; i++) {
        strncpy(checker->exercises[i].name, exercise_names[i], MAX_NAME_LEN - 1);
        checker->exercises[i].name[MAX_NAME_LEN - 1] = '\0';
        checker->exercises[i].completed = 0;
    }
}

static void show_help(void) {
    printf(COLOR_BLUE "🛠️  C 语言练习题检查器使用说明" COLOR_RESET "\n");
    printf("================================================\n");
    printf("用法:\n");
    printf("  ./c-checker list\n");
    printf("  ./c-checker check [exercise_name|number]\n");
    printf("  ./c-checker check-all\n");
    printf("  ./c-checker hint [exercise_name|number]\n");
    printf("  ./c-checker help\n");
    printf("\n例如:\n");
    printf("  ./c-checker check 01\n");
    printf("  ./c-checker check 21_singly_linked_list_josephus\n");
    printf("  ./c-checker hint 40\n");
}

int main(int argc, char *argv[]) {
    checker_t checker;
    const char *command;

    init_exercises(&checker);

    if (argc < 2) {
        show_help();
        return 1;
    }

    command = argv[1];
    if (strcmp(command, "list") == 0) {
        list_exercises(&checker);
        return 0;
    }
    if (strcmp(command, "check-all") == 0) {
        check_all_exercises(&checker);
        return 0;
    }
    if (strcmp(command, "check") == 0 || strcmp(command, "hint") == 0) {
        const char *exercise_name;

        if (argc < 3) {
            printf(COLOR_RED "错误: 请指定练习题名称或编号" COLOR_RESET "\n");
            return 1;
        }

        exercise_name = find_exercise_by_number(&checker, argv[2]);
        if (exercise_name == NULL) {
            printf(COLOR_RED "错误: 找不到练习题 '%s'" COLOR_RESET "\n", argv[2]);
            return 1;
        }

        if (strcmp(command, "check") == 0) {
            int result = check_exercise(exercise_name);
            return result == 1 ? 0 : 1;
        }

        show_hint(exercise_name);
        return 0;
    }
    if (strcmp(command, "help") == 0) {
        show_help();
        return 0;
    }

    printf(COLOR_RED "错误: 未知命令 '%s'" COLOR_RESET "\n", command);
    show_help();
    return 1;
}
