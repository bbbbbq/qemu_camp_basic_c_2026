#include "../checker/test_framework.h"

int main() {
    test_init("31_event_handler");

    printf("\n🧪 测试练习题：31_event_handler\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/31_event_handler/31_event_handler.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示：请编辑 exercises/31_event_handler/31_event_handler.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示：实现事件处理器，支持注册事件类型的回调函数，并触发事件时调用对应回调\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("31_event_handler", "31_event_handler", output, sizeof(output), 1);

    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    const char* expected_output = "Event A triggered";

    ASSERT_TRUE(string_contains(output, expected_output), "程序应该输出：Event A triggered");

    if (string_contains(output, expected_output)) {
        printf("✅ 程序正确实现了事件处理器\n");
        printf("💡 知识点：本题测试对函数指针数组、回调机制和事件类型管理的理解\n");

        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：请确保正确实现了事件处理器\n");
        printf("💡 期望输出应包含：%s\n", expected_output);
        printf("💡 具体要求:\n");
        printf("   - 使用枚举定义事件类型（EVENT_A, EVENT_B, EVENT_MAX）\n");
        printf("   - 实现注册函数 register_event()，用于注册回调函数和参数\n");
        printf("   - 实现触发函数 trigger_event()，用于触发指定事件的回调\n");
        printf("   - 注册 EVENT_A 的回调并触发，应输出 'Event A triggered'\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
