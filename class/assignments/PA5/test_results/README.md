# 测试执行过程记录

本目录包含对 Cool 编译器的测试结果，测试内容包括使用自实现的 mycoolc 编译器与官方 coolc 编译器对 Cool 代码的编译和执行结果比较。

## 详细执行命令记录

### 1. 创建测试结果目录
```bash
mkdir -p test_results
```
- 创建名为 test_results 的目录用于存放所有测试结果

### 2. 第一个测试：test1.cl

#### 2.1 使用 mycoolc 编译
```bash
./mycoolc test1.cl
```
- 使用自实现的 mycoolc 编译器编译 test1.cl 文件

#### 2.2 重命名 mycoolc 生成的汇编文件
```bash
mv test1.s test1-myc.s
```
- 重命名 mycoolc 生成的汇编文件，避免与 coolc 生成的文件冲突

#### 2.3 使用官方 coolc 编译
```bash
coolc test1.cl
```
- 使用官方 coolc 编译器编译 test1.cl 文件

#### 2.4 重命名 coolc 生成的汇编文件
```bash
mv test1.s test1-coolc.s
```
- 重命名 coolc 生成的汇编文件

#### 2.5 生成汇编代码结果文件
```bash
cp test1-myc.s test_results/test1-mycoolc-result.txt
```
- 复制 mycoolc 生成的汇编代码到结果文件

```bash
cp test1-coolc.s test_results/test1-coolc-result.txt
```
- 复制 coolc 生成的汇编代码到结果文件

#### 2.6 运行汇编代码并生成运行结果
```bash
spim test1-myc.s > test_results/test1-mycoolc-run.txt 2>&1
```
- 运行 mycoolc 生成的汇编代码并将输出保存到结果文件

```bash
spim test1-coolc.s > test_results/test1-coolc-run.txt 2>&1
```
- 运行 coolc 生成的汇编代码并将输出保存到结果文件

### 3. 第二个测试：main.cl base.cl list.cl data-structures.cl

#### 3.1 使用 mycoolc 编译多个文件
```bash
./mycoolc main.cl base.cl list.cl data-structures.cl
```
- 使用自实现的 mycoolc 编译器编译 main.cl base.cl list.cl data-structures.cl 文件

#### 3.2 重命名 mycoolc 生成的文件
```bash
mv main.s main-myc.s
```
- 重命名 mycoolc 生成的汇编文件

#### 3.3 使用官方 coolc 编译多个文件
```bash
coolc main.cl base.cl list.cl data-structures.cl
```
- 使用官方 coolc 编译器编译 main.cl base.cl list.cl data-structures.cl 文件

#### 3.4 重命名 coolc 生成的文件
```bash
mv main.s main-coolc.s
```
- 重命名 coolc 生成的汇编文件

#### 3.5 生成汇编代码结果文件
```bash
cp main-myc.s test_results/main-mycoolc-result.txt
```
- 复制 mycoolc 生成的汇编代码到结果文件

```bash
cp main-coolc.s test_results/main-coolc-result.txt
```
- 复制 coolc 生成的汇编代码到结果文件

#### 3.6 运行汇编代码并生成运行结果
```bash
spim main-myc.s > test_results/main-mycoolc-run.txt 2>&1
```
- 运行 mycoolc 生成的汇编代码并将输出保存到结果文件

```bash
spim main-coolc.s > test_results/main-coolc-run.txt 2>&1
```
- 运行 coolc 生成的汇编代码并将输出保存到结果文件

## 文件说明

### 汇编代码结果
- `test1-mycoolc-result.txt`: mycoolc 编译器生成的 test1.cl 汇编代码
- `test1-coolc-result.txt`: 官方 coolc 编译器生成的 test1.cl 汇编代码
- `main-mycoolc-result.txt`: mycoolc 编译器生成的 main.cl 等文件汇编代码
- `main-coolc-result.txt`: 官方 coolc 编译器生成的 main.cl 等文件汇编代码

### 运行结果
- `test1-mycoolc-run.txt`: mycoolc 生成代码的 spim 运行结果
- `test1-coolc-run.txt`: coolc 生成代码的 spim 运行结果
- `main-mycoolc-run.txt`: mycoolc 生成代码的 spim 运行结果
- `main-coolc-run.txt`: coolc 生成代码的 spim 运行结果