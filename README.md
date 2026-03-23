# QEMU 训练营基础阶段 C 语言习题

这个目录把 OpenCamp 的两套 C 训练营题目合并成了一套连续编号的 40 题题库，作为 QEMU 训练营基础阶段的 C 语言练习。

- 基础阶段题库保留为 `01-20`
- 专业阶段题库顺延为 `21-40`
- 共 `40` 道题，每题 `5` 分，满分 `200` 分
- 仓库已切换为 `GitHub Actions` 自动评测，并支持把成绩回传到 `OpenCamp`

上游题库来源：

- 基础阶段: [c-training-basic](https://cnb.cool/opencamp/learning-c/c-training-basic)
- 专业阶段: [c-training-advanced](https://cnb.cool/opencamp/learning-c/c-training-advanced)

## 题目列表

### 01-20 基础阶段

1. `01_insert_sort` - 插入排序
2. `02_merge_sort` - 归并排序
3. `03_quick_sort` - 快速排序
4. `04_linear_search` - 线性查找
5. `05_binary_search` - 折半查找
6. `06_stack_maze` - 栈解决迷宫问题
7. `07_queue_maze` - 队列实现广度搜索迷宫问题
8. `08_circular_queue` - 环形队列实现约瑟夫环问题
9. `09_word_counter` - 统计单词个数
10. `10_my_strcpy` - 字符串拷贝
11. `11_command_interpreter` - 命令解释器
12. `12_student_management` - 学生信息管理
13. `13_universal_sorter` - 通用排序接口
14. `14_calculator` - 四则运算
15. `15_url_parser` - URL 参数解析器
16. `16_mysed` - 简单流处理器
17. `17_myfile` - ELF 文件头查看
18. `18_mywc` - 词频统计器
19. `19_mytrans` - 查字典翻译
20. `20_mybash` - 命令解释器项目

### 21-40 专业阶段

21. `21_singly_linked_list_josephus` - 单链表约瑟夫环
22. `22_doubly_circular_queue` - 双向循环链表队列
23. `23_circular_linked_list_josephus` - 环形链表约瑟夫环
24. `24_prev_binary_tree` - 二叉树前序遍历
25. `25_counter_letter` - 排序二叉树字母统计
26. `26_hash_counter` - Hash 表词频统计
27. `27_asm_gcd` - 内联汇编求最大公约数
28. `28_operator_overflow` - 无符号运算溢出检测
29. `29_swap_endian` - 字节序转换
30. `30_debug_print` - 调试宏 `DEBUG_PRINT`
31. `31_event_handler` - 简单事件处理器
32. `32_container_of_macro` - `container_of` 宏实现
33. `33_garray_dynamic_array` - 动态数组
34. `34_protocol_header_parser` - 协议头解析器
35. `35_elf_info_parser` - ELF 信息查看工具
36. `36_lru_cache` - LRU 缓存淘汰算法
37. `37_bitmap_operations` - 位图操作
38. `38_thread_safe_ring_buffer` - 线程安全环形缓冲区
39. `39_strtok_r_thread_safe` - 线程安全字符串分割器
40. `40_bloom_filter_bitmap` - Bloom 过滤器

## 快速开始

### GitHub 自动评分

当你把代码推送到 `main` 分支时，GitHub Actions 会自动：

1. 编译 `c-checker`
2. 执行 `./c-checker check-all`
3. 生成 `test_results_summary.json`
4. 生成 GitHub Job Summary 和测试产物
5. 在配置好 OpenCamp secrets 后，把分数回传到 OpenCamp 榜单

当前 workflow 同时支持：

- 普通 GitHub 仓库直接 `push main`
- GitHub Classroom 生成的学生仓库直接 `push main`
- `pull_request` 场景下只做评测，不回传 OpenCamp

工作流文件在 `.github/workflows/opencamp-autograding.yml`。

### OpenCamp secrets 配置

如果你希望 GitHub Actions 的成绩显示到 OpenCamp 页面，需要在 GitHub 仓库里配置这些 secrets：

- `LEARNING_QEMU_2026_COURSE_POST_API`
- `LEARNING_QEMU_2026_AUTUMN_TOKEN`
- `LEARNING_QEMU_2026_AUTUMN_COURSE_ID`

当前只会回传到 OpenCamp QEMU 榜单。

### GitHub Classroom 使用建议

如果你打算通过 GitHub Classroom 发作业，推荐这样使用：

1. 把这个仓库作为 Classroom template repository
2. 让每个学生获得自己的独立作业仓库
3. 学生直接向自己仓库的 `main` 分支提交代码
4. 由学生仓库内的 GitHub Actions 自动评测并回传 OpenCamp

注意：

- fork 仓库不会自动继承原仓库的 repository secrets
- 如果要让 GitHub Classroom 批量可用，最好在 GitHub 组织里配置 organization secrets
- 至少需要配置：
  - `LEARNING_QEMU_2026_COURSE_POST_API`
  - `LEARNING_QEMU_2026_AUTUMN_TOKEN`
  - `LEARNING_QEMU_2026_AUTUMN_COURSE_ID`

### 1. 编译检查器

```bash
make c-checker
```

### 2. 查看全部题目

```bash
./c-checker list
```

### 3. 查看某道题提示

```bash
./c-checker hint 01
./c-checker hint 21
./c-checker hint 40_bloom_filter_bitmap
```

### 4. 检查某道题

```bash
./c-checker check 01
./c-checker check 21_singly_linked_list_josephus
```

### 5. 检查全部题目

```bash
./c-checker check-all
```

### 6. 直接运行单题

```bash
./run.sh 01_insert_sort
./run.sh 21_singly_linked_list_josephus
```

## 目录结构

```text
qemu_camp_basic_c/
├── .github/workflows/ # GitHub Actions 自动评测与 OpenCamp 回传
├── exercises/         # 40 道练习题源码
├── tests/             # 40 个测试文件
├── checker/           # 测试框架
├── checker.c          # 统一检查器
├── Makefile
├── run.sh
├── watch.sh
└── README.md
```

## 说明

- 题目源码都在 `exercises/<exercise_name>/`
- 测试文件都在 `tests/test_<exercise_name>.c`
- 专业阶段题目为了合并成一套连续题库，编号已从 `21` 开始重排
- `20_mybash` 仍然保留原来的多模块目录结构
- 原有的 CNB 流水线配置已经移除，当前只保留 GitHub Actions 方案
- 质量门禁会在 GitHub Checks 中明确显示是否已满分通过
- OpenCamp 回传 job 与质量门禁分离，未满分时也能继续上报当前得分
