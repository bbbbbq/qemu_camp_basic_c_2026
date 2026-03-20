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
    
    // 构建编译命令 - 使用C11标准
    snprintf(compile_cmd, sizeof(compile_cmd), 
             "cd ../exercises/15_url_parser && gcc -Wall -Wextra -std=c11 -o %s %s.c 2>&1", 
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
    
    // 运行程序
    snprintf(run_cmd, sizeof(run_cmd), 
             "cd ../exercises/15_url_parser && ./%s 2>&1", executable);
    
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
    test_init("15_url_parser");

    printf("\n🧪 测试练习题: URL参数解析器\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/15_url_parser/15_url_parser.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示: 请完成URL参数解析器\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[2048];
    printf("正在编译程序...\n");
    int result = compile_and_run_with_input("../exercises/15_url_parser/15_url_parser.c", "15_url_parser", 
                                          output, sizeof(output), "");

    // 使用ASSERT宏来确保编译运行成功会被统计为测试用例
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("❌ 程序运行失败，返回码: %d\n", result);
        printf("错误信息: %s\n", output);
        test_finish();
        return 1;
    }

    printf("✅ 程序编译和运行成功\n");
    printf("程序输出:\n%s\n", output);

    // 检查URL参数解析结果 - 使用ASSERT宏确保被统计
    int name_found = string_contains(output, "key = name, value = John");
    int age_found = string_contains(output, "key = age, value = 30");
    int city_found = string_contains(output, "key = city, value = New+York");
    
    ASSERT_TRUE(name_found, "应该解析出name参数");
    ASSERT_TRUE(age_found, "应该解析出age参数");
    ASSERT_TRUE(city_found, "应该解析出city参数");

    if (name_found && age_found && city_found) {
        printf("\n🎉 所有URL解析测试通过！\n");
        printf("💡 知识点: URL解析，字符串处理，strtok函数使用，键值对提取\n");
        g_current_exercise.completed = 1;
    } else {
        printf("\n❌ 部分测试失败，请检查URL解析逻辑\n");
        if (!name_found) printf("   缺少: key = name, value = John\n");
        if (!age_found) printf("   缺少: key = age, value = 30\n");
        if (!city_found) printf("   缺少: key = city, value = New+York\n");
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}