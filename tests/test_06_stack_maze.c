/**
 * test_06_stack_maze.c
 * 
 * 测试第六个练习题：迷宫求解
 * 输入：固定的5x5迷宫
 * 输出：使用深度优先搜索算法找到从(0,0)到(4,4)的路径，并打印路径坐标
 */

#include "../checker/test_framework.h"
#include <string.h>

#define MAX_ROW 5
#define MAX_COL 5

int main() {
    test_init("06_stack_maze.c");
    
    printf("\n🧪 测试练习题: 06_stack_maze.c\n");
    
    // 检查文件是否还包含 "I AM NOT DONE" 标记
    int has_marker = file_contains_marker("../exercises/06_stack_maze.c", "I AM NOT DONE");
    ASSERT_FALSE(has_marker, "练习题应该移除 'I AM NOT DONE' 标记");
    
    if (has_marker) {
        printf("\n💡 提示: 请编辑 exercises/06_stack_maze.cs 文件，移除 'I AM NOT DONE' 标记并完成代码\n");
        printf("💡 提示: 使用深度优先搜索算法解决迷宫问题\n");
        printf("💡 提示: 迷宫格式：0表示通路，1表示墙壁\n");
        printf("💡 提示: 需要找到从(0,0)到(4,4)的路径\n");
        test_finish();
        return 1;
    }
    
    // 编译并运行程序
    char output[2048]; // 更大的缓冲区，因为程序会输出每一步的迷宫状态
    int result = compile_and_run("06_stack_maze", "06_stack_maze", output, sizeof(output), 0);
    
    ASSERT_EQUAL_INT(0, result, "程序应该能够成功编译和运行");
    
    if (result != 0) {
        printf("\n❌ 编译或运行失败:\n%s\n", output);
        test_finish();
        return 1;
    }
    
    // 检查是否找到路径
    ASSERT_TRUE(string_contains(output, "No path!") == 0, "程序应该找到路径，而不是输出'No path!'");
    
    // 检查是否输出了路径坐标
    ASSERT_TRUE(string_contains(output, "(") && string_contains(output, ")"), "输出应该包含路径坐标");
    
    // 预期的路径坐标（从终点到起点）
    int expected_path[][2] = {
        {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4},
        {0, 3}, {0, 2}, {1, 2}, {2, 2}, {2, 1},
        {2, 0}, {1, 0}, {0, 0}
    };
    int expected_count = 13;
    
    // 解析输出中的路径坐标
    int path_coords[50][2]; // 存储路径坐标 [行, 列]
    int coord_count = 0;
    char *line = strtok(output, "\n");
    
    while (line != NULL && coord_count < 50) {
        int row, col;
        // 尝试解析坐标格式 "(行, 列)"
        if (sscanf(line, "(%d, %d)", &row, &col) == 2) {
            path_coords[coord_count][0] = row;
            path_coords[coord_count][1] = col;
            coord_count++;
        }
        line = strtok(NULL, "\n");
    }
    
    ASSERT_TRUE(coord_count > 0, "应该找到至少一个路径坐标");
    ASSERT_EQUAL_INT(expected_count, coord_count, "路径坐标数量应该与预期一致");
    
    // 验证路径是否正确（从终点到起点）
    int path_correct = 1;
    for (int i = 0; i < coord_count && i < expected_count; i++) {
        if (path_coords[i][0] != expected_path[i][0] || 
            path_coords[i][1] != expected_path[i][1]) {
            path_correct = 0;
            printf("❌ 坐标不匹配: 预期(%d, %d), 实际(%d, %d)\n", 
                   expected_path[i][0], expected_path[i][1],
                   path_coords[i][0], path_coords[i][1]);
            break;
        }
    }
    
    ASSERT_TRUE(path_correct, "路径坐标应该与预期完全一致");
    
    // 检查路径的连续性（相邻坐标之间应该相邻）
    int path_continuous = 1;
    for (int i = 1; i < coord_count; i++) {
        int row_diff = abs(path_coords[i][0] - path_coords[i-1][0]);
        int col_diff = abs(path_coords[i][1] - path_coords[i-1][1]);
        
        // 相邻坐标应该只有一个坐标相差1，另一个坐标相同
        if (!((row_diff == 1 && col_diff == 0) || 
              (row_diff == 0 && col_diff == 1))) {
            path_continuous = 0;
            printf("❌ 路径不连续: (%d, %d) -> (%d, %d)\n", 
                   path_coords[i-1][0], path_coords[i-1][1],
                   path_coords[i][0], path_coords[i][1]);
            break;
        }
    }
    
    ASSERT_TRUE(path_continuous, "路径应该是连续的（相邻坐标应该相邻）");
    
    // 检查起点和终点是否正确
    ASSERT_EQUAL_INT(0, path_coords[coord_count-1][0], "路径起点行坐标应该是0");
    ASSERT_EQUAL_INT(0, path_coords[coord_count-1][1], "路径起点列坐标应该是0");
    ASSERT_EQUAL_INT(4, path_coords[0][0], "路径终点行坐标应该是4");
    ASSERT_EQUAL_INT(4, path_coords[0][1], "路径终点列坐标应该是4");
    
    if (path_correct && path_continuous) {
        printf("📝 程序正确找到了从(0,0)到(4,4)的路径\n");
        printf("💡 知识点: 深度优先搜索(DFS)使用栈实现，适合寻找一条路径\n");
        printf("💡 迷宫布局:\n");
        printf("0 1 0 0 0\n");
        printf("0 1 0 1 0\n");
        printf("0 0 0 0 0\n");
        printf("0 1 1 1 0\n");
        printf("0 0 0 1 0\n");
        printf("💡 预期路径: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)→(1,2)→(0,2)→(0,3)→(0,4)→(1,4)→(2,4)→(3,4)→(4,4)\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
        g_current_exercise.completed = 1;
    } else {
        printf("📝 程序输出:\n%s\n", output);
        printf("💡 提示: 确保程序使用深度优先搜索算法正确找到路径\n");
        printf("💡 迷宫布局:\n");
        printf("0 1 0 0 0\n");
        printf("0 1 0 1 0\n");
        printf("0 0 0 0 0\n");
        printf("0 1 1 1 0\n");
        printf("0 0 0 1 0\n");
        printf("💡 预期路径: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)→(1,2)→(0,2)→(0,3)→(0,4)→(1,4)→(2,4)→(3,4)→(4,4)\n");
        strncpy(g_current_exercise.program_output, output, sizeof(g_current_exercise.program_output) - 1);
    }
    
    test_finish();
    return g_test_stats.failed_tests == 0 ? 0 : 1;
}