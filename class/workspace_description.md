# COOL语言编译器工作区描述文档

## 1. 工作区概述

本工作区包含COOL（Classroom Object Oriented Language）语言编译器的实现，用于完成课程作业PA4和PA5。COOL是一种简化的面向对象编程语言，编译器将COOL源代码编译为MIPS汇编代码，可通过SPIM模拟器运行。

## 2. 主要文件夹结构及作用

### 2.1 `/usr/class/assignments/` - 作业目录
包含PA1至PA5的作业文件，每个PA目录包含一个独立的编译器组件：

- **PA1**: 词法分析器（已完成）
- **PA2**: 语法分析器（已完成，包含cool.flex）
- **PA3**: 语法分析器（已完成，包含cool.y）
- **PA4**: 语义分析器（待完成）
- **PA5**: 代码生成器（待完成）

每个PA目录通常包含：
- `README`: 作业说明和要求
- `Makefile`: 编译配置文件
- 源代码文件（`.cc`, `.h`, `.cl`）
- 测试文件（`good.cl`, `bad.cl`）
- 可执行文件（如`mycoolc`, `lexer`, `parser`, `semant`, `cgen`）

### 2.2 `/usr/class/bin/` - 可执行文件目录
包含编译器的各个组件可执行文件：
- `lexer`: 词法分析器
- `parser`: 语法分析器
- `semant`: 语义分析器
- `cgen`: 代码生成器
- `mycoolc`: 完整的编译器驱动程序

### 2.3 `/usr/class/include/` - 头文件目录
包含所有PA共用的头文件，如：
- `cool-tree.h`: 抽象语法树定义
- `cool.h`: 基本类型和常量定义
- `symtab.h`: 符号表实现
- `stringtab.h`: 字符串表实现
- `utilities.h`: 实用工具函数

### 2.4 `/usr/class/examples/` - 示例代码目录
包含COOL语言示例程序，可用于测试编译器功能。

### 2.5 `/usr/class/lib/` - 库文件目录
包含编译器运行时所需的库文件。

## 3. Makefile用法

### 3.1 PA3 Makefile（语法分析器）
```bash
cd /usr/class/assignments/PA3
make parser      # 编译语法分析器
make myparser    # 运行parser测试good.cl和bad.cl
make clean       # 清理编译生成的文件
make dotest      # 运行测试
```

主要编译流程：
1. 使用Bison处理`cool.y`生成`cool-parse.cc`和`cool-parse.h`
2. 编译`parser-phase.cc`、`cool-parse.cc`和其他依赖文件
3. 链接生成`parser`可执行文件

### 3.2 PA4 Makefile（语义分析器）
```bash
cd /usr/class/assignments/PA4
make semant      # 编译语义分析器
make mysemant    # 运行semant测试good.cl和bad.cl
make clean       # 清理编译生成的文件
make dotest      # 运行测试
```

主要编译流程：
1. 编译`semant.cc`和`semant-phase.cc`
2. 链接生成`semant`可执行文件
3. 过滤处理`symtab_example.o`并修改权限

### 3.3 PA5 Makefile（代码生成器）
```bash
cd /usr/class/assignments/PA5
make cgen        # 编译代码生成器
make mycoolc     # 运行完整编译器测试
make clean       # 清理编译生成的文件
make dotest      # 运行测试
```

主要编译流程：
1. 编译`cgen.cc`和`cgen-phase.cc`
2. 链接生成`cgen`可执行文件
3. 使用`mycoolc`运行完整编译流程

## 4. 需要编写的文档

每个PA都需要编写相应的README文档，包含以下内容：

1. **设计决策**：解释实现中的关键设计选择
2. **代码正确性**：说明如何确保代码的正确性
3. **测试用例充分性**：描述测试用例的设计和覆盖范围

## 5. 指令执行关系

