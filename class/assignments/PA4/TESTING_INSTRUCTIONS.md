# 语义分析器测试说明

## 测试脚本使用方法

### 1. 通用测试脚本
- `test_semant.sh` - 详细对比测试脚本，显示差异详情
- `quick_test.sh` - 快速测试脚本，简洁输出结果

### 2. 单个文件测试
```bash
./test_semant.sh good.cl
./quick_test.sh simple.cl
```

### 3. 多文件链接测试
多个文件会被视为一个链接的程序进行测试：
```bash
./test_semant.sh file1.cl file2.cl file3.cl
./quick_test.sh file1.cl file2.cl file3.cl
```

## 重要测试组合

### 需要链接的文件组合
特别注意以下文件需要一起链接测试：
```bash
# 主要链接测试组合
./test_semant.sh main.cl base.cl list.cl data-structures.cl
./quick_test.sh main.cl base.cl list.cl data-structures.cl
```

## 现有文件测试说明

### 推荐的测试方式：

1. **简单的功能验证:**
   ```bash
   ./quick_test.sh good.cl
   ./quick_test.sh simple.cl
   ./quick_test.sh base.cl
   ```

2. **错误检测测试:**
   ```bash
   ./quick_test.sh bad.cl
   ./quick_test.sh empty.cl
   ```

3. **复杂链接测试:**
   ```bash
   ./test_semant.sh main.cl base.cl list.cl data-structures.cl
   ./quick_test.sh main.cl base.cl list.cl data-structures.cl
   ```

4. **全部文件测试:**
   ```bash
   ./quick_test.sh *.cl
   ```

## 输出说明

- `[PASS]` - 输出一致，测试通过
- `[FAIL]` - 输出不一致，测试失败
- 详细测试会显示具体的差异内容和退出码信息

## 注意事项

- 如果测试多个文件，它们将被视为一个完整的程序（链接）
- 确保链接的文件之间有适当的依赖关系
- 错误文件（如 bad.cl, test.cl）可能会产生错误输出，这属于正常行为