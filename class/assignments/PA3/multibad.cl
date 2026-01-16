(* Test file with multiple syntax errors *)

class GoodClass {
    x : Int <- 0;
    y : Int <- 0;
    
    init(newX : Int, newY : Int) : SELF_TYPE {
        {
            x <- newX;
            y <- newY;
            self;
        }
    };
};

(* Error 1: 'Class' should be lowercase 'class' *)
Class BadClass1 {
    x : Int;
};

(* Error 2: b is not a valid type identifier (lowercase) *)
Class BadClass2 inherits b {
    y : Int;
};

(* Error 3: missing closing brace *)
Class BadClass3 inherits GoodClass {
    z : Int;

(* Error 4: 'inherts' should be 'inherits' *)
Class BadClass4 inherts GoodClass {
    w : Int;
};

(* Error 5: missing semicolon after class definition *)
Class BadClass5 inherits GoodClass {
    v : Int;
}

(* Error 6: invalid feature syntax - missing colon *)
Class BadClass6 inherits GoodClass {
    bad_feature Int <- 10;
};

(* Error 7: method with wrong return type syntax *)
Class BadClass7 inherits GoodClass {
    bad_method() -> Int {
        5
    };
};

(* Error 8: feature without proper termination *)
Class BadClass8 inherits GoodClass {
    another_feature : Int <- 20
    missing_semicolon : String <- "error";
};

(* Error 9: invalid formal parameter syntax *)
Class BadClass9 inherits GoodClass {
    bad_method(param1 Int, param2 : Str) : Int {
        10
    };
};

(* Error 10: missing parentheses in method definition *)
Class BadClass10 inherits GoodClass {
    bad_method : Int {
        15
    };
};

(* Error 11: invalid let expression syntax *)
Class BadClass11 inherits GoodClass {
    test_method() : Object {
        let x Int <- 5, y String <- "hello" in
            x + y
    };
};

(* Error 12: invalid case expression syntax *)
Class BadClass12 inherits GoodClass {
    test_method() : Object {
        case x of
            y : Int => 1;
            z : String => 2
        (* missing 'esac' *)
    };
};

(* Error 13: invalid if-then-else syntax *)
Class BadClass13 inherits GoodClass {
    test_method() : Object {
        if true then
            5
        (* missing 'else' and 'fi' *)
    };
};

(* Error 14: invalid while loop syntax *)
Class BadClass14 inherits GoodClass {
    test_method() : Object {
        while true loop
            5
        (* missing 'pool' *)
    };
};

(* Error 15: invalid block syntax *)
Class BadClass15 inherits GoodClass {
    test_method() : Object {
        {
            1;
            2;
            3
        (* missing closing brace *)
    };
};