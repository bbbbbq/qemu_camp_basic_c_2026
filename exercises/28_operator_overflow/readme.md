# 08 检测整数无符号运算溢出

## 题目

实现函数检测两个无符号整数加减乘除是否溢出（超出 32 位无符号整数范围）。

## 要求

- 函数原型：
  - `int check_add_overflow_asm(unsigned int a, unsigned int b)`
  - `int check_sub_overflow_asm(unsigned int a, unsigned int b)`
  - `int check_mul_overflow_asm(unsigned int a, unsigned int b)`
  - `int check_div_overflow_asm(unsigned int a, unsigned int b)`
- 返回 `1` 表示溢出，`0` 表示正常。
- 原理：若 `a + b < a`（或 `b`），则溢出（无符号数加法溢出会回绕）。
- 测试用例：`check_add_overflow(UINT_MAX, 1)` → 输出 `1`；`check_add_overflow(100, 200)` → 输出 `0`。

## 测试输入输出

- 输入 `(UINT_MAX, 1)` → 输出 `1`；输入 `(100, 200)` → 输出 `0`。

## 考察点

- 无符号整数溢出特性（回绕）。
- 条件判断逻辑。
