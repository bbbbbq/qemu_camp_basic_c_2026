#include "../checker/test_framework.h"

int main() {
    test_init("35_elf_info_parser");

    printf("\n🧪 测试练习题：35_elf_info_parser\n");

    // 可选占位标记检查
    int has_marker = file_contains_marker("../exercises/35_elf_info_parser/35_elf_info_parser.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf("\n💡 提示：请完成 exercises/35_elf_info_parser/35_elf_info_parser.c 并移除标记\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序（默认解析 /bin/ls）
    char output[4096];
    int result = compile_and_run("35_elf_info_parser", "35_elf_info_parser", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 输出基本结构校验：类型、入口地址、加载段列表
    ASSERT_TRUE(string_contains(output, "Type: ET_"), "输出应包含 ELF 类型前缀 'Type: ET_'");
    ASSERT_TRUE(string_contains(output, "Entry: 0x"), "输出应包含入口地址 'Entry: 0x...'");
    ASSERT_TRUE(string_contains(output, "Load segments:"), "输出应包含 'Load segments:' 列表");
    ASSERT_TRUE(string_contains(output, "0x"), "输出应包含至少一个 0x 地址");

    // 通过即记录信息
    printf("✅ 程序正确解析了 ELF 基本信息\n");
    printf("💡 知识点：二进制文件 I/O（fread）、结构体与二进制数据对齐、ELF 格式解析\n");
    strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    g_current_exercise.completed = 1;

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
