#include "../checker/test_framework.h"

int main() {
    test_init("18_mywc");

    printf("\n🧪 测试练习题: 18_mywc\n");

    // 检查是否还包含未完成的标记
    int has_marker = file_contains_marker("../exercises/18_mywc/mywc.c", "I AM NOT DONE");
    has_marker |= file_contains_marker("../exercises/18_mywc/18_mywc.c", "I AM NOT DONE");
    has_marker |= file_contains_marker("../exercises/18_mywc/Makefile", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/18_mywc 中，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现一个程序 mywc，能够统计输入文本中各个单词的出现次数，并至少正确输出以下单词及其次数：\n");
        printf("         - and                  11\n");
        printf("         - the                  10\n");
        printf("         - skilled              1\n");
        printf("         - just                 3\n");
        printf("         （注意：输出格式应为 '单词 + 若干空格 + 次数'，例如 'and                  11'）\n");
        test_finish();
        return 1;
    }

    // 🎯 我们期望输出中包含以下 4 种 单词+次数 字符串，顺序不限
    const char *required_strings[] = {
        "and                  11",
        "the                  10",
        "skilled              1",
        "just                 3"
    };
    const int num_required = 4;

    // 编译并运行程序
    char output[4096];  // 足够大的缓冲区来存储所有可能的输出
    int result = compile_and_run("18_mywc", "18_mywc", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    // 检查每一个必需的字符串是否都出现在输出中
    ASSERT_TRUE(string_contains(output, required_strings[0]), "输出应该包含'and                  11'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[1]), "输出应该包含'the                  10'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[2]), "输出应该包含'skilled              1'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[3]), "输出应该包含'just                 3'字符串");

    if (string_contains(output, required_strings[0]) && string_contains(output, required_strings[1]) && 
        string_contains(output, required_strings[2]) && string_contains(output, required_strings[3])) {
        printf("🎉 所有期望的单词计数均已正确输出！\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际完整输出:\n%s\n", output);
        printf("💡 提示: 请确保程序统计输入文本中的单词频率，并至少正确输出以下 4 组数据：\n");
        printf("         - and                  11\n");
        printf("         - the                  10\n");
        printf("         - skilled              1\n");
        printf("         - just                 3\n");
        printf("         （格式为：单词后跟若干空格，然后是数字，如 'and                  11'）\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}