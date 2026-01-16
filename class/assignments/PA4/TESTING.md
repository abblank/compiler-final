# 语义分析器测试脚本使用说明

## 脚本功能
`test_semant.sh` 脚本用于对比你的语义分析器（`mysemant`）和官方语义分析器（`auth_semant`）的输出结果。

## 使用方法

### 测试单个文件
```bash
./test_semant.sh good.cl
```

### 测试多个文件
```bash
./test_semant.sh good.cl simple.cl test.cl
```

### 测试所有 .cl 文件
```bash
./test_semant.sh *.cl
```

## 输出说明
- 脚本会将两个语义分析器的输出分别保存到 `test_outputs/` 目录中
- `*_mysemant.out` - 我的语义分析器输出
- `*_auth_semant.out` - 官方语义分析器输出
- 脚本会显示两个输出是否一致，并在不一致时显示差异详情
- 脚本还会比较两个程序的退出码是否一致

## 注意事项
- 确保 `mysemant` 和 `auth_semant` 可执行文件存在于当前目录
- 测试脚本会自动创建 `test_outputs` 目录来保存输出文件
- 如果测试文件不存在，脚本会显示错误信息并跳过该文件