# 20 位图实现 Bloom 过滤器

- 题目

  使用位图和多个哈希函数实现 Bloom 过滤器，支持插入元素和查询元素是否存在。

- 要求

  - 位图大小 `m=100`，哈希函数数量 `k=3`（如 `hash1(str)=sum(c)%m`，`hash2(str)=sum(c*2)%m`，`hash3(str)=sum(c*3)%m`）。
  - 输入：插入 `"apple"`、`"banana"`，查询 `"apple"`（应存在）、`"orange"`（可能存在误判）。
  - 输出：`apple exists: 1`，`orange exists: 0` 或 `1`（允许误判）。

- 测试输入输出

  - 插入后查询 `apple` → 输出 `exists: 1`；查询未插入的 `grape` → 输出 `exists: 0`（理想情况）或 `1`（误判）。

- **考察点：哈希函数设计、位图操作、Bloom 过滤器的误判特性。**
