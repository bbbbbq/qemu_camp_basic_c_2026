# 11 简单事件处理器（回调机制）

- 题目

  实现事件处理器，支持注册事件类型（如 `EVENT_A`、`EVENT_B`）的回调函数，并触发事件时调用对应回调。

- 要求

  - 事件类型用枚举定义（`enum { EVENT_A, EVENT_B, EVENT_MAX }`）。
  - 注册函数：`void register_event(enum EVENT_TYPE type, void (*callback)(void*), void* arg)`。
  - 触发函数：`void trigger_event(enum EVENT_TYPE type)`。
  - 测试用例：注册 `EVENT_A` 的回调打印 "Event A triggered"，触发后输出该信息。

- 测试输入输出

  - 触发 `EVENT_A` → 输出 `Event A triggered`。

- **考察点：函数指针数组、回调机制、事件类型管理。**
