#include "../checker/test_framework.h"

int main() {
    test_init("16_mysed");

    printf("\n🧪 测试练习题: 16_mysed\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/16_mysed/16_mysed.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/16_mysed.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现一个简化版 sed，接受参数如 's/old/new/'，并对预设文本进行替换后输出\n");
        test_finish();
        return 1;
    }

    // 编译并运行程序
    char output[2048];  // 稍微大一些，确保容纳完整输出
    int result = compile_and_run("16_mysed", "16_mysed", output, sizeof(output), 1);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 🎯 期望程序输出包含以下字符串（可能是默认的输入文本）
    const char *expected_output = "linux is opensource. unix is free os.";

    ASSERT_TRUE(string_contains(output, expected_output),
                "程序输出应该包含字符串: linux is opensource. unix is free os.");

    if (string_contains(output, expected_output)) {
        printf("✅ 程序输出了预期的字符串：\n%s\n", expected_output);
        printf("💡 知识点: 本题可能是验证程序能正确输出或处理特定格式的文本\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际输出:\n%s\n", output);
        printf("💡 提示: 请确保程序输出包含字符串: \"%s\"\n", expected_output);
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}