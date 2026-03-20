#include "../checker/test_framework.h"

int main() {
    test_init("40_bloom_filter_bitmap");

    printf("\n🧪 测试练习题：40_bloom_filter_bitmap\n");

    // 检查未完成标记
    int has_marker =
        file_contains_marker("../exercises/40_bloom_filter_bitmap/40_bloom_filter_bitmap.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/40_bloom_filter_bitmap/40_bloom_filter_bitmap.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行
    char output[2048];
    int result = compile_and_run("40_bloom_filter_bitmap", "40_bloom_filter_bitmap", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 必须包含 apple 存在为 1
    ASSERT_TRUE(string_contains(output, "apple exists: 1"), "输出应包含 apple exists: 1");

    // grape 未插入，允许误判；仅校验打印格式
    ASSERT_TRUE(string_contains(output, "grape exists: "), "输出应包含 grape exists: <0 或 1>");

    printf("✅ 程序正确实现了基于位图的 Bloom 过滤器\n");
    printf("💡 知识点：哈希函数设计、位图操作、Bloom 过滤器的误判特性（无假阴性但可能假阳性）\n");
    strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    g_current_exercise.completed = 1;

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
