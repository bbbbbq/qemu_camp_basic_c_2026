#include "../checker/test_framework.h"
#include <stdlib.h>
#include <string.h>

// 支持自动输入的函数
int compile_and_run_with_input(const char* source_file, const char* executable, 
                              char* output, size_t output_size, const char* input) {
    char compile_cmd[512];
    char run_cmd[512];
    FILE* fp;
    
    // 清空输出缓冲区
    memset(output, 0, output_size);
    
    // 构建编译命令 - 修正路径
    snprintf(compile_cmd, sizeof(compile_cmd), 
             "cd ../exercises/14_calculator && gcc -Wall -Wextra -std=c11 -o %s %s.c 2>&1", 
             executable, executable);
    
    // 编译程序
    fp = popen(compile_cmd, "r");
    if (fp == NULL) {
        strncpy(output, "无法执行编译命令", output_size - 1);
        return -1;
    }
    
    char compile_output[4096] = {0};
    size_t bytes_read = fread(compile_output, 1, sizeof(compile_output) - 1, fp);
    int compile_status = pclose(fp);
    
    // 检查编译是否成功
    if (compile_status != 0) {
        snprintf(output, output_size, "编译失败:\n%s", compile_output);
        return -1;
    }
    
    // 使用echo自动输入数据并运行程序 - 修正路径
    snprintf(run_cmd, sizeof(run_cmd), 
             "cd ../exercises/14_calculator && echo '%s' | ./%s 2>&1", input, executable);
    
    fp = popen(run_cmd, "r");
    if (fp == NULL) {
        strncpy(output, "无法执行程序", output_size - 1);
        return -1;
    }
    
    // 读取程序输出
    bytes_read = fread(output, 1, output_size - 1, fp);
    output[bytes_read] = '\0';
    
    int run_status = pclose(fp);
    return run_status;
}

int main() {
    test_init("14_calculator");

    printf("\n🧪 测试练习题: 14_calculator\n");

    // 修正文件路径
    int has_marker = file_contains_marker("../exercises/14_calculator/14_calculator.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示: 请完成函数指针计算器\n");
        test_finish();
        return 1;
    }

    // 测试加法 - 使用自动输入
    char add_output[1024];
    int result = compile_and_run_with_input("../exercises/14_calculator/14_calculator.c", "14_calculator", 
                                          add_output, sizeof(add_output), "10 5 +");
    
    if (result == 0 && string_contains(add_output, "15")) {
        printf("✅ 加法测试通过 (10 + 5 = 15)\n");
        g_current_exercise.completed = 1;
    } else {
        printf("❌ 加法测试失败\n");
        printf("程序输出: %s\n", add_output);
        g_test_stats.failed_tests += 1;
    }

    // 测试减法
    char sub_output[1024];
    result = compile_and_run_with_input("../exercises/14_calculator/14_calculator.c", "14_calculator", 
                                      sub_output, sizeof(sub_output), "10 5 -");
    
    if (result == 0 && string_contains(sub_output, "5")) {
        printf("✅ 减法测试通过 (10 - 5 = 5)\n");
    } else {
        printf("❌ 减法测试失败\n");
        printf("程序输出: %s\n", sub_output);
        g_test_stats.failed_tests += 1;
    }

    // 测试乘法
    char mul_output[1024];
    result = compile_and_run_with_input("../exercises/14_calculator/14_calculator.c", "14_calculator", 
                                      mul_output, sizeof(mul_output), "10 5 *");
    
    if (result == 0 && string_contains(mul_output, "50")) {
        printf("✅ 乘法测试通过 (10 * 5 = 50)\n");
    } else {
        printf("❌ 乘法测试失败\n");
        printf("程序输出: %s\n", mul_output);
        g_test_stats.failed_tests += 1;
    }

    // 测试除法
    char div_output[1024];
    result = compile_and_run_with_input("../exercises/14_calculator/14_calculator.c", "14_calculator", 
                                      div_output, sizeof(div_output), "10 5 /");
    
    if (result == 0 && string_contains(div_output, "2")) {
        printf("✅ 除法测试通过 (10 / 5 = 2)\n");
    } else {
        printf("❌ 除法测试失败\n");
        printf("程序输出: %s\n", div_output);
        g_test_stats.failed_tests += 1;
    }

    // 测试除零错误处理
    char div_error_output[1024];
    result = compile_and_run_with_input("../exercises/14_calculator/14_calculator.c", "14_calculator", 
                                      div_error_output, sizeof(div_error_output), "10 0 /");
    
    if (result == 0 && (string_contains(div_error_output, "错误") || 
                        string_contains(div_error_output, "error") ||
                        string_contains(div_error_output, "零"))) {
        printf("✅ 除零错误处理测试通过\n");
    } else {
        printf("❌ 除零错误处理测试失败\n");
        printf("程序输出: %s\n", div_error_output);
        g_test_stats.failed_tests += 1;
    }

    // 测试负数运算
    char neg_output[1024];
    result = compile_and_run_with_input("../exercises/14_calculator/14_calculator.c", "14_calculator", 
                                      neg_output, sizeof(neg_output), "-5 -3 +");
    
    if (result == 0 && string_contains(neg_output, "-8")) {
        printf("✅ 负数加法测试通过 (-5 + -3 = -8)\n");
    } else {
        printf("❌ 负数加法测试失败\n");
        printf("程序输出: %s\n", neg_output);
        g_test_stats.failed_tests += 1;
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}