### 5.1 编译流程
```
源代码(.cl) → 词法分析(lexer) → 语法分析(parser) → 语义分析(semant) → 代码生成(cgen) → 汇编代码(.s)
```

### 5.2 各PA之间的关系
- **PA3**（语法分析器）：依赖于PA2的词法分析器（`cool.flex`）
- **PA4**（语义分析器）：依赖于PA3的语法分析器（`cool.y`）
- **PA5**（代码生成器）：依赖于PA4的语义分析器

### 5.3 测试流程
1. 使用`good.cl`测试正确代码的处理
2. 使用`bad.cl`测试错误代码的检测
3. 通过`dotest`目标运行自动化测试

## 6. 运行环境条件

### 6.1 必需工具
- **Flex**: 词法分析器生成工具（用于PA2）
- **Bison**: 语法分析器生成工具（用于PA3）
- **G++**: C++编译器（版本需支持C++11标准）
- **Make**: 构建工具
- **SPIM**: MIPS汇编模拟器（用于运行生成的汇编代码）

### 6.2 环境配置
在PA2和PA3中，需要运行`setup`脚本创建符号链接：
```bash
# PA2 setup
ln -sf /usr/class/bin/parser .
ln -sf /usr/class/bin/semant .
ln -sf /usr/class/bin/cgen .

# PA3 setup
ln -sf ../PA2/lexer .
ln -sf /usr/class/bin/semant .
ln -sf /usr/class/bin/cgen .
```

### 6.3 编译选项
Makefile中使用的编译选项：
- `-g`: 包含调试信息
- `-Wall`: 开启所有警告
- `-D__STDC_LIMIT_MACROS`: 定义标准C限制宏
- `-I/usr/class/include/PA${ASSN}`: 指定头文件路径

## 7. 已完成作业参考

### 7.1 PA2 - 词法分析器
- **cool.flex**: 使用Flex实现的COOL语言词法分析器
  - 定义了关键字、标识符、字符串、注释等词法规则
  - 实现了字符串和注释的状态处理
  - 包含错误处理机制

### 7.2 PA3 - 语法分析器
- **cool.y**: 使用Bison实现的COOL语言语法分析器
  - 定义了类、特性、方法、表达式等语法规则
  - 实现了运算符优先级和结合性
  - 添加了let_chain非终结符处理单重和多重LET绑定

## 8. 待完成作业要点

### 8.1 PA3 - 语法分析器
- 完善`cool.y`中的语法规则
- 实现错误恢复机制
- 确保能正确解析COOL语言的所有语法结构

### 8.2 PA4 - 语义分析器
- 实现`semant.cc`中的语义检查逻辑
- 完成`ClassTable`类的继承关系检查
- 实现类型检查和作用域规则

### 8.3 PA5 - 代码生成器
- 实现`cgen.cc`中的代码生成逻辑
- 完成各种表达式的MIPS汇编代码生成
- 实现对象布局和方法调用机制

## 9. 测试与调试

### 9.1 测试文件
- `good.cl`: 包含合法COOL代码，用于测试正确处理
- `bad.cl`: 包含非法COOL代码，用于测试错误检测

### 9.2 调试技巧
1. 使用`-g`选项编译，便于使用GDB调试
2. 使用`-DDEBUG`宏定义开启调试输出
3. 逐步测试各个组件，确保每个阶段正确

### 9.3 运行示例
```bash
# 完整编译流程
cd /usr/class/assignments/PA5
./mycoolc example.cl
spim example.s  # 运行生成的汇编代码
```

## 10. 注意事项

1. 每个PA的代码都依赖于前一个PA的正确实现
2. 修改代码后需要重新编译整个项目
3. 测试时应考虑边界情况和错误处理
4. 遵循COOL语言规范和MIPS汇编约定
5. 注意内存管理和垃圾回收机制

---

本文档提供了COOL编译器工作区的全面概述，帮助理解各组件之间的关系和完成PA3、PA4、PA5作业所需的环境和步骤。