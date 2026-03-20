# 12 container_of 宏实现

- 题目

  使用 GCC 扩展（如 `typeof`）实现 `container_of(ptr, type, member)` 宏，通过结构体成员的指针获取结构体变量的指针。

- 要求

  - 示例：定义 `struct Test { int a; char b; }`，若 `ptr` 是 `&test.b`，则 `container_of(ptr, struct Test, b)` 应返回 `&test`。
  - 测试用例：定义结构体变量 `t`，取成员 `t.b` 的指针传入宏，验证返回的指针是否等于 `&t`。

- 测试输入输出

  - 结构体 `t` 的地址为 `0x7ffd...`，成员 `t.b` 的指针传入宏后，输出 `0x7ffd...`（与 `&t` 相同）。

- **考察点：指针运算、`typeof` 扩展、结构体成员偏移量计算。**
