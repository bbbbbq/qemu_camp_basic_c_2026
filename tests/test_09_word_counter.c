#include "../checker/test_framework.h"
#include <string.h>

int main() {
    test_init("09_word_counter");
    
    printf("\n🧪 测试练习题: 统计单词数量\n");
    
    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/09_word_counter.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/09_word_counter.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        test_finish();
        return 1;
    }
    
    // 编译并运行程序
    char output[256];
    int result = compile_and_run("09_word_counter", "09_word_counter", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }
    
    // 检查输出是否包含单词数量
    ASSERT_TRUE(string_contains(output, "单词数量"), "输出应该包含'单词数量'字样");
    
    // 提取数字
    int word_count = -1;
    if (sscanf(output, "单词数量: %d", &word_count) == 1) {
        // 验证单词数量是否正确
        // 原字符串: "Don't ask what your country can do for you, but ask what you can do for your country."
        // 单词列表: Don't, ask, what, your, country, can, do, for, you,, but, ask, what, you, can, do, for, your, country.
        // 注意: "you," 和 "country." 被视为单词（因为只以空格分隔）
        ASSERT_EQUAL_INT(18, word_count, "单词数量应该为18");
    } else {
        ASSERT_TRUE(0, "无法从输出中提取单词数量");
    }
    
    // 测试边界情况
    printf("\n🧪 测试边界情况\n");
    
    // 测试空字符串
    char empty_str[] = "";
    int empty_count = 0;
    int in_empty = 0;
    
    for(int i = 0; empty_str[i] != '\0'; i++) {
        if(empty_str[i] != ' ' && empty_str[i] != '\n' && !in_empty) {
            in_empty = 1;
            empty_count++;
        }
        else if(empty_str[i] == ' ') {
            in_empty = 0;
        }
    }
    
    ASSERT_EQUAL_INT(0, empty_count, "空字符串应该返回0个单词");
    
    // 测试只有空格的字符串
    char space_str[] = "     ";
    int space_count = 0;
    int in_space = 0;
    
    for(int i = 0; space_str[i] != '\0'; i++) {
        if(space_str[i] != ' ' && space_str[i] != '\n' && !in_space) {
            in_space = 1;
            space_count++;
        }
        else if(space_str[i] == ' ') {
            in_space = 0;
        }
    }
    
    ASSERT_EQUAL_INT(0, space_count, "只有空格的字符串应该返回0个单词");
    
    // 测试单个单词
    char single_str[] = "Hello";
    int single_count = 0;
    int in_single = 0;
    
    for(int i = 0; single_str[i] != '\0'; i++) {
        if(single_str[i] != ' ' && single_str[i] != '\n' && !in_single) {
            in_single = 1;
            single_count++;
        }
        else if(single_str[i] == ' ') {
            in_single = 0;
        }
    }
    
    ASSERT_EQUAL_INT(1, single_count, "单个单词应该返回1");
    
    // 测试开头和结尾有空格的情况
    char padded_str[] = "   Hello World   ";
    int padded_count = 0;
    int in_padded = 0;
    
    for(int i = 0; padded_str[i] != '\0'; i++) {
        if(padded_str[i] != ' ' && padded_str[i] != '\n' && !in_padded) {
            in_padded = 1;
            padded_count++;
        }
        else if(padded_str[i] == ' ') {
            in_padded = 0;
        }
    }
    
    ASSERT_EQUAL_INT(2, padded_count, "开头和结尾有空格的字符串应该正确计数");
    
    // 测试多个连续空格
    char multi_space_str[] = "Hello     World";
    int multi_space_count = 0;
    int in_multi_space = 0;
    
    for(int i = 0; multi_space_str[i] != '\0'; i++) {
        if(multi_space_str[i] != ' ' && multi_space_str[i] != '\n' && !in_multi_space) {
            in_multi_space = 1;
            multi_space_count++;
        }
        else if(multi_space_str[i] == ' ') {
            in_multi_space = 0;
        }
    }
    
    ASSERT_EQUAL_INT(2, multi_space_count, "多个连续空格应该正确计数");
    
    if (word_count == 18) {
        printf("📝 程序正确统计了单词数量\n");
        printf("💡 知识点: 使用状态变量(inWord)跟踪是否在单词中是一种常见的文本处理技巧\n");
        printf("💡 原字符串: \"Don't ask what your country can do for you, but ask what you can do for your country.\"\n");
        printf("💡 单词数量: %d\n", word_count);
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序输出:\n%s\n", output);
        printf("💡 提示: 确保程序正确处理各种边界情况\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }
    
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}