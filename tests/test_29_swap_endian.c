#include "../checker/test_framework.h"

int main() {
    test_init("29_swap_endian");

    printf("\n🧪 测试练习题: 29_swap_endian\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/29_swap_endian/29_swap_endian.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/29_swap_endian.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现32位无符号整数的大端序和小端序转换函数\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("29_swap_endian", "29_swap_endian", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    const char* expected_output = "0x78563412 -> 0x12345678";
        
    ASSERT_TRUE(string_contains(output, expected_output), "程序应该输出: 0x78563412 -> 0x12345678");
    
    if (string_contains(output, expected_output)) {
        printf("✅ 程序正确实现了大端序和小端序的转换\n");
        printf("💡 知识点: 本题测试对大端序和小端序的理解以及位操作能力\n");
        
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示: 请确保正确实现了大端序和小端序的转换\n");
        printf("💡 期望输出应包含: %s\n", expected_output);
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}