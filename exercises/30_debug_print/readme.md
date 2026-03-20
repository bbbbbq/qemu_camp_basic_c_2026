# 10 调试宏 DEBUG_PRINT

## 题目

实现调试宏 `DEBUG_PRINT`，根据编译选项 `-DDEBUG_LEVEL=1/2/3` 控制输出详细程度：

- `LEVEL=1`：输出函数名和行号（如 `DEBUG: func=main, line=10`）。
- `LEVEL=2`：额外输出变量值（如 `DEBUG: func=main, line=10, x=42`）。
- `LEVEL=3`：输出完整调用堆栈（需调用 `backtrace()`）。

## 要求

- 使用 `__func__`、`__LINE__` 预定义宏。

## 测试输入输出

- 当 `DEBUG_LEVEL=2` 时，调用 `DEBUG_PRINT("x=%d", 42)` → 输出 `DEBUG: func=test, line=20, x=42`。

## 考察点

- 条件编译（`#if/#elif`）。
- 预定义宏。
- 可变参数宏（`__VA_ARGS__`）。
