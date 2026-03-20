# 13 可扩展动态数组（类似 QEMU GArray）

- 题目

  实现动态数组 `GArray`，支持自动扩容（初始容量 16，每次扩容 2 倍），提供初始化、追加元素、释放内存的接口。

- 要求

  - 结构体定义：`typedef struct { void *data; size_t len; size_t capacity; } GArray`。
  - 接口：`GArray* garray_init(size_t elem_size)`、`void garray_append(GArray *arr, void *elem)`、`void garray_free(GArray *arr)`。
  - 测试用例：初始化 GArray 存储 int，追加 `[1,2,3,16]`（超过初始容量 `16?` 不，初始容量是元素个数，这里假设初始容量 16 个 int，追加 16 个元素后扩容到 32）。

- 测试输入输出

  - 追加 17 个 `int` 元素后，检查 `arr->len=17`，`arr->capacity=32`，且元素值正确。

- **考察点：内存管理（`realloc`）、泛型编程（`void*`）、扩容策略设计。**
