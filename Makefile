CC = gcc
CFLAGS = -Wall -Wextra -std=c11

CHECKER = c-checker
CHECKER_SRC = checker.c
CHECKER_DIR = checker
EXERCISES_DIR = exercises
TESTS_DIR = tests

.PHONY: all c-checker list check-all check hint test clean watch help

all: c-checker

c-checker: $(CHECKER_SRC) $(CHECKER_DIR)/test_framework.c $(CHECKER_DIR)/test_framework.h
	$(CC) $(CFLAGS) -o $(CHECKER) $(CHECKER_SRC)

list: c-checker
	./$(CHECKER) list

check-all: c-checker
	./$(CHECKER) check-all

%:
	@:

check: c-checker
	@if [ -z "$(filter-out $@,$(MAKECMDGOALS))" ]; then \
		echo "错误: 请指定练习题名称或编号"; \
		echo "使用练习题名称: make check 21_singly_linked_list_josephus"; \
		echo "使用练习题编号: make check 21"; \
		exit 1; \
	fi
	@./$(CHECKER) check $(filter-out $@,$(MAKECMDGOALS)) || true

hint: c-checker
	@if [ -z "$(filter-out $@,$(MAKECMDGOALS))" ]; then \
		echo "错误: 请指定练习题名称或编号"; \
		echo "使用练习题名称: make hint 40_bloom_filter_bitmap"; \
		echo "使用练习题编号: make hint 40"; \
		exit 1; \
	fi
	@./$(CHECKER) hint $(filter-out $@,$(MAKECMDGOALS)) || true

test: check-all

clean:
	@rm -f $(CHECKER)
	@rm -f $(CHECKER_DIR)/*.o
	@find $(EXERCISES_DIR) -type f -executable -delete 2>/dev/null || true
	@find $(EXERCISES_DIR) -type f -name '*.o' -delete 2>/dev/null || true
	@find $(EXERCISES_DIR) -type f -name '*.d' -delete 2>/dev/null || true
	@find $(TESTS_DIR) -type f -executable -name "test_*" -delete 2>/dev/null || true
	@rm -f test_results_summary.json 2>/dev/null || true
	@echo "✅ 清理完成"

watch: c-checker
	@chmod +x watch.sh
	@./watch.sh

help:
	@echo "可用目标:"
	@echo "  c-checker         - 编译 C 语言检查器"
	@echo "  list              - 列出全部 40 道练习题"
	@echo "  check-all         - 检查全部练习题"
	@echo "  check [exercise]  - 检查指定练习题"
	@echo "  hint [exercise]   - 显示指定练习题提示"
	@echo "  test              - 运行全部测试"
	@echo "  clean             - 清理构建文件"
	@echo "  watch             - 启动监控模式"
	@echo "  help              - 显示此帮助信息"
	@echo ""
	@echo "例如:"
	@echo "  make check 01"
	@echo "  make check 21_singly_linked_list_josephus"
	@echo "  make hint 40"
