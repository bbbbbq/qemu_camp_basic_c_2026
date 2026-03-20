#include "../checker/test_framework.h"

int main() {
    test_init("21_singly_linked_list_josephus");

    printf("\n🧪 测试练习题：21_singly_linked_list_josephus\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker(
        "../exercises/21_singly_linked_list_josephus/21_singly_linked_list_josephus.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf(
            "\n💡 提示：请编辑 exercises/21_singly_linked_list_josephus/21_singly_linked_list_josephus.c 文件，移除 'I "
            "AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示：实现单链表约瑟夫环问题的功能\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result =
        compile_and_run("21_singly_linked_list_josephus", "21_singly_linked_list_josephus", output, sizeof(output), 1);

    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 🎯 默认情况下，期望输出为 n=5, k=1, m=2 的约瑟夫环结果：输出包含 "2 4 1 5 3"
    const char *expected_output = "2 4 1 5 3";

    ASSERT_TRUE(string_contains(output, expected_output), "程序输出应该包含'2 4 1 5 3'");

    if (string_contains(output, expected_output)) {
        printf("✅ 程序正确输出了约瑟夫环问题的结果：\n%s\n", output);
        printf("💡 知识点：本题测试单链表的创建、遍历和删除操作，以及约瑟夫环算法的实现\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：请确保正确实现了约瑟夫环问题，确保程序输出包含'%s'\n", expected_output);
        printf("💡 具体要求:\n");
        printf("   - 创建包含 n 个节点的单向链表\n");
        printf("   - 从第 k 个节点开始，每数到第 m 个节点将其删除\n");
        printf("   - 输出被删除节点的编号序列\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
