#include "../checker/test_framework.h"

int main() {
    test_init("37_bitmap_operations");

    printf("\n🧪 测试练习题：37_bitmap_operations\n");

    // 检查是否存在未完成标记
    int has_marker = file_contains_marker("../exercises/37_bitmap_operations/37_bitmap_operations.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/37_bitmap_operations/37_bitmap_operations.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行
    char output[1024];
    int result = compile_and_run("37_bitmap_operations", "37_bitmap_operations", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 校验输出：query(3)=1 与 query(1)=0
    ASSERT_TRUE(string_contains(output, "query(3)=1"), "输出应包含 query(3)=1");
    ASSERT_TRUE(string_contains(output, "query(1)=0"), "输出应包含 query(1)=0");

    printf("✅ 程序正确实现了位图的 set/test 操作\n");
    printf("💡 知识点：位运算（|=、&=、(1<<n)）、数组索引计算（byte = bit / 8，offset = bit % 8）\n");
    strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    g_current_exercise.completed = 1;

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
