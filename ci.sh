#!/usr/bin/env bash

# 一键启动并运行 CI 检测脚本

set -e

CONTAINER_NAME="c-training-advanced"
TEST_RESULTS_FILE="test_results_summary.json"
CI_LOG_FILE="ci.log"
CONTAINER_WAIT_TIME=6

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 日志函数
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 检查依赖
check_dependencies() {
    log_info "检查依赖"

    if ! command -v docker &>/dev/null; then
        log_error "Docker 未安装或不在 PATH 中"
        exit 1
    fi

    if ! docker compose version &>/dev/null; then
        log_error "Docker Compose 未安装或不在 PATH 中"
        exit 1
    fi

    if ! command -v jq &>/dev/null; then
        log_error "jq 未安装或不在 PATH 中"
        exit 1

        # log_info "尝试安装 jq"
        # if command -v apt-get &> /dev/null; then
        #     sudo apt-get update && sudo apt-get install -y jq
        # else
        #     log_error "无法自动安装 jq，请手动安装"
        #     exit 1
        # fi
    fi

    log_success "依赖检查完成"
}

# 启动容器
start_container() {
    log_info "启动 Docker 容器"

    # 启动容器
    # docker compose up -d &>/dev/null
    # if [ $? -eq 0 ]; then  # SC2181 – ShellCheck Wiki: https://www.shellcheck.net/wiki/SC2181
    if docker compose up -d &>/dev/null; then
        log_success "容器启动命令执行完成"
    else
        log_error "容器启动失败"
        exit 1
    fi
}

# 检查容器状态
check_container_status() {
    log_info "检查容器状态"

    if docker ps --format "table {{.Names}}" | grep -q "^${CONTAINER_NAME}$"; then
        log_success "容器 ${CONTAINER_NAME} 正在运行"
        return 0
    else
        log_info "容器 ${CONTAINER_NAME} 未运行"
        return 1
    fi
}

# 在容器内执行 CI 检测
run_ci_tests() {
    # 编译检查器和所有必要的组件
    log_info "编译检查器和必要组件"
    if ! docker exec "$CONTAINER_NAME" make c-checker; then
        return 1
    fi

    # 测试所有练习题并生成 JSON 报告
    log_info "测试所有练习题"
    if docker exec "$CONTAINER_NAME" ./c-checker check-all 2>&1 | tee >(sed -r "s/\x1B\[([0-9]{1,3}(;[0-9]{1,2})?)?[mGK]//g" >"$CI_LOG_FILE"); then
        log_success "测试执行完成"
    else
        log_error "测试执行失败"
        return 1
    fi

    # 检查测试结果文件是否存在
    if [ ! -f "$TEST_RESULTS_FILE" ]; then
        log_error "测试结果文件 $TEST_RESULTS_FILE 不存在"
        return 1
    fi

    # 验证测试结果
    if ! PASSED_COUNT=$(jq '.test_summary.passed_exercises' "$TEST_RESULTS_FILE" 2>/dev/null) || [ -z "$PASSED_COUNT" ] || [ "$PASSED_COUNT" = "null" ]; then
        log_error "无法解析测试结果中的通过练习数量"
        return 1
    fi

    if ! TOTAL_COUNT=$(jq '.test_summary.total_exercises' "$TEST_RESULTS_FILE" 2>/dev/null) || [ -z "$TOTAL_COUNT" ] || [ "$TOTAL_COUNT" = "null" ]; then
        log_error "无法解析测试结果中的总练习数量"
        return 1
    fi

    if ! SCORE=$(jq -r '.test_summary.total_score' "$TEST_RESULTS_FILE" 2>/dev/null) || [ -z "$SCORE" ] || [ "$SCORE" = "null" ]; then
        log_error "无法解析测试结果中的总分"
        return 1
    fi

    # 生成测试报告并写入日志文件
    {
        echo -e "\n测试完成！查看详细报告："
        jq '.test_summary' "$TEST_RESULTS_FILE"

        if [ "$PASSED_COUNT" -eq "$TOTAL_COUNT" ]; then
            echo -e "\n所有 ${TOTAL_COUNT} 个练习题测试通过！总分：${SCORE}"
        else
            echo -e "\n测试失败：只有 $PASSED_COUNT/$TOTAL_COUNT 个练习题通过，总分：${SCORE}"

            if NOT_COMPLETED_NAMES=$(jq -r '.exercises[] | select(.status == "NOT_COMPLETED") | .name' "$TEST_RESULTS_FILE" 2>/dev/null) && [ -n "$NOT_COMPLETED_NAMES" ]; then
                echo -e "\nNOT_COMPLETED:\n$NOT_COMPLETED_NAMES"
            fi

            if FAILED_NAMES=$(jq -r '.exercises[] | select(.status == "FAILED") | .name' "$TEST_RESULTS_FILE" 2>/dev/null) && [ -n "$FAILED_NAMES" ]; then
                echo -e "\nFAILED:\n$FAILED_NAMES"
            fi
        fi
    } >>"$CI_LOG_FILE"
}

# 停止并清理容器
cleanup_container() {
    log_info "停止并清理容器"

    if docker compose down &>/dev/null; then
        log_success "容器已停止"
    else
        log_warning "容器停止时出现问题"
    fi
}

main() {
    check_dependencies

    start_container
    log_info "等待 ${CONTAINER_WAIT_TIME} 秒后检查容器状态"
    sleep "$CONTAINER_WAIT_TIME"
    if check_container_status; then
        log_info "开始执行 CI 检测"
        rm -f "$TEST_RESULTS_FILE" "$CI_LOG_FILE"
        if run_ci_tests; then
            log_success "CI 检测完成"
        else
            log_error "CI 检测失败"
        fi
    else
        log_error "容器启动失败，跳过 CI 检测"
    fi

    cleanup_container
    log_info "等待 ${CONTAINER_WAIT_TIME} 秒后检查容器状态"
    sleep "$CONTAINER_WAIT_TIME"
    if check_container_status; then
        log_warning "容器 ${CONTAINER_NAME} 仍在运行"
    else
        log_success "容器 ${CONTAINER_NAME} 已停止"
    fi

    if [ -f "$CI_LOG_FILE" ]; then
        log_info "CI 详细结果请查看 $(pwd)/$CI_LOG_FILE"
    fi
}

trap cleanup_container INT TERM

main "$@"
