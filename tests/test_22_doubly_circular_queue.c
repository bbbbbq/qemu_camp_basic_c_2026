#include "../checker/test_framework.h"

int main() {
    test_init("22_doubly_circular_queue");

    printf("\n🧪 测试练习题：22_doubly_circular_queue\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker =
        file_contains_marker("../exercises/22_doubly_circular_queue/22_doubly_circular_queue.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/22_doubly_circular_queue 下的代码并移除 'I AM NOT DONE' 标记\n");
        printf("💡 提示：用双向循环链表实现一个队列，支持入队和出队操作\n");
        test_finish();
        return 1;
    }

    // 使用 Makefile 进行多文件编译
    char output[4096];
    int result = compile_and_run("22_doubly_circular_queue", "22_doubly_circular_queue", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 基本 FIFO 输出
    ASSERT_TRUE(string_contains(output, "1 2 3"), "应输出基本用例：1 2 3");

    // 单元素队列
    ASSERT_TRUE(string_contains(output, "single: 42"), "应输出单元素用例：single: 42");

    // 空队列出队
    ASSERT_TRUE(string_contains(output, "empty: OK"), "应正确处理空队列出队：empty: OK");

    if (string_contains(output, "1 2 3") && string_contains(output, "single: 42") &&
        string_contains(output, "empty: OK")) {
        printf("✅ 队列功能测试通过（多用例）\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：请确保三个指定用例均能正确工作\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
