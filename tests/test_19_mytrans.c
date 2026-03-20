#include "../checker/test_framework.h"

int main() {
    test_init("19_mytrans");

    printf("\n🧪 测试练习题: 19_mytrans\n");

    // 检查是否还包含未完成的标记
    int has_marker = file_contains_marker("../exercises/19_mytrans/19_mytrans.c", "I AM NOT DONE");
    has_marker |= file_contains_marker("../exercises/19_mytrans/mytrans.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/19_mytrans/19_mytrans.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现一个程序 mytrans，能够针对输入的英文单词输出其翻译或未找到的提示，格式如下：\n");
        printf("         - 原文: <word>      翻译: <translation>\n");
        printf("         - 原文: <word>  未找到该单词的翻译。\n");
        printf("         （注意：输出格式必须严格匹配，包括空格和标点）\n");
        test_finish();
        return 1;
    }

    // 🎯 我们期望输出中包含以下 7 个固定字符串，顺序不限
    const char *required_strings[] = {
        "原文: code\t翻译: n. 码;密码;法规;法典@vt. 把...编码;制成法典@n. 代码",
        "原文: empowers\t未找到该单词的翻译。",
        "原文: individuals\t未找到该单词的翻译。",
        "原文: to\t翻译: prep. 到;向;趋于@ad. 向前",
        "原文: be\t翻译: prep. 是;有;在",
        "原文: creators\t未找到该单词的翻译。",
        "原文: in\t翻译: prep. 在;在...之内;从事于;按照;穿着@ad. 进入;朝里;在家@a. 在里面的;执政的@n. 执政者;入口"
    };
    const int num_required = 7;

    // 编译并运行程序
    char output[100024];  // 稍微大一些，确保容纳所有输出
    int result = compile_and_run("19_mytrans", "19_mytrans", output, sizeof(output), 1);
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    ASSERT_TRUE(string_contains(output, required_strings[0]), "输出应该包含'原文: code      翻译: n. 码;密码;法规;法典@vt. 把...编码;制成法典@n. 代码'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[1]), "输出应该包含'原文: empowers  未找到该单词的翻译。'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[2]), "输出应该包含'原文: individuals       未找到该单词的翻译。'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[3]), "输出应该包含'原文: to        翻译: prep. 到;向;趋于@ad. 向前'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[4]), "输出应该包含'原文: be        翻译: prep. 是;有;在'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[5]), "输出应该包含'原文: creators  未找到该单词的翻译。'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[6]), "输出应该包含'原文: in        翻译: prep. 在;在...之内;从事于;");
    
    if (string_contains(output, required_strings[0]) && string_contains(output, required_strings[1]) && 
        string_contains(output, required_strings[2]) && string_contains(output, required_strings[3]) && 
        string_contains(output, required_strings[4]) && string_contains(output, required_strings[5]) && 
        string_contains(output, required_strings[6])) {
        printf("🎉 所有期望的翻译结果均已正确输出！\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        // printf("📝 程序实际完整输出:\n%s\n", output);
        printf("💡 提示: 请确保程序对每个输入的单词，按照如下格式输出翻译或未找到提示：\n");
        printf("         - 原文: <word>      翻译: <translation内容>\n");
        printf("         - 原文: <word>  未找到该单词的翻译。\n");
        printf("         并且必须严格匹配上述 7 个示例中的字符串（包括空格与标点）。\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}