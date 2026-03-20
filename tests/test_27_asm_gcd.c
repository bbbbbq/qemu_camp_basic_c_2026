#include "../checker/test_framework.h"

int main() {
    test_init("27_asm_gcd");

    printf("\n🧪 测试练习题: 27_asm_gcd\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/27_asm_gcd/27_asm_gcd.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/27_asm_gcd.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 使用内联汇编实现 GCD 函数\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("27_asm_gcd", "27_asm_gcd", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

        
    // 检查第一个测试用例 gcd(12, 8)
    ASSERT_TRUE(string_contains(output, "4"), "gcd(12, 8) 应该等于 4");
    ASSERT_TRUE(string_contains(output, "1"), "gcd(7, 5) 应该等于 1");
    
    if (string_contains(output, "4") && string_contains(output, "1")) {
        printf("✅ 程序正确计算了最大公约数\n");
        printf("📊 检测到的结果:\n");
        printf("  gcd(12, 8) = 4\ngcd(7, 5) = 1\n");
        printf("💡 知识点: 本题测试内联汇编实现数学算法\n");
        
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示: 请确保 gcd_asm 函数正确实现了最大公约数算法\n");
        printf("💡 期望输出:\n4\n1\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}