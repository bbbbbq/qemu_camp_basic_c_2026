#include "../checker/test_framework.h"
#include <stdlib.h>
#include <string.h>

int main() {
    test_init("13_universal_sorter");

    printf("\n🧪 测试练习题: 13_universal_sorter\n");

    int has_marker = file_contains_marker("../exercises/13_universal_sorter.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示: 请完成通用排序函数\n");
        test_finish();
        return 1;
    }

    // 测试整数排序
    char int_input[] = "1\n3\n5 2 8\n";
    char int_output[1024];
    int result = compile_and_run("13_universal_sorter", "13_universal_sorter", 
                                          int_output, sizeof(int_output), 0);
    
    if (result == 0 && string_contains(int_output, "2 5 8")) {
        printf("✅ 整数排序测试通过\n");
    } else {
        printf("❌ 整数排序测试失败\n");
        g_test_stats.failed_tests += 1;
    }

    // 测试浮点数排序
    char float_input[] = "2\n4\n3.1 1.5 4.2 2.0\n";
    char float_output[1024];
    result = compile_and_run("13_universal_sorter", "13_universal_sorter", 
                                      float_output, sizeof(float_output), 0);
    
    if (result == 0 && (string_contains(float_output, "1.50") || string_contains(float_output, "1.5"))) {
        printf("✅ 浮点数排序测试通过\n");
    } else {
        printf("❌ 浮点数排序测试失败\n");
        g_test_stats.failed_tests += 1;
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}