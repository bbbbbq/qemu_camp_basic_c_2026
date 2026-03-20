# 19 字符串分割器（类似 strtok_r）

- 题目

  实现线程安全的字符串分割函数 `strtok_r`，支持指定分隔符集合。

- 要求

  - 函数原型：`char* strtok_r(char *str, const char *delim, char **saveptr)`。
  - 输入：字符串 `"hello,world test"`，分隔符 `", "`（逗号和空格）。
  - 输出：分割结果 `["hello", "world", "test"]`。

- 测试输入输出

  - 调用 `strtok_r` 三次，依次输出 `hello`、`world`、`test`。

- **考察点：状态保存（`saveptr` 指针）、分隔符匹配、线程安全（无静态变量）。**
