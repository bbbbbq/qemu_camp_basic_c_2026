#include "../checker/test_framework.h"
#include <string.h>

#define MAX_PEOPLE 50

int main() {
    test_init("08_circular_queue");
    
    printf("\n🧪 测试练习题: 08_circular_queue\n");
    
    // 检查文件是否还包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/08_circular_queue.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/08_circular_queue.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 使用队列模拟约瑟夫环问题\n");
        printf("💡 提示: 总人数50人，报数间隔为5\n");
        printf("💡 提示: 需要正确模拟淘汰过程并输出每次淘汰的人员编号\n");
        test_finish();
        return 1;
    }
    
    // 编译并运行程序
    char output[2048]; // 更大的缓冲区以容纳所有淘汰记录
    int result = compile_and_run("08_circular_queue", "08_circular_queue", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }
    
    // 检查是否输出了淘汰信息
    ASSERT_TRUE(string_contains(output, "淘汰"), "输出应该包含淘汰信息");
    
    // 检查是否输出了最后剩下的人
    ASSERT_TRUE(string_contains(output, "最后剩下的人"), "输出应该包含最后剩下的人的信息");
    
    // 解析输出中的淘汰顺序
    int eliminated[50];
    int elim_count = 0;
    char *line = strtok(output, "\n");
    int last_survivor = -1;
    
    while (line != NULL && elim_count < 50) {
        int id;
        // 尝试解析淘汰信息格式 "淘汰: x"
        if (sscanf(line, "淘汰: %d", &id) == 1) {
            eliminated[elim_count++] = id;
        }
        // 尝试解析最后剩下的人的信息
        else if (sscanf(line, "最后剩下的人是: %d", &id) == 1) {
            last_survivor = id;
        }
        line = strtok(NULL, "\n");
    }
    
    ASSERT_EQUAL_INT(49, elim_count, "应该淘汰49人，剩下1人");
    ASSERT_TRUE(last_survivor != -1, "应该找到最后剩下的人");
    
    // 验证最后剩下的人是否正确
    ASSERT_EQUAL_INT(19, last_survivor, "最后剩下的人应该是19号");
    
    // 验证淘汰顺序中的一些关键点
    ASSERT_EQUAL_INT(5, eliminated[0], "第一个淘汰的应该是5号");
    ASSERT_EQUAL_INT(10, eliminated[1], "第二个淘汰的应该是10号");
    ASSERT_EQUAL_INT(50, eliminated[9], "第十个淘汰的应该是50号");
    ASSERT_EQUAL_INT(6, eliminated[10], "第十一个淘汰的应该是6号");
    ASSERT_EQUAL_INT(36, eliminated[48], "最后一个淘汰的应该是36号");
    
    // 检查所有淘汰的人员编号是否唯一
    int ids_unique = 1;
    for (int i = 0; i < elim_count; i++) {
        for (int j = i + 1; j < elim_count; j++) {
            if (eliminated[i] == eliminated[j]) {
                ids_unique = 0;
                printf("❌ 编号重复: %d 被多次淘汰\n", eliminated[i]);
                break;
            }
        }
        if (!ids_unique) break;
    }
    
    ASSERT_TRUE(ids_unique, "所有淘汰的人员编号应该唯一");
    
    // 检查所有编号是否在1-50范围内
    int ids_in_range = 1;
    for (int i = 0; i < elim_count; i++) {
        if (eliminated[i] < 1 || eliminated[i] > 50) {
            ids_in_range = 0;
            printf("❌ 编号超出范围: %d\n", eliminated[i]);
            break;
        }
    }
    
    ASSERT_TRUE(ids_in_range, "所有淘汰的人员编号应该在1-50范围内");
    
    if (elim_count == 49 && last_survivor == 19 && ids_unique && ids_in_range) {
        printf("📝 程序正确模拟了约瑟夫环问题\n");
        printf("💡 知识点: 约瑟夫环问题使用队列模拟非常高效\n");
        printf("💡 总人数: 50人\n");
        printf("💡 报数间隔: 5\n");
        printf("💡 最后剩下的是第%d个人\n", last_survivor);
        printf("💡 淘汰顺序与预期完全一致\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序输出:\n%s\n", output);
        printf("💡 提示: 确保程序正确模拟约瑟夫环问题\n");
        printf("💡 提示: 总人数50人，报数间隔为5\n");
        printf("💡 提示: 最后剩下的人应该是19号\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }
    
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}