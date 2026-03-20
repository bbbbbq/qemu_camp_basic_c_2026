/**
 * test_03_quick_sort.c
 * 
 * 测试第三个练习题：快速排序
 * 输入：从文件读入 n 个学生的信息（包含姓名和成绩），n 不超过 100
 * 输出：使用快速排序算法按成绩从高到低排序后，在屏幕上依次显示排序后的学生姓名和成绩，每个学生信息占一行
 */

 #include "../checker/test_framework.h"

 int main() {
     test_init("03_quick_sort");
     
     printf("\n🧪 测试练习题: 03_quick_sort\n");
     
     // 检查文件是否还包含 "I AM NOT DONE" 标记
     int has_marker = file_contains_marker("../exercises/03_quick_sort.c", "I AM NOT DONE");
     ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
     
     if (has_marker) {
         printf("\n💡 提示: 请编辑 exercises/03_quick_sort.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
         printf("💡 提示: 快速排序算法：选择一个基准元素，将数组分为小于和大于基准的两部分，递归排序\n");
         printf("💡 提示: 需要从文件读取学生信息，按成绩从高到低排序\n");
         printf("💡 提示: 输出格式：每行显示一个学生的姓名和成绩\n");
         test_finish();
         return 1;
     }
     
     // 编译并运行程序
     char output[1024];
     int result = compile_and_run("03_quick_sort", "03_quick_sort", output, sizeof(output), 0);
     
     ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
     
     if (result != 0) {
         printf("\n❌ 编译或运行失败:\n%s\n", output);
         test_finish();
         return 1;
     }
     
     // 检查是否包含开始提示
     ASSERT_TRUE(string_contains(output, "quick sort") || string_contains(output, "快速排序"), 
                 "输出应该包含排序算法相关信息");
     
     // 检查是否包含学生信息读取提示
     ASSERT_TRUE(string_contains(output, "student") || string_contains(output, "学生") || 
                 string_contains(output, "file") || string_contains(output, "文件"), 
                 "输出应该包含学生信息或文件读取相关信息");
     
     // 检查是否输出了排序结果（至少包含姓名和成绩）
     ASSERT_TRUE(string_contains(output, "name") || string_contains(output, "姓名") || 
                 string_contains(output, "score") || string_contains(output, "成绩"), 
                 "输出应该包含学生姓名和成绩信息");
     
     // 检查输出格式是否正确（每行一个学生信息）
     // 复制一份输出用于分割统计行数，避免破坏原始输出缓冲区
     char output_copy[sizeof(output)];
     strncpy(output_copy, output, sizeof(output_copy) - 1);
     output_copy[sizeof(output_copy) - 1] = '\0';
 
     int line_count = 0;
     char *line = strtok(output_copy, "\n");
     while (line != NULL) {
         if (strlen(line) > 0) {
             line_count++;
         }
         line = strtok(NULL, "\n");
     }
     
     ASSERT_TRUE(line_count >= 2, "输出应该至少包含2行（标题和至少一个学生信息）");
     
     // 校验排序后的精确输出顺序与分数（基于 03_students.txt）
     const char* expected_lines[] = {
         "David 96",
         "Bob 92",
         "Eve 88",
         "Alice 85",
         "Charlie 78"
     };
     const int expected_count = (int)(sizeof(expected_lines) / sizeof(expected_lines[0]));
 
     const char* search_pos = output;
     const char* prev_pos = NULL;
     for (int i = 0; i < expected_count; i++) {
         const char* found = strstr(search_pos, expected_lines[i]);
         char assert_msg[128];
         snprintf(assert_msg, sizeof(assert_msg), "第%d个学生应为 %s", i + 1, expected_lines[i]);
         ASSERT_TRUE(found != NULL, assert_msg);
         if (found == NULL) {
             break;
         }
         ASSERT_TRUE(prev_pos == NULL || found > prev_pos, "学生输出顺序应正确（从高到低）");
         prev_pos = found;
         search_pos = found + strlen(expected_lines[i]);
     }
 
     if (line_count >= 2) {
         printf("📝 程序正确执行了快速排序算法\n");
         printf("💡 知识点: 快速排序平均时间复杂度O(n log n)，最坏O(n²)，空间复杂度O(log n)\n");
         strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
         g_current_exercise.completed = 1;
     } else {
         printf("📝 程序输出:\n%s\n", output);
         printf("💡 提示: 确保程序能正确读取文件中的学生信息并排序\n");
         strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
     }
     
     test_finish();
     return g_test_stats.failed_tests == 0 ? 0 : 1;
 }
