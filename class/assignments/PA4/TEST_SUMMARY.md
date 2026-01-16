# 语义分析器测试套件

我们已经成功创建了用于测试和对比语义分析器的工具：

## 已创建的文件

### 1. test_semant.sh
- 功能全面的测试脚本，可以对比 mysemant 和 auth_semant 的输出
- 提供详细的差异分析
- 统计测试通过/失败情况
- 保存输出文件供后续分析

### 2. quick_test.sh
- 快速测试脚本，提供简洁的测试结果
- 适合快速验证多个文件

### 3. TESTING.md
- 使用说明文档，解释如何使用测试脚本

## 测试结果概览

运行 `./test_semant.sh *.cl` 的结果显示：
- 总共 9 个测试文件
- 2 个通过 (base.cl, simple.cl)
- 7 个失败 (bad.cl, data-structures.cl, empty.cl, good.cl, list.cl, main.cl, test.cl)

## 主要差异类型

从测试结果可以看出，你的语义分析器与官方版本存在以下差异：

1. 错误报告格式不同 (如行号前缀、错误消息格式等)
2. 某些情况下错误检测不完整 (如 empty.cl 中未检测到 main 方法缺失)
3. AST 输出表示差异 (如 #4 vs #0 的区别)
4. 某些错误检测顺序不同

## 使用方法

```bash
# 运行完整测试
./test_semant.sh *.cl

# 测试特定文件
./test_semant.sh good.cl

# 快速测试
./quick_test.sh *.cl
```

测试输出保存在 test_outputs/ 目录中，分别以 *_mysemant.out 和 *_auth_semant.out 命名。