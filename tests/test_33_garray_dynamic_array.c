#include "../checker/test_framework.h"

int main() {
    test_init("33_garray_dynamic_array");

    printf("\n🧪 测试练习题：33_garray_dynamic_array\n");

    // 检查是否包含未完成标记
    int has_marker =
        file_contains_marker("../exercises/33_garray_dynamic_array/33_garray_dynamic_array.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/33_garray_dynamic_array/33_garray_dynamic_array.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[2048];
    int result = compile_and_run("33_garray_dynamic_array", "33_garray_dynamic_array", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 断言关键输出
    ASSERT_TRUE(string_contains(output, "len=17"), "应输出 len=17");
    ASSERT_TRUE(string_contains(output, "capacity=32"), "应输出 capacity=32");
    ASSERT_TRUE(string_contains(output, "arr[0]=1"), "应输出首元素 arr[0]=1");
    ASSERT_TRUE(string_contains(output, "arr[16]=17"), "应输出第 17 个元素 arr[16]=17");

    if (string_contains(output, "len=17") && string_contains(output, "capacity=32") &&
        string_contains(output, "arr[0]=1") && string_contains(output, "arr[16]=17")) {
        printf("✅ 程序正确实现了 GArray 扩容与数据追加\n");
        printf("💡 知识点：内存管理（realloc）、泛型编程（void*）、扩容策略设计、元素字节拷贝与偏移计算\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：按题意打印 len/capacity 以及关键元素值，便于自动化判定\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
