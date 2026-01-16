#!/bin/bash

# 语义分析器对比测试脚本
# 用于对比 mysemant（我的语义分析器）和 auth_semant（官方语义分析器）的输出
# 支持单个文件或多个文件（作为链接的程序）

# 检查可执行文件是否存在
if [ ! -f "./mysemant" ]; then
    echo "错误: mysemant 可执行文件不存在"
    exit 1
fi

if [ ! -f "./auth_semant" ]; then
    echo "错误: auth_semant 可执行文件不存在"
    exit 1
fi

# 检查参数
if [ $# -eq 0 ]; then
    echo "用法: $0 <file1.cl> [file2.cl] [file3.cl] ..."
    echo "示例: $0 good.cl simple.cl"
    echo ""
    echo "预设测试套件:"
    echo "  - 运行所有 .cl 文件: $0 *.cl"
    echo "  - 运行特定测试: $0 good.cl simple.cl test.cl"
    exit 1
fi

# 创建输出目录
mkdir -p test_outputs
mkdir -p test_results

echo "开始对比语义分析器输出..."
echo "我的语义分析器 (mysemant) vs 官方语义分析器 (auth_semant)"
echo "========================================================="

# 统计变量
total_tests=1  # 总是只有1个测试（多个文件作为一个程序）
passed_tests=0

# 构建文件列表字符串用于显示
file_list=""
for file in "$@"; do
    if [ -f "$file" ]; then
        if [ -z "$file_list" ]; then
            file_list="$file"
        else
            file_list="$file_list $file"
        fi
    else
        echo "错误: 文件 $file 不存在"
        exit 1
    fi
done

echo "测试文件: $file_list"

# 创建文件名标识符（用于区分不同测试的输出文件）
if [ $# -eq 1 ]; then
    # 单文件测试，使用文件名（去掉扩展名）
    file_identifier=$(basename "$1" .cl)
else
    # 多文件测试，使用"multi_files"作为标识符
    file_identifier="multi_files"
fi

# 运行我的语义分析器
echo "  运行 mysemant $file_list..."
./mysemant "$@" > "test_outputs/mysemant_${file_identifier}.out" 2>&1
mysemant_exit_code=$?

# 运行官方语义分析器
echo "  运行 auth_semant $file_list..."
./auth_semant "$@" > "test_outputs/auth_semant_${file_identifier}.out" 2>&1
auth_semant_exit_code=$?

# 比较退出码
exit_code_match=""
if [ $mysemant_exit_code -ne $auth_semant_exit_code ]; then
    exit_code_match=" [退出码不一致: mysemant=$mysemant_exit_code, auth_semant=$auth_semant_exit_code]"
fi

# 比较输出
if diff -q "test_outputs/mysemant_${file_identifier}.out" "test_outputs/auth_semant_${file_identifier}.out" > /dev/null; then
    if [ -z "$exit_code_match" ]; then
        echo "  [PASS] 所有文件: 输出和退出码都一致"
        passed_tests=$((passed_tests + 1))
    else
        echo "  [FAIL] 所有文件: 输出一致但退出码不一致$exit_code_match"
    fi
else
    echo "  [FAIL] 所有文件: 输出不一致$exit_code_match"
    echo "  差异详情:"
    echo "  ===================================="
    diff -u "test_outputs/mysemant_${file_identifier}.out" "test_outputs/auth_semant_${file_identifier}.out" > "test_results/diff_${file_identifier}.diff" || true
    # 同时显示在终端上
    cat "test_results/diff_${file_identifier}.diff"
    echo "  ===================================="
fi
echo ""

# 保存测试结果摘要
echo "测试文件: $file_list" > "test_results/summary_${file_identifier}.txt"
echo "测试结果: $([ $passed_tests -eq $total_tests ] && echo "通过" || echo "失败")" >> "test_results/summary_${file_identifier}.txt"
echo "我的语义分析器退出码: $mysemant_exit_code" >> "test_results/summary_${file_identifier}.txt"
echo "官方语义分析器退出码: $auth_semant_exit_code" >> "test_results/summary_${file_identifier}.txt"
echo "输出文件: mysemant_${file_identifier}.out, auth_semant_${file_identifier}.out" >> "test_results/summary_${file_identifier}.txt"

echo "========================================================="
echo "测试总结: $passed_tests/$total_tests 测试通过"

if [ $passed_tests -eq $total_tests ]; then
    echo "🎉 测试通过！"
else
    echo "❌ 测试失败"
fi

echo ""
echo "输出文件保存在 test_outputs/ 目录中:"
echo "- 我的语义分析器输出: test_outputs/mysemant_${file_identifier}.out"
echo "- 官方语义分析器输出: test_outputs/auth_semant_${file_identifier}.out"
echo ""
echo "测试结果保存在 test_results/ 目录中:"
echo "- 测试摘要: test_results/summary_${file_identifier}.txt"
if [ $passed_tests -ne $total_tests ]; then
    echo "- 差异详情: test_results/diff_${file_identifier}.diff"
fi