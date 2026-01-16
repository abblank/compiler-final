-- 更复杂的测试文件，包含多种语义错误

class A {
    a : Int;
    b : Bool;
    
    -- 方法参数类型不匹配
    foo(x : Int, y : Bool) : Int {
        x
    };
    
    -- 方法返回类型不匹配
    bar() : Str {
        42  -- Int类型，但返回类型声明为Str
    };
};

class B inherits A {
    c : Str;
    
    -- 重写方法时参数类型不匹配
    foo(x : Int, y : Int) : Int {  -- y应该是Bool，但这里是Int
        x
    };
    
    -- 重写方法时返回类型不匹配
    bar() : Int {  -- 返回类型应该是Str
        "hello"
    };
};

class C {
    d : A;
    
    -- 方法调用参数类型不匹配
    test1() : Object {
        d.foo(42, true)  -- 第二个参数应该是Bool，但这里是true
    };
    
    -- 方法调用参数数量不匹配
    test2() : Object {
        d.foo(42)  -- 缺少一个参数
    };
    
    -- 调用未定义的方法
    test3() : Object {
        d.baz(42, true)  -- baz方法不存在
    };
    
    -- 静态分派类型不匹配
    test4() : Object {
        let x : A <- new A in
            x@B.foo(42, true)  -- x是A类型，不能静态分派到B
    };
    
    -- 静态分派调用未定义的方法
    test5() : Object {
        let x : B <- new B in
            x@A.baz(42, true)  -- A类中没有baz方法
    };
    
    -- case表达式中的重复类型
    test6() : Object {
        case x of
            a : A => a;
            b : B => b;
            a : A => a;  -- 重复的A类型
        esac
    };
};

class Main {
    main() : Object {
        let c : C <- new C in {
            c.test1();
            c.test2();
            c.test3();
            c.test4();
            c.test5();
            c.test6();
        }
    };
};