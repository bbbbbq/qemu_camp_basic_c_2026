#include "../checker/test_framework.h"
#include <stdlib.h>
#include <string.h>

int main() {
    test_init("12_student_management");

    printf("\n🧪 测试练习题: 12_student_management\n");

    // 检查文件是否包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/12_student_management.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");

    if (has_marker) {
        printf("\n💡 提示: 请完成文件读取和结构体操作\n");
        test_finish();
        return 1;
    }

    // 创建测试文件
    FILE *test_file = fopen("students.txt", "w");
    if (test_file == NULL) {
        printf("❌ 无法创建测试文件\n");
        test_finish();
        return 1;
    }
    fprintf(test_file, "S001 Alice 20\n");
    fprintf(test_file, "S002 Bob 21\n");
    fprintf(test_file, "S003 Carol 19\n");
    fclose(test_file);

    // 编译并运行程序
    char output[1024];
    int result = compile_and_run("12_student_management", "12_student_management", output, sizeof(output), 0);

    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");

    // 检查输出内容
    ASSERT_TRUE(string_contains(output, "学号：S001, 姓名：Alice, 年龄：20"),
                "输出应该包含第一个学生的信息");
    ASSERT_TRUE(string_contains(output, "学号：S002, 姓名：Bob, 年龄：21"),
                "输出应该包含第二个学生的信息");
    ASSERT_TRUE(string_contains(output, "学号：S003, 姓名：Carol, 年龄：19"),
                "输出应该包含第三个学生的信息");

    if (string_contains(output, "S001") && string_contains(output, "S002") && string_contains(output, "S003")) {
        printf("✅ 学生信息管理功能正确实现\n");
        printf("💡 知识点: 文件I/O，结构体，动态内存管理\n");
        g_current_exercise.completed = 1;
    }

    // 清理
    remove("students.txt");
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}