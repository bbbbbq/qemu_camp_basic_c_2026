#include "../checker/test_framework.h"

int main() {
    test_init("17_myfile");

    printf("\n🧪 测试练习题: 17_myfile\n");

    // 检查是否还包含未完成的标记
    int has_marker = file_contains_marker("../exercises/17_myfile/17_myfile.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/17_myfile.c 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 实现一个程序 myfile，能够检测输入 ELF 文件的类型，并输出如下四种类型之一：Unknown、Relocatable、Executable、Shared Object/PIE\n");
        test_finish();
        return 1;
    }

    // 🎯 我们期望输出中包含以下 3 种 ELF 类型字符串，顺序不限
    const char *required_strings[] = {
        "Relocatable",
        "Executable",
        "Shared Object/PIE"
    };

    // 编译并运行程序
    char output[4096];  // 足够大的缓冲区来存储所有可能的输出
    int result = compile_and_run("17_myfile", "17_myfile", output, sizeof(output),1 );
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }

    ASSERT_TRUE(string_contains(output, required_strings[0]), "输出应该包含'Relocatable'字符串");
    ASSERT_TRUE(string_contains(output, required_strings[2]), "输出应该包含'Shared Object/PIE'字符串");
    
    if (string_contains(output, required_strings[0]) && string_contains(output, required_strings[2])) {
        printf("🎉 所有期望的 ELF 类型均已正确输出！\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序实际完整输出:\n%s\n", output);
        printf("💡 提示: 请确保程序对不同 ELF 文件类型（或模拟输入）能正确识别并输出以下类型：\n");
        printf("         - Unknown\n");
        printf("         - Relocatable\n");
        printf("         - Executable\n");
        printf("         - Shared Object/PIE\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }

    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}