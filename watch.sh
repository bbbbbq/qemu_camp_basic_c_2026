#!/bin/bash

set -e

if [ ! -f "c-checker" ]; then
    echo "⚙️  编译检查器..."
    if ! make c-checker; then
        echo "❌ 检查器编译失败"
        exit 1
    fi
fi

if ! command -v inotifywait >/dev/null 2>&1; then
    echo "警告: 未安装 inotify-tools，将使用轮询模式"
    while true; do
        echo -e "\n🔄 检查所有练习题..."
        ./c-checker check-all
        echo -e "\n⏰ 10 秒后再次检查..."
        sleep 10
    done
else
    while inotifywait -r -e modify,create,delete exercises tests checker >/dev/null 2>&1; do
        clear
        echo "🔄 检测到文件变化，重新检查..."
        ./c-checker check-all
        echo -e "\n📝 继续监控文件变化..."
    done
fi
