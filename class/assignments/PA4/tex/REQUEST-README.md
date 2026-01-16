# PA4 语义分析器测试请求

本文档详细说明如何在Linux环境中为PA4语义分析器创建测试脚本、执行测试以及管理测试文件。

## 目录结构

请按照以下目录结构组织PA4项目：

```
PA4/
├── README                 # 项目说明文档
├── Makefile              # 构建脚本
├── semant.h              # 语义分析器头文件
├── semant.cc             # 语义分析器实现文件
├── cool-tree.h           # AST节点定义
├── cool-tree.cc          # AST节点实现
├── utilities.h           # 工具函数头文件
├── utilities.cc          # 工具函数实现
├── stringtab.h           # 字符串表头文件
├── stringtab.cc          # 字符串表实现
├── list.h                # 列表类头文件
├── list.cc               # 列表类实现
├── graph.h               # 图类头文件
├── graph.cc              # 图类实现
├── symtab.h              # 符号表头文件
├── symtab.cc             # 符号表实现
├── mysemant              # 编译后的语义分析器
├── good.cl               # 正确的测试用例
├── bad.cl                # 包含语义错误的测试用例
├── test_semant.sh        # 语义分析器测试脚本
├── test_coolc.sh         # 完整编译器测试脚本
├── compare_outputs.sh    # 输出比较脚本
├── test_outputs/         # 测试输出目录
│   ├── auth_semant_output.out  # 官方语义分析器输出
│   └── mysemant_output.out     # 我们的语义分析器输出
└── tex/                  # 文档目录
    ├── main.tex          # 主文档
    └── REQUEST-README.md # 本文档
```

## 测试脚本

### 1. test_semant.sh - 语义分析器测试脚本

创建以下脚本文件，用于测试语义分析器：

```bash
#!/bin/bash

# 测试语义分析器脚本
# 用法: ./test_semant.sh <test_file>

if [ $# -ne 1 ]; then
    echo "用法: $0 <test_file>"
    exit 1
fi

TEST_FILE=$1
AUTH_OUTPUT="test_outputs/auth_semant_output.out"
MY_OUTPUT="test_outputs/mysemant_output.out"

# 确保输出目录存在
mkdir -p test_outputs

# 使用官方语义分析器处理测试文件
echo "使用官方语义分析器处理 $TEST_FILE..."
./auth_semant $TEST_FILE > $AUTH_OUTPUT 2>&1
AUTH_RESULT=$?

# 使用我们的语义分析器处理测试文件
echo "使用我们的语义分析器处理 $TEST_FILE..."
./mysemant $TEST_FILE > $MY_OUTPUT 2>&1
MY_RESULT=$?

# 比较退出码
if [ $AUTH_RESULT -ne $MY_RESULT ]; then
    echo "错误: 退出码不匹配 (官方: $AUTH_RESULT, 我们: $MY_RESULT)"
    exit 1
fi

# 比较输出
echo "比较输出..."
diff $AUTH_OUTPUT $MY_OUTPUT > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "测试通过: 输出完全一致"
else
    echo "测试失败: 输出存在差异"
    echo "官方输出:"
    cat $AUTH_OUTPUT
    echo "我们的输出:"
    cat $MY_OUTPUT
    echo "差异:"
    diff $AUTH_OUTPUT $MY_OUTPUT
    exit 1
fi

echo "测试完成"
```

### 2. test_coolc.sh - 完整编译器测试脚本

创建以下脚本文件，用于测试完整编译器：

