#include "../checker/test_framework.h"
#include <stdlib.h>
#include <string.h>

int main() {
    test_init("11_command_interpreter");

    printf("\n🧪 测试练习题: 11_command_interpreter\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/11_command_interpreter.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/11_command_interpreter.c 文件，完成shell_parse函数\n");
        printf("💡 提示: 使用状态机方式解析命令行参数，正确处理空格和字符串结束符\n");
        test_finish();
        return 1;
    }

    // 测试用例
    char test_cases[][100] = {
        "hello world test 123\n",
        "echo hello world\n",
        "add 5 3\n",
        "help\n",
        "   multiple   spaces   test   \n",
        "a b c d e f g h i j k l m n o p q r s t u v w x y z"
    };

    char expected_outputs[][200] = {
        "Parameter 1: hello, Length: 5",
        "Echo: hello world",
        "5 + 3 = 8",
        "This is help command",
        "Parameter 1: multiple, Length: 8"
    };

    int passed_tests = 0;
    const int total_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < total_tests; i++) {
        char output[1024];
        int result = compile_and_run("11_command_interpreter", "11_command_interpreter", 
                                              output, sizeof(output), 0);
        
        if (result == 0) {
            // 检查基本输出格式
            if (string_contains(output, "Parameter") || 
                string_contains(output, "Echo:") ||
                string_contains(output, "+") ||
                string_contains(output, "help command") ||
                string_contains(output, "Total 10 parameters")
            ) {
                printf("✅ 测试用例 %d 通过\n", i + 1);
                passed_tests++;
            } else {
                printf("❌ 测试用例 %d 失败 - 输出格式不正确\n", i + 1);
                printf("输入: %s", test_cases[i]);
                printf("输出: %s\n", output);
                g_test_stats.failed_tests += 1;
            }
        } else {
            printf("❌ 测试用例 %d 失败 - 程序运行错误\n", i + 1);
            printf("输入: %s", test_cases[i]);
            printf("错误输出: %s\n", output);
            g_test_stats.failed_tests += 1;
        }
    }

    if (passed_tests >= total_tests) {
        printf("✅ 命令行解析功能正确实现\n");
        printf("💡 知识点: 状态机解析，字符串处理，命令行参数分割\n");
        g_current_exercise.completed = 1;
    } else {
        printf("📊 通过测试: %d/%d\n", passed_tests, total_tests + 1);
        printf("💡 提示: 确保shell_parse函数能正确分割参数并处理边界情况\n");
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}