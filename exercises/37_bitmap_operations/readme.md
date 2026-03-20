# 17 位图操作

- 题目

  实现位图（Bitmap）的置位（set_bit）和查询（test_bit）功能。

- 要求

  - 位图用 `unsigned char*` 数组存储，支持按位操作。
  - 输入：位图大小 10，置位第 0、3、5 位，查询第 3 位应返回 1，查询第 1 位返回 0。
  - 测试用例：`set_bit(bitmap, 0)` → `set_bit(bitmap, 3)` → `set_bit(bitmap, 5)` → `test_bit(bitmap, 0)=1`；`test_bit(bitmap, 1)=0`。

- 测试输入输出

  - 置位 0、3、5 后，查询 3 → 输出 `1`；查询 1 → 输出 `0`。

- **考察点：位运算（`|=、&=、(1<<n)`）、数组索引计算（`byte = bit / 8`，`offset = bit % 8`）。**