```bash
#!/bin/bash

# 测试完整编译器脚本
# 用法: ./test_coolc.sh <test_file>

if [ $# -ne 1 ]; then
    echo "用法: $0 <test_file>"
    exit 1
fi

TEST_FILE=$1
AUTH_OUTPUT="test_outputs/auth_coolc_output.out"
MY_OUTPUT="test_outputs/mycoolc_output.out"

# 确保输出目录存在
mkdir -p test_outputs

# 使用官方编译器处理测试文件
echo "使用官方编译器处理 $TEST_FILE..."
./coolc $TEST_FILE > $AUTH_OUTPUT 2>&1
AUTH_RESULT=$?

# 使用我们的编译器处理测试文件
echo "使用我们的编译器处理 $TEST_FILE..."
./mycoolc $TEST_FILE > $MY_OUTPUT 2>&1
MY_RESULT=$?

# 比较退出码
if [ $AUTH_RESULT -ne $MY_RESULT ]; then
    echo "错误: 退出码不匹配 (官方: $AUTH_RESULT, 我们: $MY_RESULT)"
    exit 1
fi

# 比较输出
echo "比较输出..."
diff $AUTH_OUTPUT $MY_OUTPUT > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "测试通过: 输出完全一致"
else
    echo "测试失败: 输出存在差异"
    echo "官方输出:"
    cat $AUTH_OUTPUT
    echo "我们的输出:"
    cat $MY_OUTPUT
    echo "差异:"
    diff $AUTH_OUTPUT $MY_OUTPUT
    exit 1
fi

echo "测试完成"
```

### 3. compare_outputs.sh - 输出比较脚本

创建以下脚本文件，用于比较两个输出文件：

```bash
#!/bin/bash

# 比较两个输出文件脚本
# 用法: ./compare_outputs.sh <file1> <file2>

if [ $# -ne 2 ]; then
    echo "用法: $0 <file1> <file2>"
    exit 1
fi

FILE1=$1
FILE2=$2

if [ ! -f "$FILE1" ]; then
    echo "错误: 文件 $FILE1 不存在"
    exit 1
fi

if [ ! -f "$FILE2" ]; then
    echo "错误: 文件 $FILE2 不存在"
    exit 1
fi

echo "比较文件 $FILE1 和 $FILE2..."
diff $FILE1 $FILE2 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "文件完全一致"
else
    echo "文件存在差异:"
    diff $FILE1 $FILE2
fi
```

## 设置脚本权限

创建脚本后，需要设置可执行权限：

```bash
chmod +x test_semant.sh
chmod +x test_coolc.sh
chmod +x compare_outputs.sh
```

## 测试用例创建指南

### 重要说明

**注意**：以下文件已经存在，请勿创建或修改：
- `good.cl` - 官方提供的正确测试用例
- `bad.cl` - 官方提供的错误测试用例  
- `main.cl`, `base.cl`, `list.cl`, `data-structures.cl` - 您的四文件项目测试用例（作为一个整体项目测试）

### 1. 四文件项目测试（main.cl + base.cl + list.cl + data-structures.cl）

这是您的主要测试项目，需要将这4个文件作为一个整体进行测试：

```bash
# 测试整个项目（必须同时处理这4个文件）
./test_semant.sh main.cl base.cl list.cl data-structures.cl

# 或者创建项目测试脚本
#!/bin/bash
# test_project.sh - 测试四文件项目
echo "测试四文件项目..."
./mysemant main.cl base.cl list.cl data-structures.cl > my_project_output.out 2>&1
./auth_semant main.cl base.cl list.cl data-structures.cl > auth_project_output.out 2>&1
diff my_project_output.out auth_project_output.out
```

### 2. 官方测试文件单独测试

对于官方提供的其他.cl文件，需要各自单独测试：

```bash
# 单独测试每个官方文件
./test_semant.sh good.cl
./test_semant.sh bad.cl
# 其他官方测试文件...
```

### 3. 复杂语义错误测试用例（test_complex.cl）

创建一个名为`test_complex.cl`的文件，包含全面覆盖的复杂语义错误。该文件已经创建，包含以下10个主要错误类别：

