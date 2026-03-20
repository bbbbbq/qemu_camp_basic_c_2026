#include "../checker/test_framework.h"

int main() {
    test_init("36_lru_cache");

    printf("\n🧪 测试练习题：36_lru_cache\n");

    // 检查未完成标记
    int has_marker = file_contains_marker("../exercises/36_lru_cache/36_lru_cache.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/36_lru_cache/36_lru_cache.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行
    char output[2048];
    int result = compile_and_run("36_lru_cache", "36_lru_cache", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 校验包含 {2,4,5}，且不包含 {1,3}
    ASSERT_TRUE(string_contains(output, "2:2"), "输出应包含 2:2");
    ASSERT_TRUE(string_contains(output, "4:4"), "输出应包含 4:4");
    ASSERT_TRUE(string_contains(output, "5:5"), "输出应包含 5:5");
    ASSERT_FALSE(string_contains(output, "1:1"), "输出不应包含 1:1（应被淘汰）");
    ASSERT_FALSE(string_contains(output, "3:3"), "输出不应包含 3:3（应被淘汰）");

    printf("✅ 程序正确实现了 LRU 缓存淘汰策略\n");
    printf("💡 知识点：哈希表与双向链表的协同、LRU 淘汰策略（最近最少使用）\n");
    strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    g_current_exercise.completed = 1;

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
