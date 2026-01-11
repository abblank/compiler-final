# PA4和PA5作业指南：应该做和不该做的事情

## PA4 - 语义分析器

### 应该做的事情

1. **实现语义分析功能**
   - 在`semant.cc`中编写语义分析器的主要逻辑
   - 实现`ClassTable`类的构造函数和`install_basic_classes`方法
   - 实现`program_class::semant()`入口函数

2. **扩展AST类**
   - 在`cool-tree.h`或`cool-tree.handcode.h`中添加字段和方法
   - 添加遍历表达式树的方法
   - 实现类型检查规则



4. **编写文档**
   - 在README中解释设计决策
   - 说明代码正确性的保证
   - 解释测试用例的充分性

5. **使用符号表**
   - 可以使用提供的`symtab.h`中的符号表实现
   - 参考`symtab_example.cc`中的示例

6. **调试支持**
   - 可以使用`semant_debug`标志添加调试输出
   - 调试代码应放在`if (semant_debug) {...}`块中

### 不应该做的事情

1. **不要修改以下文件**
   - `Makefile` - 编译配置文件
   - `cool-tree.aps` - AST规范文件
   - `tree.cc`和`tree.h` - 树包定义
   - `cool-tree.cc` - AST方法定义
   - `ast-lex.cc`和`ast-parse.cc` - AST词法分析器和语法分析器
   - `semant-phase.cc` - 语义分析测试驱动程序
   - `symtab.h` - 符号表实现（除非必要）

2. **不要删除已有定义**
   - 不要删除`cool-tree.h`和`cool-tree.handcode.h`中已有的函数和数据成员
   - 这些是系统正常运行所必需的

3. **不要修改错误打印例程**
   - 不要修改提供的错误报告方法

## PA5 - 代码生成器

### 应该做的事情

1. **实现代码生成功能**
   - 在`cgen.cc`中完成代码生成器的实现
   - 实现各种表达式的MIPS汇编代码生成方法
   - 实现对象布局和方法调用机制

2. **扩展代码生成器**
   - 在`cgen.h`中添加需要的声明
   - 在`cgen_supp.cc`中添加支持函数（除了三个特定函数）



4. **修改AST类**
   - 可以修改`cool-tree.h`或`cool-tree.handcode.h`
   - 可以添加字段
   - 可以修改或删除`code`方法

5. **编写文档**
   - 在README中解释设计决策
   - 说明代码正确性的保证
   - 解释测试用例的充分性

6. **使用调试支持**
   - 可以使用`cgen_debug`标志添加调试输出
   - 调试代码应放在`if (cgen_debug) {...}`块中

7. **自定义emit.h**
   - 可以根据需要修改`emit.h`中的宏定义

### 不应该做的事情

1. **不要修改以下文件**
   - `Makefile` - 编译配置文件
   - `cgen-phase.cc` - 编译器驱动程序
   - `cool-tree.cc` - AST方法定义
   - `cool.h` - 编译器基本定义
   - `stringtab.h` - 字符串表操作
   - `dumptype.cc` - AST打印函数

2. **不要修改cgen_supp.cc中的特定函数**
   - `byte_mode`
   - `ascii_mode`
   - `emit_string_constant`

3. **不要修改emit.h中的所有内容**
   - 虽然可以修改，但应谨慎，确保不破坏现有功能

## 通用注意事项

1. **编译和测试**
   - PA4使用`make semant`编译，`./mysemant`测试
   - PA5使用`gmake cgen`编译，`./mycoolc`测试
   - 使用`make dotest`或`gmake dotest`运行标准测试

2. **架构切换**
   - 更改架构时必须执行`make clean`（PA4）或`gmake clean`（PA5）

3. **代码组织**
   - PA4：将添加到AST类的方法定义放在`semant.cc`中
   - PA5：将所有方法定义放在`cgen.cc`中

4. **错误处理**
   - 不要修改错误报告例程
   - 确保错误信息清晰有用

5. **测试充分性**
   - 确保测试用例覆盖各种边界情况
   - 测试应包括正面和负面案例

6. **文档质量**
   - 文档应清晰简洁
   - 解释设计选择的原因
   - 说明如何验证代码正确性

遵循这些指南将帮助您顺利完成PA4和PA5的作业，避免常见的错误和问题。