**错误类别覆盖：**
1. **继承相关错误**（4种）：循环继承、继承未定义类、重复类定义
2. **类型相关错误**（3种）：类型不匹配、SELF_TYPE错误、未定义类型
3. **方法相关错误**（6种）：方法重定义、未定义方法调用、参数类型/数量不匹配
4. **属性相关错误**（3种）：属性重定义、未定义属性访问、属性类型不匹配
5. **let表达式错误**（3种）：变量类型未定义、初始化类型不匹配、变量重定义
6. **case表达式错误**（2种）：分支类型重复、分支类型未定义
7. **复杂表达式错误**（8种）：if/while条件错误、算术/比较/逻辑运算错误、new/isvoid错误、赋值错误
8. **作用域相关错误**（2种）：未定义变量、变量作用域错误
9. **特殊类型处理错误**（2种）：SELF_TYPE上下文错误、继承SELF_TYPE
10. **综合复杂错误**（3种）：多重继承链错误、嵌套表达式错误、方法重写链错误

**总计：33个具体语义错误点**

**测试命令：**
```bash
# 测试复杂语义错误文件
./test_semant.sh test_complex.cl

# 查看预期输出（应该检测到多个语义错误）
./mysemant test_complex.cl
```

**测试目标：**
- 验证语义分析器能够正确识别所有类型的语义错误
- 确保错误消息清晰准确
- 测试错误恢复机制（多个错误都能被检测到）

## 测试执行步骤

### 1. 编译语义分析器

```bash
make semant
```

### 2. 四文件项目测试（重要）

**这是您的主要测试项目，必须作为一个整体测试：**

```bash
# 方法1：使用修改后的测试脚本（推荐）
./test_semant.sh main.cl base.cl list.cl data-structures.cl

# 方法2：手动测试并比较输出
echo "测试四文件项目..."
./mysemant main.cl base.cl list.cl data-structures.cl > my_project_output.out 2>&1
./auth_semant main.cl base.cl list.cl data-structures.cl > auth_project_output.out 2>&1
diff my_project_output.out auth_project_output.out

# 方法3：创建专用项目测试脚本
cat > test_project.sh << 'EOF'
#!/bin/bash
echo "=== 四文件项目测试 ==="
echo "使用官方语义分析器处理..."
./auth_semant main.cl base.cl list.cl data-structures.cl > test_outputs/auth_project.out 2>&1
AUTH_RESULT=$?

echo "使用我们的语义分析器处理..."
./mysemant main.cl base.cl list.cl data-structures.cl > test_outputs/my_project.out 2>&1
MY_RESULT=$?

echo "比较结果..."
if [ $AUTH_RESULT -ne $MY_RESULT ]; then
    echo "错误: 退出码不匹配 (官方: $AUTH_RESULT, 我们: $MY_RESULT)"
    exit 1
fi

diff test_outputs/auth_project.out test_outputs/my_project.out > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "✓ 项目测试通过: 输出完全一致"
else
    echo "✗ 项目测试失败: 输出存在差异"
    echo "差异详情:"
    diff test_outputs/auth_project.out test_outputs/my_project.out
    exit 1
fi
EOF
chmod +x test_project.sh
./test_project.sh
```

### 3. 官方测试文件单独测试

对于官方提供的测试文件，各自单独测试：

```bash
# 基本功能测试
./test_semant.sh good.cl

# 基本错误检测测试  
./test_semant.sh bad.cl

# 复杂语义错误测试（33个错误点）
./test_semant.sh test_complex.cl

# 其他官方测试文件
./test_semant.sh simple.cl
./test_semant.sh empty.cl
# ... 其他.cl文件
```

### 3. 运行多个测试

创建一个批量测试脚本：

```bash
#!/bin/bash

# 批量测试脚本
TEST_FILES="good.cl bad.cl inheritance.cl method_dispatch.cl type_checking.cl let_expression.cl case_expression.cl"

for file in $TEST_FILES; do
    echo "测试文件: $file"
    ./test_semant.sh $file
    echo "----------------------------------------"
done
```

## 测试结果整理

### 1. 保存测试结果

将测试结果保存到文件中：

```bash
./test_semant.sh good.cl > test_results/good_test.log 2>&1
./test_semant.sh bad.cl > test_results/bad_test.log 2>&1
```

### 2. 生成测试报告

创建一个测试报告模板：

