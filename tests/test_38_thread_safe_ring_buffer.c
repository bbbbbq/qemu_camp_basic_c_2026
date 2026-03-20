#include "../checker/test_framework.h"

int main() {
    test_init("38_thread_safe_ring_buffer");

    printf("\n🧪 测试练习题：38_thread_safe_ring_buffer\n");

    // 检查未完成标记
    int has_marker =
        file_contains_marker("../exercises/38_thread_safe_ring_buffer/38_thread_safe_ring_buffer.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/38_thread_safe_ring_buffer/38_thread_safe_ring_buffer.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 使用题目自带 Makefile（需要 -pthread）
    char output[2048];
    int result = compile_and_run("38_thread_safe_ring_buffer", "38_thread_safe_ring_buffer", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 校验消费者按顺序输出 1,2,3,4,5,6
    ASSERT_TRUE(string_contains(output, "1,2,3,4,5,6"), "输出应包含 1,2,3,4,5,6（顺序正确，无丢失）");

    printf("✅ 程序正确实现了线程安全环形缓冲区（生产者 - 消费者）\n");
    printf("💡 知识点：多线程同步（互斥锁、条件变量）、环形队列读写指针管理、满/空条件等待与唤醒\n");
    strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    g_current_exercise.completed = 1;

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
