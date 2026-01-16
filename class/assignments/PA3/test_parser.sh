#!/bin/bash

# 测试脚本：比较myparser和官方parser的输出
# 参数格式与myparser一致

# 检查参数是否提供
if [ $# -eq 0 ]; then
    echo "用法: $0 <input-file> [options]"
    echo "示例: $0 test.cl"
    echo "      $0 -l test.cl"
    exit 1
fi

# 分离选项和输入文件
options=""
input_file=""

for arg in "$@"; do
    if [[ $arg == -* ]]; then
        options="$options $arg"
    else
        input_file="$arg"
    fi
done

# 检查输入文件是否存在
if [ -z "$input_file" ]; then
    echo "错误: 未指定输入文件"
    exit 1
fi

if [ ! -f "$input_file" ]; then
    echo "错误: 输入文件 '$input_file' 不存在"
    exit 1
fi

# 获取输入文件的基本名称（不含路径和扩展名）
base_name=$(basename "$input_file" .cl)

# 运行myparser并保存输出
echo "正在运行myparser..."
myparser_output="test/myparser_${base_name}.output"
./myparser $options "$input_file" > "$myparser_output" 2>&1

# 运行官方parser并保存输出
echo "正在运行官方parser..."
official_output="test/official_${base_name}.output"
../../bin/lexer $options "$input_file" | ../../bin/parser $options "$input_file" > "$official_output" 2>&1

# 比较输出并生成diff
echo "正在比较输出..."
diff_output="test/diff_${base_name}.txt"
diff -u "$myparser_output" "$official_output" > "$diff_output"

# 显示差异摘要
diff_lines=$(wc -l < "$diff_output")
if [ "$diff_lines" -eq 0 ]; then
    echo "myparser和官方parser的输出完全一致！"
    rm "$diff_output"  # 删除空的diff文件
else
    echo "发现差异！差异已保存到: $diff_output"
    echo "差异行数: $diff_lines"
    
    # 如果需要，也可以生成更友好的diff格式
#    friendly_diff="test/diff_${base_name}_friendly.txt"
#    diff --side-by-side --width=120 "$myparser_output" "$official_output" > "$friendly_diff"
#    echo "友好格式的差异已保存到: $friendly_diff"
fi

echo "myparser输出已保存到: $myparser_output"
echo "官方parser输出已保存到: $official_output"
