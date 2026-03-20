#include "../checker/test_framework.h"

int main() {
    test_init("10_my_strcpy");
    
    printf("\n🧪 测试练习题: 10_my_strcpy\n");
    
    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/10_my_strcpy.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/10_my_strcpy.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 使用字符指针实现字符串拷贝，逐个字符复制直到遇到结束符\n");
        test_finish();
        return 1;
    }
    
    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("10_my_strcpy", "10_my_strcpy", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }
    
    // 检查输出是否包含预期的字符串内容
    ASSERT_TRUE(string_contains(output, "Hello, World!"), 
                "输出应该包含源字符串的起始部分");
    ASSERT_TRUE(string_contains(output, "my_strcpy function"), 
                "输出应该包含源字符串的中间部分");
    ASSERT_TRUE(string_contains(output, "拷贝后的字符串"), 
                "输出应该包含中文提示信息");
    
    // 验证完整的字符串拷贝
    char expected[] = "Hello, World! This is a test string for my_strcpy function.\n";
    ASSERT_TRUE(string_contains(output, expected), 
                "输出应该完整包含拷贝后的字符串");
    
    if (string_contains(output, expected)) {
        printf("✅ 字符串拷贝功能正确实现\n");
        printf("💡 知识点: 使用指针逐字符拷贝是C语言中字符串操作的经典方法\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序输出:\n%s\n", output);
        printf("💡 提示: 确保程序能正确实现字符串拷贝功能，包括正确添加结束符\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }
    
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}