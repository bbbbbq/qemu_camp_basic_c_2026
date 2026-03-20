/**
 * test_04_linear_search.c
 * 
 * 测试第四个练习题：线性查找
 * 输入：先从文件读入 n 个学生的信息（包含姓名和成绩），n 不超过 50，再输入要查找的学生姓名
 * 输出：如果找到该学生，在屏幕上显示 "姓名：XXX，成绩：XXX"；如果未找到，显示 "未找到该学生"
 */

#include "../checker/test_framework.h"

int main() {
    test_init("04_linear_search");
    
    printf("\n🧪 测试练习题: 04_linear_search\n");
    
    // 检查文件是否还包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/04_linear_search.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/04_linear_search.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 线性查找算法：从数组的第一个元素开始，逐个比较直到找到目标或遍历完整个数组\n");
        printf("💡 提示: 需要从文件读取学生信息，然后输入要查找的学生姓名\n");
        printf("💡 提示: 输出格式：找到显示'姓名：XXX，成绩：XXX'，未找到显示'未找到该学生'\n");
        test_finish();
        return 1;
    }
    
    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("04_linear_search", "04_linear_search", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }
    
    // 检查是否包含开始提示
    ASSERT_TRUE(string_contains(output, "linear search") || string_contains(output, "线性查找") || 
                string_contains(output, "search") || string_contains(output, "查找"), 
                "输出应该包含查找算法相关信息");
    
    // 检查是否包含学生信息读取提示
    ASSERT_TRUE(string_contains(output, "student") || string_contains(output, "学生") || 
                string_contains(output, "file") || string_contains(output, "文件"), 
                "输出应该包含学生信息或文件读取相关信息");
    
    // 检查是否包含输入提示
    ASSERT_TRUE(string_contains(output, "input") || string_contains(output, "输入") || 
                string_contains(output, "name") || string_contains(output, "姓名"), 
                "输出应该包含输入学生姓名的提示");
    
    // 检查输出格式（找到或未找到的情况）
    int found_format = string_contains(output, "姓名：") || string_contains(output, "name:") || 
                      string_contains(output, "成绩：") || string_contains(output, "score:");
    int not_found_format = string_contains(output, "未找到") || string_contains(output, "not found") || 
                          string_contains(output, "找不到");
    
    ASSERT_TRUE(found_format || not_found_format, 
                "输出应该包含找到学生的格式（姓名：XXX，成绩：XXX）或未找到的提示");
    
    if (found_format || not_found_format) {
        printf("📝 程序正确执行了线性查找算法\n");
        printf("💡 知识点: 线性查找时间复杂度O(n)，适用于无序数组\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序输出:\n%s\n", output);
        printf("💡 提示: 确保程序能正确读取文件中的学生信息并实现查找功能\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }
    
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
