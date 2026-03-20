#include "../checker/test_framework.h"

int main() {
    test_init("25_counter_letter");

    printf("\n🧪 测试练习题：25_counter_letter\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/25_counter_letter/25_counter_letter.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示：请编辑 exercises/25_counter_letter.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示：实现字母计数功能\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[2048];
    int result = compile_and_run("25_counter_letter", "25_counter_letter", output, sizeof(output), 0);

    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 🎯 期望程序输出包含特定的字母计数
    const char *expected_counts[] = {"a:59", "e:70", "l:32", "n:51", "o:55"};

    // 检查每个期望的计数是否出现在输出中
    for (int i = 0; i < 5; i++) {
        char str[100];
        snprintf(str, sizeof(str), "程序应该输出：%s", expected_counts[i]);
        ASSERT_TRUE(string_contains(output, expected_counts[i]), str);
    }

    // 检查输出格式是否正确（按字母顺序）
    if (string_contains(output, "a:59") && string_contains(output, "e:70") && string_contains(output, "l:32") &&
        string_contains(output, "n:51") && string_contains(output, "o:55")) {
        printf("✅ 程序正确输出了字母计数结果\n");
        printf("📊 检测到的计数:\n");
        printf("  a:59, e:70, l:32, n:51, o:55\n");
        printf("💡 知识点：本题测试字母频率统计和格式化输出\n");

        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：请确保程序按字母顺序输出所有字母的计数\n");
        printf("💡 期望包含：a:59, e:70, l:32, n:51, o:55\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
