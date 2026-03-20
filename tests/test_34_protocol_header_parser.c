#include "../checker/test_framework.h"

int main() {
    test_init("34_protocol_header_parser");

    printf("\n🧪 测试练习题：34_protocol_header_parser\n");

    // 检查是否仍存在占位标记
    int has_marker =
        file_contains_marker("../exercises/34_protocol_header_parser/34_protocol_header_parser.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    if (has_marker) {
        printf(
            "\n💡 提示：请编辑 exercises/34_protocol_header_parser/34_protocol_header_parser.c，移除 'I AM NOT DONE' "
            "并完成代码\n");
        printf("💡 提示：定义紧凑协议头结构，解析位域并按要求输出\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("34_protocol_header_parser", "34_protocol_header_parser", output, sizeof(output), 1);

    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    const char* expected_output = "version:0.3, length:32, flags:0x00";
    ASSERT_TRUE(string_contains(output, expected_output), "输出应包含：version:0.3, length:32, flags:0x00");

    if (string_contains(output, expected_output)) {
        printf("✅ 程序正确解析了紧凑协议头\n");
        printf(
            "💡 知识点：位域定义（struct { unsigned int ver_major:4; ... }）、结构体对齐（#pragma "
            "pack(1)）、字节流解析\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf(
            "💡 提示：请确保解析规则为：ver_major=低 8 位高 4 位，ver_minor=低 8 位低 4 位，length=大端 16 "
            "位，flags=低 5 位\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}
