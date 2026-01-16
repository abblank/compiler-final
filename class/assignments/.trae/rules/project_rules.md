PA4运行我的semant的指令为：
在PA4目录下./mysemant <File.cl> <File.cl> ...

PA4运行官方semant的指令为：
在PA4目录下./auth_semant <File.cl> <File.cl> ...

PA5运行我的cgen的指令为：
在PA5目录下./mycgen <File.cl> <File.cl> ...

PA5运行官方cgen的指令为：
在PA5目录下./auth_cgen <File.cl> <File.cl> ...

注意！不要单独运行cgen，而是通过./mycgen或./auth_cgen运行。

结果将输出到标准输入输出流(多个文件则视为一整个项目拼接后运行)

请勿使用make clean命令，不要删除任何我原有的文件。

PA4如果需要测试错误输出，请尝试使用./mysemant ./test_complex.cl 和 ./auth_semant ./test_complex.cl

PA5如果需要测试错误输出，请尝试使用./mycgen <file.cl> 和 ./auth_cgen <file.cl>

.h文件部分在../../include/中，不要创建新文件。

修改了semant之后需要使用make semant指令重新编译。