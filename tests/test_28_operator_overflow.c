#include "../checker/test_framework.h"

int main() {
    test_init("28_operator_overflow");

    printf("\n🧪 测试练习题：28_operator_overflow\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/28_operator_overflow/28_operator_overflow.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示：请编辑 exercises/28_operator_overflow.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示：实现检测整数运算溢出的函数\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("28_operator_overflow", "28_operator_overflow", output, sizeof(output), 0);

    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    const char* expected_output[] = {
        "(UINT_MAX + 1)Add: Overflow", "(1, 0)Add: Not Overflow", "(0, 1)Sub: Overflow",  "(2, 1)Sub: Not Overflow",
        "(UINT_MAX, 2)Mul: Overflow",  "(1, 2)Mul: Not Overflow", "(10, 0)Div: Overflow", "(2, 1)Div: Not Overflow"};

    for (int i = 0; i < 8; i++) {
        char str[100];
        snprintf(str, sizeof(str), "程序应该输出：%s", expected_output[i]);
        ASSERT_TRUE(string_contains(output, expected_output[i]), str);
    }

    if (string_contains(output, "(UINT_MAX + 1)Add: Overflow") && string_contains(output, "(1, 0)Add: Not Overflow") &&
        string_contains(output, "(0, 1)Sub: Overflow") && string_contains(output, "(2, 1)Sub: Not Overflow") &&
        string_contains(output, "(UINT_MAX, 2)Mul: Overflow") && string_contains(output, "(1, 2)Mul: Not Overflow") &&
        string_contains(output, "(10, 0)Div: Overflow") && string_contains(output, "(2, 1)Div: Not Overflow")) {
        printf("✅ 程序正确检测了各种运算的溢出情况\n");
        printf("💡 知识点：本题测试对整数运算溢出的检测能力\n");

        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：请确保正确实现了所有四种运算的溢出检测\n");
        printf("💡 期望输出应包含:\n");
        for (int i = 0; i < 8; i++) {
            printf("%s\n", expected_output[i]);
        }
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
