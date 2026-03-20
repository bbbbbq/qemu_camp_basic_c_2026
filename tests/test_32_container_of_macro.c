#include <ctype.h>

#include "../checker/test_framework.h"

static void extract_two_addresses(const char* src, char* addr1, size_t n1, char* addr2, size_t n2) {
    /* 从输出中提取两个以 0x 开头的地址字符串 */
    const char* p = strstr(src, "0x");
    if (!p) {
        addr1[0] = '\0';
        addr2[0] = '\0';
        return;
    }
    // 提取第一个地址直到遇到空白或换行
    size_t i = 0;
    while (p[i] && !isspace((unsigned char)p[i]) && i + 1 < n1) {
        addr1[i] = p[i];
        i++;
    }
    addr1[i] = '\0';

    // 继续查找下一个地址
    const char* q = strstr(p + i, "0x");
    if (!q) {
        addr2[0] = '\0';
        return;
    }
    size_t j = 0;
    while (q[j] && !isspace((unsigned char)q[j]) && j + 1 < n2) {
        addr2[j] = q[j];
        j++;
    }
    addr2[j] = '\0';
}

int main() {
    test_init("32_container_of_macro");

    printf("\n🧪 测试练习题：32_container_of_macro\n");

    // 可选：检查未完成标记
    int has_marker =
        file_contains_marker("../exercises/32_container_of_macro/32_container_of_macro.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/32_container_of_macro/32_container_of_macro.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行（使用该题自带 Makefile，需 GNU 扩展）
    char output[1024];
    int result = compile_and_run("32_container_of_macro", "32_container_of_macro", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 基本输出关键字检查
    ASSERT_TRUE(string_contains(output, "container_of(ptr_to_b) = "), "输出应包含 container_of(ptr_to_b) = ");
    ASSERT_TRUE(string_contains(output, "&t                  = "), "输出应包含 &t                  = ");

    // 提取两个地址并比较应相等
    char addr1[64] = {0};
    char addr2[64] = {0};
    extract_two_addresses(output, addr1, sizeof(addr1), addr2, sizeof(addr2));

    ASSERT_TRUE(strlen(addr1) > 0 && strlen(addr2) > 0, "应成功提取到两个地址");
    ASSERT_TRUE(strcmp(addr1, addr2) == 0, "container_of 反推地址应与 &t 相同");

    if (strcmp(addr1, addr2) == 0) {
        printf("✅ 程序正确实现了 container_of 宏\n");
        printf("💡 知识点：本题测试对结构体成员偏移量计算 offsetof，指针运算 与 typeof 扩展的理解\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示：请确保 container_of(ptr, type, member) 正确回退到结构体首地址\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
