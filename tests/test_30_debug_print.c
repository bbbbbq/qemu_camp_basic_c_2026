#include "../checker/test_framework.h"

int main() {
    test_init("30_debug_print");

    printf("\n🧪 测试练习题: 30_debug_print\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/30_debug_print/30_debug_print.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/30_debug_print.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现调试宏 DEBUG_PRINT，根据 DEBUG_LEVEL 输出不同详细程度的调试信息\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("30_debug_print", "30_debug_print", output, sizeof(output), 1);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    const char* expected_output = "DEBUG: func=test, line=48, x=42";
        
    ASSERT_TRUE(string_contains(output, expected_output), "程序应该输出: DEBUG: func=test, line=48, x=42");
    
    if (string_contains(output, expected_output)) {
        printf("✅ 程序正确实现了 DEBUG_PRINT 宏\n");
        printf("💡 知识点: 本题测试对预处理器宏、调试输出和条件编译的理解\n");
        
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示: 请确保正确实现了 DEBUG_PRINT 宏\n");
        printf("💡 期望输出应包含: %s\n", expected_output);
        printf("💡 具体要求:\n");
        printf("   - 当 DEBUG_LEVEL=2 时，调用 DEBUG_PRINT(\"x=%%d\", x) 应输出 DEBUG: func=test, line=48, x=42\n");
        printf("   - 使用 __func__ 和 __LINE__ 预定义宏\n");
        printf("   - 根据 DEBUG_LEVEL 值控制输出详细程度\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}