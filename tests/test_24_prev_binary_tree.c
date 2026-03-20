#include "../checker/test_framework.h"

int main() {
    test_init("24_prev_binary_tree");

    printf("\n🧪 测试练习题: 24_prev_binary_tree\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/24_prev_binary_tree/24_prev_binary_tree.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/24_prev_binary_tree.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现二叉树的前序遍历功能\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[2048];  // 稍微大一些，确保容纳完整输出
    int result = compile_and_run("24_prev_binary_tree", "24_prev_binary_tree", output, sizeof(output), 1);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 🎯 期望程序输出包含两行"1 2 3 4 5"
    const char *expected_output[] = {
        "1 2 3 4 5",
        "1 2 3 5 4"
    };
    
    ASSERT_TRUE(string_contains(output, expected_output[0]), "程序输出应该包含'1 2 3 4 5'");
    ASSERT_TRUE(string_contains(output, expected_output[1]), "程序输出应该包含'1 2 3 5 4'");

    if (string_contains(output, expected_output[0]) && string_contains(output, expected_output[1])) {
        printf("✅ 程序正确输出了两行前序遍历结果：\n%s\n", output);
        printf("💡 知识点: 本题测试二叉树的前序遍历实现\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示: 请确保程序输出包含两行\n'%s'\n'%s'", expected_output[0], expected_output[2]);
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}