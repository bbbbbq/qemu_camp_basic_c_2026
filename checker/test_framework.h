/**
 * test_framework.h
 * 
 * 简单的C语言测试框架 - 专为初学者设计
 * 提供基本的测试断言和输出功能
 */

 #ifndef TEST_FRAMEWORK_H
 #define TEST_FRAMEWORK_H
 
 // 在C11标准下启用POSIX功能
 #define _POSIX_C_SOURCE 200809L
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <time.h>
 
 // ANSI 颜色码，让输出更加美观
 #define COLOR_GREEN   "\033[0;32m"
 #define COLOR_RED     "\033[0;31m"
 #define COLOR_YELLOW  "\033[0;33m"
 #define COLOR_BLUE    "\033[0;34m"
 #define COLOR_RESET   "\033[0m"
 
 // 测试统计
 typedef struct {
     int total_tests;
     int passed_tests;
     int failed_tests;
 } test_stats_t;
 
 // 单个测试结果
 typedef struct {
     char name[256];
     char status[16];  // "PASS" or "FAIL"
     char message[512];
     int expected;
     int actual;
     int has_expected_actual;
 } test_result_t;
 
 // 练习题测试结果
 typedef struct {
     char exercise_name[64];
     char status[16];  // "PASSED", "FAILED", "NOT_COMPLETED"
     test_stats_t stats;
     int test_duration_ms;
     int completed;
     int compiled_successfully;
     char program_output[1024];
     test_result_t individual_tests[32];
     int individual_test_count;
 } exercise_result_t;
 
 // 全局测试统计
 extern test_stats_t g_test_stats;
 
 // 当前练习题结果
 extern exercise_result_t g_current_exercise;
 
 // 初始化测试框架
 void test_init(const char* exercise_name);
 
 // 完成测试并显示结果
 void test_finish(void);
 
 // 生成JSON测试报告
 void generate_json_report(const char* filename, exercise_result_t* result);
 
 // 添加单个测试结果
 void add_test_result(const char* name, const char* status, const char* message, int expected, int actual, int has_expected_actual);
 
 // 断言宏 - 简单易懂
 #define ASSERT_TRUE(condition, message) \
     do { \
         g_test_stats.total_tests++; \
         if (condition) { \
             printf(COLOR_GREEN "✅ PASS" COLOR_RESET ": %s\n", message); \
             g_test_stats.passed_tests++; \
             add_test_result(message, "PASS", "", 0, 0, 0); \
         } else { \
             printf(COLOR_RED "❌ FAIL" COLOR_RESET ": %s\n", message); \
             g_test_stats.failed_tests++; \
             add_test_result(message, "FAIL", "", 0, 0, 0); \
         } \
     } while(0)
 
 #define ASSERT_FALSE(condition, message) \
     ASSERT_TRUE(!(condition), message)
 
 #define ASSERT_EQUAL_INT(expected, actual, message) \
     do { \
         int exp = (expected); \
         int act = (actual); \
         g_test_stats.total_tests++; \
         if (exp == act) { \
             printf(COLOR_GREEN "✅ PASS" COLOR_RESET ": %s (expected: %d, actual: %d)\n", message, exp, act); \
             g_test_stats.passed_tests++; \
             add_test_result(message, "PASS", "", exp, act, 1); \
         } else { \
             printf(COLOR_RED "❌ FAIL" COLOR_RESET ": %s (expected: %d, actual: %d)\n", message, exp, act); \
             g_test_stats.failed_tests++; \
             add_test_result(message, "FAIL", "", exp, act, 1); \
         } \
     } while(0)
 
 #define ASSERT_EQUAL_STR(expected, actual, message) \
     do { \
         const char* exp = (expected); \
         const char* act = (actual); \
         g_test_stats.total_tests++; \
         if (strcmp(exp, act) == 0) { \
             printf(COLOR_GREEN "✅ PASS" COLOR_RESET ": %s\n", message); \
             g_test_stats.passed_tests++; \
             add_test_result(message, "PASS", "", 0, 0, 0); \
         } else { \
             printf(COLOR_RED "❌ FAIL" COLOR_RESET ": %s\n", message); \
             printf("  Expected: \"%s\"\n", exp); \
             printf("  Actual:   \"%s\"\n", act); \
             g_test_stats.failed_tests++; \
             char fail_msg[512]; \
             snprintf(fail_msg, sizeof(fail_msg), "Expected: %s, Actual: %s", exp, act); \
             add_test_result(message, "FAIL", fail_msg, 0, 0, 0); \
         } \
     } while(0)
 
 // 编译并运行程序，捕获输出
 int compile_and_run(const char* source_file, const char* executable, char* output, size_t output_size, int is_make);
 
 // 检查字符串是否包含子字符串
 int string_contains(const char* haystack, const char* needle);
 
 // 检查文件是否包含特定标记
 int file_contains_marker(const char* filename, const char* marker);
 
 #endif // TEST_FRAMEWORK_H