```
# PA4 语义分析器测试报告

## 测试环境
- 操作系统: Linux
- 编译器: GCC
- 测试日期: [日期]

## 测试用例
| 测试文件 | 测试结果 | 说明 |
|---------|---------|------|
| good.cl | 通过 | 基本功能测试 |
| bad.cl | 通过 | 错误检测测试 |
| inheritance.cl | 通过 | 继承关系测试 |
| method_dispatch.cl | 通过 | 方法分派测试 |
| type_checking.cl | 通过 | 类型检查测试 |
| let_expression.cl | 通过 | let表达式测试 |
| case_expression.cl | 通过 | case表达式测试 |

## 测试总结
[总结测试结果，指出存在的问题和改进方向]
```

## 常见问题解决

### 1. 权限问题

如果遇到权限错误，确保脚本有执行权限：

```bash
chmod +x *.sh
```

### 2. 路径问题

确保所有脚本和可执行文件在正确的路径下，或者使用绝对路径。

### 3. 输出文件不存在

确保测试输出目录存在：

```bash
mkdir -p test_outputs
```

### 4. 编译错误

如果编译失败，检查依赖文件是否完整，编译器是否正确安装。

## 测试数据收集

### 1. 四文件项目测试数据

**测试用例代码：**
- main.cl: 主程序文件，包含项目入口点
- base.cl: 基础类定义文件
- list.cl: 列表相关类定义
- data-structures.cl: 数据结构类定义

**测试命令：**
```bash
./mysemant main.cl base.cl list.cl data-structures.cl
./auth_semant main.cl base.cl list.cl data-structures.cl
```

**预期结果：**
- 输出应该完全一致（包括错误消息和格式）
- 退出码应该相同

**测试结果记录：**
```
测试类型: 四文件项目整体测试
测试文件: main.cl, base.cl, list.cl, data-structures.cl
官方输出: [保存到 test_outputs/auth_project.out]
我们的输出: [保存到 test_outputs/my_project.out]
结果: 通过/失败
差异: [如果有差异，记录具体差异]
```

### 2. 单个文件测试数据

对于每个测试文件（good.cl, bad.cl, test_complex.cl等）：

**测试用例代码：**
```cool
[具体的COOL代码]
```

**测试命令：**
```bash
./mysemant filename.cl
./auth_semant filename.cl
```

**预期输出：**
```
[具体的输出内容]
```

**实际输出：**
```
[实际的输出内容]
```

**测试结果：**
- 结果: 通过/失败
- 差异分析: [如果有差异，详细说明]
- 错误类型: [如果是失败的测试，说明错误类型]

## 注意事项

### 1. 四文件项目测试优先级
- **最高优先级**：main.cl + base.cl + list.cl + data-structures.cl 四文件整体测试
- 这四文件必须作为一个完整项目一起测试，不能单独分开测试
- 确保语义分析器能正确处理多文件项目中的交叉引用和依赖关系

### 2. 测试覆盖要求
- 官方测试文件（good.cl/bad.cl等）：必须全部单独测试通过
- 复杂语义错误（test_complex.cl）：33个错误点必须全部正确检测
- 四文件项目：必须确保整体语义分析正确

### 3. 错误处理验证
- 测试语义分析器是否能正确报告错误位置（文件名、行号）
- 验证错误消息的准确性和清晰度
- 确保多个错误都能被检测到（错误恢复机制）

### 4. 输出格式一致性
- 我们的语义分析器输出必须与官方版本完全一致
- 包括错误消息格式、警告信息、退出码等
- 特别注意多文件项目中的错误报告格式

### 5. 性能测试
- 四文件项目测试时记录处理时间
- 确保语义分析器能在合理时间内完成复杂项目的分析

### 6. 测试报告生成
测试完成后，请生成包含以下内容的报告：
1. 四文件项目测试结果（必须包含）
2. 所有官方测试文件结果汇总
3. test_complex.cl的33个错误点检测情况
4. 任何发现的差异或问题
5. 测试用例代码和输出文件路径

通过以上步骤，您可以全面测试PA4语义分析器的正确性和健壮性，并收集足够的测试数据用于文档编写。