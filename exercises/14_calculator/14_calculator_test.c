#include <stdio.h>
#include <assert.h>

// 测试加法函数
void test_add() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(0, 0) == 0);
    assert(add(-5, -5) == -10);
}

// 测试减法函数
void test_subtract() {
    assert(subtract(5, 3) == 2);
    assert(subtract(0, 0) == 0);
    assert(subtract(-1, -1) == 0);
    assert(subtract(10, 20) == -10);
}

// 测试乘法函数
void test_multiply() {
    assert(multiply(2, 3) == 6);
    assert(multiply(-1, 1) == -1);
    assert(multiply(0, 5) == 0);
    assert(multiply(-5, -5) == 25);
}

// 测试除法函数
void test_divide() {
    assert(divide(6, 3) == 2);
    assert(divide(0, 1) == 0);
    assert(divide(-10, 2) == -5);
    // 测试除数为0的情况
    assert(divide(5, 0) == 0); // 预期输出错误信息
}

int main() {
    test_add();
    test_subtract();
    test_multiply();
    test_divide();
    
    printf("所有测试通过！\n");
    return 0;
}