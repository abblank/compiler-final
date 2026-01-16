#!/bin/bash

# 快速测试脚本 - 简化版
# 使用 $* 将参数原封不动地传递给命令，支持单个或多个文件

if [ $# -eq 0 ]; then
    echo "用法: $0 <file1.cl> [file2.cl] ..."
    exit 1
fi

mkdir -p test_outputs

./mysemant "$@" > "test_outputs/mysemant_output.out" 2>&1
./auth_semant "$@" > "test_outputs/auth_semant_output.out" 2>&1

if diff -q "test_outputs/mysemant_output.out" "test_outputs/auth_semant_output.out" > /dev/null 2>&1; then
    echo "[PASS] $*"
else
    echo "[FAIL] $*"
fi