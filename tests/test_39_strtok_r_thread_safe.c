#include "../checker/test_framework.h"

int main() {
    test_init("39_strtok_r_thread_safe");

    printf("\n🧪 测试练习题：39_strtok_r_thread_safe\n");

    int has_marker =
        file_contains_marker("../exercises/39_strtok_r_thread_safe/39_strtok_r_thread_safe.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/39_strtok_r_thread_safe/39_strtok_r_thread_safe.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("39_strtok_r_thread_safe", "39_strtok_r_thread_safe", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 校验三次分割结果：hello、world、test
    ASSERT_TRUE(string_contains(output, "hello"), "输出应包含 hello");
    ASSERT_TRUE(string_contains(output, "world"), "输出应包含 world");
    ASSERT_TRUE(string_contains(output, "test"), "输出应包含 test");

    printf("✅ 程序正确实现了线程安全的字符串分割 (strtok_r)\n");
    printf("💡 知识点：状态保存（saveptr 指针）、分隔符匹配、线程安全（避免静态全局变量）\n");
    strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    g_current_exercise.completed = 1;

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
