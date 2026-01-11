PA5：
编译cgen请使用make cgen
使用我的cgen编译.cl文件请使用./mycgen filename.cl
使用官方cgen编译.cl文件请使用./auth_cgen filename.cl
main.cl、base.cl、list.cl、data-structures.cl需要一起作为参数被编译（是一个四文件的项目）

注意：PA5判断cgen是否成功完成需要使用./mycgen main.cl list.cl base.cl data-structures.cl && spim main.s和./auth_cgen main.cl list.cl base.cl data-structures.cl && spim main.s，确保两者输出一致才算成功。

不要修改lexer、parser、semant、cgen相关链接！每次make clean后，使用./setup进行初始化

不要使用git命令