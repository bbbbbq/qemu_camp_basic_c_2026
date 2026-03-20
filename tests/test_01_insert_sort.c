/**
 * test_01_insert_sort.c
 * 
 * 测试第一个练习题：插入排序
 * 输入：从文件读入 n 个学生的信息（包含姓名和成绩），n 不超过 50
 * 输出：使用插入排序算法按成绩从高到低排序后，在屏幕上依次显示排序后的学生姓名和成绩，每个学生信息占一行
 */

#include "../checker/test_framework.h"

int main() {
    test_init("01_insert_sort");
    
    printf("\n🧪 测试练习题: 01_insert_sort\n");
    
    // 检查文件是否还包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/01_insert_sort.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/01_insert_sort.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 插入排序算法：从第二个元素开始，将当前元素插入到已排序部分的正确位置\n");
        printf("💡 提示: 需要从文件读取学生信息，按成绩从高到低排序\n");
        printf("💡 提示: 输出格式：每行显示一个学生的姓名和成绩\n");
        test_finish();
        return 1;
    }
    
    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("01_insert_sort", "01_insert_sort", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }
    
    // 检查是否包含排序结果标题
    ASSERT_TRUE(string_contains(output, "按成绩从高到低排序后的学生信息") || 
                string_contains(output, "排序后的学生信息"), 
                "输出应该包含排序结果标题");
    
    // 解析输出中的成绩，验证排序是否正确
    int scores[50];
    char names[50][20];
    int score_count = 0;
    char *line = strtok(output, "\n");
    int found_title = 0;
    
    while (line != NULL) {
        if (strlen(line) > 0) {
            // 跳过标题行
            if (string_contains(line, "按成绩从高到低排序后的学生信息") || 
                string_contains(line, "排序后的学生信息")) {
                found_title = 1;
            }
            // 解析学生信息行（格式：姓名 成绩）
            else if (found_title && score_count < 50) {
                char name[20];
                int score;
                if (sscanf(line, "%s %d", name, &score) == 2) {
                    strcpy(names[score_count], name);
                    scores[score_count] = score;
                    score_count++;
                }
            }
        }
        line = strtok(NULL, "\n");
    }
    
    ASSERT_TRUE(score_count > 0, "应该至少有一个学生的成绩信息");
    
    // 验证排序是否正确（从高到低）
    int sorted_correctly = 1;
    for (int i = 1; i < score_count; i++) {
        if (scores[i-1] < scores[i]) {
            sorted_correctly = 0;
            break;
        }
    }
    
    ASSERT_TRUE(sorted_correctly, "成绩应该按从高到低排序");
    
    // 检查特定的测试数据（Alice 85, Bob 92, Carol 78, David 95, Eve 88）
    if (score_count >= 5) {
        // 检查是否包含预期的学生姓名
        int found_alice = 0, found_bob = 0, found_carol = 0, found_david = 0, found_eve = 0;
        for (int i = 0; i < score_count; i++) {
            if (strcmp(names[i], "Alice") == 0) found_alice = 1;
            if (strcmp(names[i], "Bob") == 0) found_bob = 1;
            if (strcmp(names[i], "Carol") == 0) found_carol = 1;
            if (strcmp(names[i], "David") == 0) found_david = 1;
            if (strcmp(names[i], "Eve") == 0) found_eve = 1;
        }
        
        if (found_alice && found_bob && found_carol && found_david && found_eve) {
            printf("📝 程序正确处理了测试数据：Alice 85, Bob 92, Carol 78, David 95, Eve 88\n");
        }
    }
    
    if (sorted_correctly && score_count > 0) {
        printf("📝 程序正确执行了插入排序算法\n");
        printf("💡 知识点: 插入排序时间复杂度O(n²)，空间复杂度O(1)，稳定排序\n");
        printf("💡 测试数据: Alice 85, Bob 92, Carol 78, David 95, Eve 88\n");
        printf("💡 期望结果: David 95, Bob 92, Eve 88, Alice 85, Carol 78\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序输出:\n%s\n", output);
        printf("💡 提示: 确保程序能正确读取文件中的学生信息并排序\n");
        printf("💡 测试数据: Alice 85, Bob 92, Carol 78, David 95, Eve 88\n");
        printf("💡 期望结果: David 95, Bob 92, Eve 88, Alice 85, Carol 78\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }
    
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}