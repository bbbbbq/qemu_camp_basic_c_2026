# 07 内嵌汇编求解最大公约数（GCD）

## 题目

使用 x86-64 内联汇编（GCC 扩展）实现欧几里得算法，计算两个无符号整数的 GCD。

## 要求

- 函数原型：`unsigned int gcd_asm(unsigned int a, unsigned int b)`。
- 内联汇编需使用 `volatile` 关键字，避免编译器优化。
- 测试用例：`gcd_asm(12, 8)` → 输出 `4`；`gcd_asm(7, 5)` → 输出 `1`。

## 测试输入输出

- 调用 `gcd_asm(12,8)` → 输出 `4`；调用 `gcd_asm(7,5)` → 输出 `1`。

## 考察点

- 内联汇编语法（操作数约束 `"r"、"a"`）。
- 寄存器操作（`eax/ebx`）。
- `volatile` 防止优化。
