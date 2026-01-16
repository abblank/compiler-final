#!/bin/bash

# 测试脚本：比较mycoolc和官方coolc的输出
# 参数格式与mycoolc一致

# 检查参数是否提供
if [ $# -eq 0 ]; then
    echo "用法: $0 <input-file> [options]"
    echo "示例: $0 test.cl"
    echo "      $0 -o test.cl"
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

# 运行mycoolc并保存输出
echo "正在运行mycoolc..."
mycoolc_output="test/mycoolc_${base_name}.output"
./mycoolc $options "$input_file" > "$mycoolc_output" 2>&1

# 运行官方coolc并保存输出
echo "正在运行官方coolc..."
official_output="test/official_${base_name}_coolc.output"
../../bin/coolc $options "$input_file" > "$official_output" 2>&1

# 比较输出并生成diff
echo "正在比较输出..."
diff_output="test/diff_${base_name}_coolc.txt"
diff -u "$mycoolc_output" "$official_output" > "$diff_output"

# 显示差异摘要
diff_lines=$(wc -l < "$diff_output")
if [ "$diff_lines" -eq 0 ]; then
    echo "mycoolc和官方coolc的输出完全一致！"
    rm "$diff_output"  # 删除空的diff文件
else
    echo "发现差异！差异已保存到: $diff_output"
    echo "差异行数: $diff_lines"
fi

echo "mycoolc输出已保存到: $mycoolc_output"
echo "官方coolc输出已保存到: $official_output"