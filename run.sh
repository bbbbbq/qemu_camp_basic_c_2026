#!/bin/bash

set -e

if [ $# -eq 0 ]; then
    echo "用法: ./run.sh [exercise_name]"
    echo "例如: ./run.sh 01_insert_sort"
    echo ""
    if [ -f "c-checker" ]; then
        ./c-checker list
    else
        echo "请先编译检查器: make c-checker"
    fi
    exit 1
fi

EXERCISE_NAME=$1
EXERCISE_DIR="exercises/${EXERCISE_NAME}"
SOURCE_FILE="${EXERCISE_DIR}/${EXERCISE_NAME}.c"
EXECUTABLE="${EXERCISE_DIR}/${EXERCISE_NAME}"

if [ "$EXERCISE_NAME" = "20_mybash" ]; then
    SOURCE_FILE="${EXERCISE_DIR}/src/mybash/main.c"
    EXECUTABLE="${EXERCISE_DIR}/20_mybash"
fi

echo "🏃 运行练习题: $EXERCISE_NAME"
echo "=================="

if [ ! -d "$EXERCISE_DIR" ]; then
    echo "❌ 错误: 找不到目录 $EXERCISE_DIR"
    exit 1
fi

if [ ! -f "$SOURCE_FILE" ]; then
    echo "❌ 错误: 找不到源码 $SOURCE_FILE"
    exit 1
fi

if grep -R -q "I AM NOT DONE" "$EXERCISE_DIR"; then
    echo "❌ 错误: 练习题还没有完成，请先移除 'I AM NOT DONE' 标记"
    exit 1
fi

echo "🔨 编译中..."
if [ -f "${EXERCISE_DIR}/Makefile" ]; then
    make -C "$EXERCISE_DIR"
else
    gcc -Wall -Wextra -std=c11 -o "$EXECUTABLE" "$SOURCE_FILE"
fi

echo "✅ 编译成功"
echo "🚀 运行程序:"
echo "---------------"

if [ "$EXERCISE_NAME" = "20_mybash" ]; then
    (cd "$EXERCISE_DIR" && ./20_mybash)
else
    "$EXECUTABLE"
fi

echo ""
echo "✨ 程序执行完成"
