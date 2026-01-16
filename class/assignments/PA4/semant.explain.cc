/*
 * 语义分析器基础知识
 * 
 * 语义分析是编译过程中的一个重要阶段，它在语法分析之后进行，主要任务是：
 * 1. 类型检查：确保程序中的类型使用是正确的，如变量声明、表达式类型匹配等
 * 2. 作用域分析：确保变量和函数的使用符合作用域规则
 * 3. 语义正确性检查：如控制流检查、函数调用参数匹配等
 * 4. 符号表管理：维护程序中所有符号的信息，包括类型、作用域等
 * 
 * 在COOL语言中，语义分析主要包括：
 * - 类继承关系检查
 * - 方法重写规则检查
 * - 类型兼容性检查
 * - 变量作用域检查
 * - 表达式类型推断
 * 
 * COOL语言的类型系统特点：
 * - 单继承：每个类最多有一个父类
 * - 基本类型：Object, Int, Bool, String, SELF_TYPE
 * - 类型兼容：子类型可以赋值给父类型
 * - SELF_TYPE：特殊类型，表示当前对象的类型
 * 
 * 符号表（Symbol Table）：
 * - 用于存储变量、方法、类等符号的信息
 * - 支持作用域嵌套：进入新作用域时添加符号，退出时移除
 * - 类型推断：通过符号表查找变量的类型信息
 * 
 * 语义分析器实现步骤：
 * 1. 构建类继承层次结构
 * 2. 检查类定义的合法性
 * 3. 检查方法和属性定义的合法性
 * 4. 检查方法重写的合法性
 * 5. 检查表达式和语句的类型正确性
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <set>
#include "semant.h"
#include "utilities.h"

// 辅助函数，用于访问类的protected成员
// 这些函数通过动态类型转换，将基类指针转换为派生类指针，从而访问派生类的特定方法
// 这是C++中访问protected成员的常用技巧

// 获取类的名称
Symbol get_class_name(Class_ c) {
    class__class* class_ptr = dynamic_cast<class__class*>(c);
    if (class_ptr) {
        return class_ptr->get_name();
    }
    return NULL;
}

// 获取类的父类名称
Symbol get_class_parent(Class_ c) {
    class__class* class_ptr = dynamic_cast<class__class*>(c);
    if (class_ptr) {
        return class_ptr->get_parent();
    }
    return NULL;
}

// 获取类的特性（方法和属性列表）
Features get_class_features(Class_ c) {
    class__class* class_ptr = dynamic_cast<class__class*>(c);
    if (class_ptr) {
        return class_ptr->get_features();
    }
    return NULL;
}

// 获取方法的名称
Symbol get_method_name(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_name();
    }
    return NULL;
}

// 获取方法的返回类型
Symbol get_method_return_type(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_return_type();
    }
    return NULL;
}

// 获取方法的参数列表
Formals get_method_formals(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_formals();
    }
    return NULL;
}

// 获取方法体表达式
Expression get_method_expr(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_expr();
    }
    return NULL;
}

// 获取属性的名称
Symbol get_attr_name(Feature f) {
    attr_class* attr = dynamic_cast<attr_class*>(f);
    if (attr) {
        return attr->get_name();
    }
    return NULL;
}

// 获取属性的类型声明
Symbol get_attr_type_decl(Feature f) {
    attr_class* attr = dynamic_cast<attr_class*>(f);
    if (attr) {
        return attr->get_type_decl();
    }
    return NULL;
}

// 获取属性的初始化表达式
Expression get_attr_init(Feature f) {
    attr_class* attr = dynamic_cast<attr_class*>(f);
    if (attr) {
        return attr->get_init();
    }
    return NULL;
}

// 获取形式参数的名称
Symbol get_formal_name(Formal f) {
    formal_class* formal = dynamic_cast<formal_class*>(f);
    if (formal) {
        return formal->get_name();
    }
    return NULL;
}

// 获取形式参数的类型声明
Symbol get_formal_type_decl(Formal f) {
    formal_class* formal = dynamic_cast<formal_class*>(f);
    if (formal) {
        return formal->get_type_decl();
    }
    return NULL;
}

// 获取case分支的类型声明
Symbol get_branch_type(Case branch) {
    branch_class* bc = dynamic_cast<branch_class*>(branch);
    if (bc) {
        return bc->get_type_decl();
    }
    return NULL;
}

// 获取case分支的变量名
Symbol get_branch_name(Case branch) {
    branch_class* bc = dynamic_cast<branch_class*>(branch);
    if (bc) {
        return bc->get_name();
    }
    return NULL;
}

// 获取case分支的表达式
Expression get_branch_expr(Case branch) {
    branch_class* bc = dynamic_cast<branch_class*>(branch);
    if (bc) {
        return bc->get_expr();
    }
    return NULL;
}

// 全局ClassTable指针，用于表达式类型检查
// ClassTable是语义分析的核心数据结构，存储了所有类的信息及其继承关系
static ClassTable *classtable = NULL;

// 为Formals类型添加特化版本
// 计算形式参数列表的长度
int list_length(Formals formals) {
    int count = 0;
    if (formals) {
        for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
            count++;
        }
    }
    return count;
}

extern int semant_debug;  // 外部定义的调试标志
extern char *curr_filename;  // 外部定义的当前文件名

// 当前类名，用于类型检查
static Symbol current_class = NULL;

// 当前类对象，用于获取文件名等信息
static Class_ current_class_obj = NULL;

// 当前方法名，用于方法内检查
static Symbol current_method = NULL;

// 简单的Entry类，用于存储Symbol信息
// 继承自Entry基类，用于符号表中的条目
class SymbolEntry : public Entry {
private:
    Symbol type;  // 存储符号的类型
public:
    SymbolEntry(Symbol t) : Entry("", 0, 0), type(t) {}
    Symbol get_type() { return type; }  // 获取符号的类型
};

// 对象符号表，用于存储变量和其类型的映射关系
// 支持作用域嵌套，是语义分析的重要数据结构
static SymbolTable<Symbol, Entry> object_table;

// 辅助函数：检查类型是否兼容
// 在COOL中，类型兼容是指子类型可以赋值给父类型
bool conforms_to(Symbol type1, Symbol type2) {
    // 如果两个类型相同，则兼容
    if (type1 == type2) return true;
    // 如果两个类型都是SELF_TYPE，则兼容
    if (type1 == SELF_TYPE && type2 == SELF_TYPE) return true;
    // 如果type1是SELF_TYPE，则替换为当前类
    if (type1 == SELF_TYPE) type1 = current_class;
    // 如果type2是SELF_TYPE，则替换为当前类
    if (type2 == SELF_TYPE) type2 = current_class;
    // 检查type1是否是type2的子类
    return classtable->is_subclass(type1, type2);
}

// 辅助函数：获取两个类型的最小公共祖先
// 用于确定表达式类型的公共超类型，如if表达式的类型
Symbol join(Symbol type1, Symbol type2) {
    // 如果两个类型都是SELF_TYPE，则返回SELF_TYPE
    if (type1 == SELF_TYPE && type2 == SELF_TYPE) return SELF_TYPE;
    // 如果type1是SELF_TYPE，则替换为当前类
    if (type1 == SELF_TYPE) type1 = current_class;
    // 如果type2是SELF_TYPE，则替换为当前类
    if (type2 == SELF_TYPE) type2 = current_class;
    // 返回两个类型的最小公共祖先
    return classtable->least_common_ancestor(type1, type2);
}

// 辅助函数：查找方法
// 在类及其父类中查找指定名称的方法
Feature lookup_method(Symbol class_name, Symbol method_name) {
    // 查找类
    Class_ c = classtable->lookup_class(class_name);
    if (!c) return NULL;
    
    // 获取类的特性列表
    Features features = get_class_features(c);
    // 遍历特性列表，查找方法
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        method_class* method = dynamic_cast<method_class*>(f);
        // 如果找到同名方法，返回该方法
        if (method && get_method_name(method) == method_name) {
            return method;
        }
    }
    
    // 如果在当前类中找不到，递归查找父类
    Symbol parent = get_class_parent(c);
    if (parent != No_class) {
        return lookup_method(parent, method_name);
    }
    
    return NULL;
}

// 辅助函数：查找属性
// 在类及其父类中查找指定名称的属性
Feature lookup_attribute(Symbol class_name, Symbol attr_name) {
    // 查找类
    Class_ c = classtable->lookup_class(class_name);
    if (!c) return NULL;
    
    // 获取类的特性列表
    Features features = get_class_features(c);
    // 遍历特性列表，查找属性
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        attr_class* attr = dynamic_cast<attr_class*>(f);
        // 如果找到同名属性，返回该属性
        if (attr && get_attr_name(attr) == attr_name) {
            return attr;
        }
    }
    
    // 如果在当前类中找不到，递归查找父类
    Symbol parent = get_class_parent(c);
    if (parent != No_class) {
        return lookup_attribute(parent, attr_name);
    }
    
    return NULL;
}

// 实现program_class::semant()方法
// 这是语义分析的入口点，负责整个程序的语义分析
void program_class::semant()
{
    // 初始化常量
    // 这一步初始化COOL语言的基本类型和常量
    initialize_constants();
    
    // 初始化对象符号表 - 首先进入作用域
    // 对象符号表用于存储变量和其类型的映射关系
    if (semant_debug) {
        cerr << "Entering global scope" << endl;
    }
    object_table.enterscope();
    
    // 创建类表
    // 类表是语义分析的核心数据结构，存储了所有类的信息及其继承关系
    ::classtable = new ClassTable(classes);
    
    // 检查所有类的特性
    // 遍历所有类，检查每个类的方法和属性定义
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        current_class = get_class_name(classes->nth(i));
        if (semant_debug) {
            cerr << "Checking class features for " << current_class << endl;
        }
        // 检查类的特性（方法和属性）
        classtable->check_class_features(classes->nth(i));
    }
    
    // 退出全局作用域
    if (semant_debug) {
        cerr << "Exiting global scope" << endl;
    }
    object_table.exitscope();
    
    // 如果有错误，退出
    // 如果语义分析过程中发现错误，则终止编译
    if (classtable->errors()) {
        cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}

// 实现各种表达式类型的semant方法
// 每个表达式类都有自己的semant方法，用于进行类型检查和类型推断

// 常量表达式：整型常量
Symbol int_const_class::semant()
{
    // 设置类型为Int
    set_type(Int);
    return Int;
}

// 常量表达式：布尔常量
Symbol bool_const_class::semant()
{
    // 设置类型为Bool
    set_type(Bool);
    return Bool;
}

// 常量表达式：字符串常量
Symbol string_const_class::semant()
{
    // 设置类型为String
    set_type(Str);
    return Str;
}

// 变量表达式
// 处理变量引用，如变量名
Symbol object_class::semant()
{
    // 查找变量在对象符号表中的类型
    // 首先在当前作用域中查找变量
    SymbolEntry* entry = (SymbolEntry*)object_table.lookup(name);
    if (entry) {
        Symbol obj_type = entry->get_type();
        set_type(obj_type);
        return obj_type;
    }
    
    // 如果在对象符号表中找不到，查找属性
    // 变量可能是类的属性
    Feature attr = lookup_attribute(current_class, name);
    if (attr) {
        Symbol attr_type = get_attr_type_decl(attr);
        set_type(attr_type);
        return attr_type;
    }
    
    // 如果都找不到，报错
    // 变量未定义，这是语义错误
    classtable->semant_error(current_class_obj->get_filename(), this) << "Undeclared identifier " << name << "." << endl;
    set_type(Object);
    return Object;
}

// 赋值表达式
// 处理变量赋值，如 x = expr
Symbol assign_class::semant()
{
    // 检查变量是否已声明
    SymbolEntry* entry = (SymbolEntry*)object_table.lookup(name);
    Symbol var_type;
    if (!entry) {
        // 查找属性
        // 变量可能是类的属性
        Feature attr = lookup_attribute(current_class, name);
        if (!attr) {
            // 变量未定义，报错
            classtable->semant_error(current_class_obj->get_filename(), this) << "Undeclared identifier " << name << "." << endl;
            set_type(Object);
            return Object;
        }
        var_type = get_attr_type_decl(attr);
    } else {
        // 变量在符号表中找到，获取其类型
        var_type = entry->get_type();
    }
    
    // 检查表达式的类型
    Symbol expr_type = expr->semant();
    
    // 检查类型是否兼容
    // 赋值表达式的类型必须与变量的类型兼容
    if (!conforms_to(expr_type, var_type)) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Type " << expr_type 
            << " of assigned expression does not conform to declared type " 
            << var_type << " of identifier " << name << "." << endl;
    }
    
    // 赋值表达式的类型是表达式的类型
    set_type(expr_type);
    return expr_type;
}

// new表达式
// 处理对象创建，如 new Type
Symbol new__class::semant()
{
    // 检查类型是否存在
    if (type_name == SELF_TYPE) {
        // SELF_TYPE是特殊类型，表示当前对象的类型
        set_type(SELF_TYPE);
        return SELF_TYPE;
    }
    
    // 查找类型是否存在
    Class_ c = classtable->lookup_class(type_name);
    if (!c) {
        // 类型未定义，报错
        classtable->semant_error(current_class_obj->get_filename(), this) << "new is used with undefined class " 
            << type_name << "." << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为指定的类型
    set_type(type_name);
    return type_name;
}

// isvoid表达式
// 处理isvoid操作，检查表达式是否为void
Symbol isvoid_class::semant()
{
    // 检查表达式的类型
    e1->semant();
    // isvoid表达式的结果总是Bool类型
    set_type(Bool);
    return Bool;
}

// no_expr表达式
// 表示没有表达式，如方法没有返回值
Symbol no_expr_class::semant()
{
    // 设置类型为No_type
    set_type(No_type);
    return No_type;
}

// 算术表达式：加法
// 处理加法表达式，如 e1 + e2
Symbol plus_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    // COOL中算术操作只支持Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " + " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Int
    set_type(Int);
    return Int;
}

// 算术表达式：减法
// 处理减法表达式，如 e1 - e2
Symbol sub_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " - " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Int
    set_type(Int);
    return Int;
}

// 算术表达式：乘法
// 处理乘法表达式，如 e1 * e2
Symbol mul_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " * " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Int
    set_type(Int);
    return Int;
}

// 算术表达式：除法
// 处理除法表达式，如 e1 / e2
Symbol divide_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " / " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Int
    set_type(Int);
    return Int;
}

// 取负表达式
// 处理取负操作，如 ~e1
Symbol neg_class::semant()
{
    // 获取操作数的类型
    Symbol e1_type = e1->semant();
    
    // 检查操作数是否是Int类型
    if (e1_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Argument of '~' has type " 
            << e1_type << " instead of Int." << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Int
    set_type(Int);
    return Int;
}

// 比较表达式：小于
// 处理小于比较，如 e1 < e2
Symbol lt_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    // COOL中比较操作只支持Int、String和Bool类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " < " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Bool
    set_type(Bool);
    return Bool;
}

// 比较表达式：相等
// 处理相等比较，如 e1 = e2
Symbol eq_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否是基本类型
    // COOL中基本类型（Int、String、Bool）只能与同类型比较
    if ((e1_type == Int || e1_type == Str || e1_type == Bool) &&
        (e2_type == Int || e2_type == Str || e2_type == Bool) &&
        e1_type != e2_type) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Illegal comparison with a basic type." << endl;
    }
    
    // 设置类型为Bool
    set_type(Bool);
    return Bool;
}

// 比较表达式：小于等于
// 处理小于等于比较，如 e1 <= e2
Symbol leq_class::semant()
{
    // 获取两个操作数的类型
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " <= " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Bool
    set_type(Bool);
    return Bool;
}

// 逻辑表达式：非
// 处理逻辑非操作，如 not e1
Symbol comp_class::semant()
{
    // 获取操作数的类型
    Symbol e1_type = e1->semant();
    
    // 检查操作数是否是Bool类型
    if (e1_type != Bool) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Argument of 'not' has type " 
            << e1_type << " instead of Bool." << endl;
        set_type(Object);
        return Object;
    }
    
    // 设置类型为Bool
    set_type(Bool);
    return Bool;
}

// 控制流表达式

// if表达式
// 处理条件分支，如 if pred then then_exp else else_exp fi
Symbol cond_class::semant()
{
    // 获取条件表达式的类型
    Symbol pred_type = pred->semant();
    
    // 检查条件表达式是否是Bool类型
    if (pred_type != Bool) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Predicate of 'if' does not have type Bool." << endl;
    }
    
    // 获取then分支和else分支的类型
    Symbol then_type = then_exp->semant();
    Symbol else_type = else_exp->semant();
    
    // if表达式的类型是then分支和else分支的最小公共祖先
    // 这是类型推断的关键步骤
    Symbol result_type = join(then_type, else_type);
    set_type(result_type);
    return result_type;
}

// loop表达式
// 处理循环，如 while pred loop body pool
Symbol loop_class::semant()
{
    // 获取条件表达式的类型
    Symbol pred_type = pred->semant();
    
    // 检查条件表达式是否是Bool类型
    if (pred_type != Bool) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Loop condition does not have type Bool." << endl;
    }
    
    // 检查循环体
    body->semant();
    
    // loop表达式的类型是Object
    // 在COOL中，循环表达式的类型总是Object
    set_type(Object);
    return Object;
}

// block表达式
// 处理代码块，如 { e1; e2; ...; en; }
Symbol block_class::semant()
{
    // 默认返回Object类型
    Symbol last_type = Object;
    
    // 依次检查每个表达式
    for (int i = body->first(); body->more(i); i = body->next(i)) {
        Expression expr = body->nth(i);
        last_type = expr->semant();
    }
    
    // block表达式的类型是最后一个表达式的类型
    set_type(last_type);
    return last_type;
}

// let表达式
// 处理局部变量绑定，如 let x : Type <- init in body
Symbol let_class::semant()
{
    // 保存当前对象符号表
    // let表达式引入新的作用域
    object_table.enterscope();
    
    // 检查初始化表达式
    Symbol init_type = No_type;
    if (init) {
        init_type = init->semant();
        // 检查初始化表达式类型是否与变量类型兼容
        if (!conforms_to(init_type, type_decl)) {
            classtable->semant_error(current_class_obj->get_filename(), this) << "Inferred type " << init_type 
                << " of initialization of " << identifier 
                << " does not conform to declared type " << type_decl << "." << endl;
        }
    }
    
    // 将变量添加到对象符号表
    // 在新作用域中添加变量
    object_table.addid(identifier, new SymbolEntry(type_decl));
    
    // 检查body表达式
    Symbol body_type = body->semant();
    
    // 恢复对象符号表
    // 退出let表达式的作用域
    object_table.exitscope();
    
    // let表达式的类型是body表达式的类型
    set_type(body_type);
    return body_type;
}

// case表达式
// 处理模式匹配，如 case expr of A : x => e1; B : y => e2; ... esac
Symbol typcase_class::semant()
{
    // 检查case表达式的类型
    Symbol expr_type = expr->semant();
    
    // 保存当前对象符号表
    object_table.enterscope();
    
    // 结果类型初始化为No_type
    Symbol result_type = No_type;
    // 用于检查重复的case类型
    std::set<Symbol> case_types;
    
    // 依次检查每个分支
    for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
        Case branch = cases->nth(i);
        
        // 获取分支的类型和变量名
        Symbol branch_type = get_branch_type(branch);
        Symbol branch_name = get_branch_name(branch);
        Expression branch_expr = get_branch_expr(branch);
        
        // 检查case类型是否重复
        // COOL不允许case表达式中有重复的类型
        if (case_types.find(branch_type) != case_types.end()) {
            classtable->semant_error(current_class_obj->get_filename(), this) << "Duplicate branch " << branch_type << " in case statement." << endl;
        } else {
            case_types.insert(branch_type);
        }
        
        // 将变量添加到对象符号表
        // 每个分支引入新的作用域
        object_table.enterscope();
        object_table.addid(branch_name, new SymbolEntry(branch_type));
        
        // 检查分支表达式
        Symbol branch_expr_type = branch_expr->semant();
        
        // 更新结果类型
        // case表达式的类型是所有分支类型的最小公共祖先
        if (result_type == No_type) {
            result_type = branch_expr_type;
        } else {
            result_type = join(result_type, branch_expr_type);
        }
        
        // 恢复对象符号表
        // 退出分支的作用域
        object_table.exitscope();
    }
    
    // 恢复对象符号表
    // 退出case表达式的作用域
    object_table.exitscope();
    
    // 如果没有分支，结果是Object
    if (result_type == No_type) {
        result_type = Object;
    }
    
    // 设置case表达式的类型
    set_type(result_type);
    return result_type;
}

// 方法调用表达式

// 静态分派表达式
// 处理静态方法调用，如 expr@Type.method(args)
Symbol static_dispatch_class::semant()
{
    // 检查表达式类型
    Symbol expr_type = expr->semant();
    
    // 检查指定的类型是否存在
    if (type_name != SELF_TYPE && !classtable->lookup_class(type_name)) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Type " << type_name 
            << " of static dispatch is undefined." << endl;
        set_type(Object);
        return Object;
    }
    
    // 检查表达式类型是否是指定类型的子类
    // 静态分派要求表达式类型是指定类型的子类
    if (expr_type != SELF_TYPE && !conforms_to(expr_type, type_name)) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Expression type " << expr_type 
            << " does not conform to declared static dispatch type " << type_name << "." << endl;
    }
    
    // 查找方法
    Feature method = lookup_method(type_name, name);
    if (!method) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Dispatch to undefined method " 
            << name << "." << endl;
        set_type(Object);
        return Object;
    }
    
    // 获取方法的参数类型和返回类型
    Formals formals = get_method_formals(method);
    Symbol return_type = get_method_return_type(method);
    
    // 检查参数数量
    if (list_length(formals) != list_length(actual)) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Method " << name 
            << " called with wrong number of arguments." << endl;
        set_type(Object);
        return Object;
    }
    
    // 检查每个参数的类型
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        Expression arg = actual->nth(i);
        Formal formal = formals->nth(i);
        
        Symbol arg_type = arg->semant();
        Symbol formal_type = get_formal_type_decl(formal);
        
        // 检查参数类型是否兼容
        if (!conforms_to(arg_type, formal_type)) {
            classtable->semant_error(current_class_obj->get_filename(), this) << "In call of method " << name 
                << ", type " << arg_type << " of parameter " << get_formal_name(formal) 
                << " does not conform to declared type " << formal_type << "." << endl;
        }
    }
    
    // 如果返回类型是SELF_TYPE，则返回表达式的类型
    if (return_type == SELF_TYPE) {
        if (expr_type == SELF_TYPE) {
            set_type(SELF_TYPE);
            return SELF_TYPE;
        } else {
            set_type(expr_type);
            return expr_type;
        }
    } else {
        set_type(return_type);
        return return_type;
    }
}

// 动态分派表达式
// 处理动态方法调用，如 expr.method(args)
Symbol dispatch_class::semant() {
    // 检查表达式类型
    Symbol expr_type = expr->semant();
    
    // 如果表达式类型是SELF_TYPE，则使用当前类
    // SELF_TYPE是特殊类型，表示当前对象的类型
    Symbol dispatch_type = expr_type;
    if (dispatch_type == SELF_TYPE) {
        dispatch_type = current_class;
    }
    
    // 查找方法
    Feature method = lookup_method(dispatch_type, name);
    if (!method) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Dispatch to undefined method " 
            << name << "." << endl;
        set_type(Object);
        return Object;
    }
    
    // 获取方法的参数类型和返回类型
    Formals formals = get_method_formals(method);
    Symbol return_type = get_method_return_type(method);
    
    // 检查参数数量
    if (list_length(formals) != list_length(actual)) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Method " << name 
            << " called with wrong number of arguments." << endl;
        set_type(Object);
        return Object;
    }
    
    // 检查每个参数的类型
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        Expression arg = actual->nth(i);
        Formal formal = formals->nth(i);
        
        Symbol arg_type = arg->semant();
        Symbol formal_type = get_formal_type_decl(formal);
        
        // 检查参数类型是否兼容
        if (!conforms_to(arg_type, formal_type)) {
            classtable->semant_error(current_class_obj->get_filename(), this) << "In call of method " << name 
                << ", type " << arg_type << " of parameter " << get_formal_name(formal) 
                << " does not conform to declared type " << formal_type << "." << endl;
        }
    }
    
    // 如果返回类型是SELF_TYPE，则返回表达式的类型
    if (return_type == SELF_TYPE) {
        if (expr_type == SELF_TYPE) {
            set_type(SELF_TYPE);
            return SELF_TYPE;
        } else {
            set_type(expr_type);
            return expr_type;
        }
    } else {
        set_type(return_type);
        return return_type;
    }
}

// ClassTable类的实现
// ClassTable是语义分析的核心数据结构，存储了所有类的信息及其继承关系

// 构造函数
ClassTable::ClassTable(Classes classes) : semant_errors(0), error_stream(cerr) {
    // 首先安装基本类
    install_basic_classes();
    
    // 检查类定义的合法性
    // 1. 检查是否有重复的类名
    // 2. 检查父类是否存在
    // 3. 检查是否继承自基本类
    // 4. 检查是否有Main类和main方法
    
    // 检查类名是否重复
    std::set<Symbol> class_names;
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        Class_ c = classes->nth(i);
        Symbol name = get_class_name(c);
        
        if (class_names.find(name) != class_names.end()) {
            semant_error(c->get_filename(), c) << "Class " << name << " was previously defined." << endl;
        } else {
            class_names.insert(name);
        }
    }
    
    // 添加类到类表
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        Class_ c = classes->nth(i);
        Symbol name = get_class_name(c);
        Symbol parent = get_class_parent(c);
        
        // 检查父类是否存在
        if (parent != No_class && class_names.find(parent) == class_names.end()) {
            semant_error(c->get_filename(), c) << "Class " << name << " inherits from an undefined class " 
                << parent << "." << endl;
        }
        
        // 检查是否继承自基本类
        if (parent == Int || parent == Str || parent == Bool) {
            semant_error(c->get_filename(), c) << "Class " << name << " cannot inherit class " 
                << parent << "." << endl;
        }
        
        // 添加到类表
        class_map[name] = c;
    }
    
    // 检查是否有Main类
    if (class_map.find(Main) == class_map.end()) {
        semant_error() << "Class Main is not defined." << endl;
    } else {
        // 检查Main类是否有main方法
        Class_ main_class = class_map[Main];
        Feature main_method = lookup_method(Main, main_meth);
        if (!main_method) {
            semant_error(main_class->get_filename(), main_class) << "No 'main' method in class Main." << endl;
        }
    }
}

// 安装基本类
// COOL语言有五个基本类：Object, IO, Int, Bool, String
void ClassTable::install_basic_classes() {
    // 安装Object类
    Class_ Object_class = 
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, Nil, single_Formals(formal(arg, Str)), 
								    no_expr())),
					       single_Features(method(type_name, Str, single_Formals(formal(arg, Object)), 
								    no_expr()))),
			       single_Features(method(copy, SELF_TYPE, nil_Formals(), no_expr()))),
	       filename);
    
    // 安装IO类
    Class_ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       single_Features(method(out_string, SELF_TYPE, single_Formals(formal(arg, Str)), 
								    no_expr())),
					       single_Features(method(out_int, SELF_TYPE, single_Formals(formal(arg, Int)), 
								    no_expr()))),
			       append_Features(
					       single_Features(method(in_string, Str, nil_Formals(), no_expr())),
					       single_Features(method(in_int, Int, nil_Formals(), no_expr())))),
	       filename);
    
    // 安装Int类
    Class_ Int_class = 
	class_(Int, 
	       Object,
	       single_Features(attr(val, Int, int_const(0))),
	       filename);
    
    // 安装Bool类
    Class_ Bool_class = 
	class_(Bool, 
	       Object,
	       single_Features(attr(val, Bool, bool_const(false))),
	       filename);
    
    // 安装String类
    Class_ Str_class =
	class_(Str, 
	       Object,
	       single_Features(attr(val, Int, int_const(0))),
	       single_Features(attr(str_field, Str, no_expr())),
	       single_Features(method(length, Int, nil_Formals(), no_expr())),
	       single_Features(method(concat, Str, single_Formals(formal(arg, Str)), no_expr())),
	       filename);
    
    // 添加到类表
    class_map[Object] = Object_class;
    class_map[IO] = IO_class;
    class_map[Int] = Int_class;
    class_map[Bool] = Bool_class;
    class_map[Str] = Str_class;
}

// 检查类的特性
// 检查类中的方法和属性定义的合法性
void ClassTable::check_class_features(Class_ c) {
    // 设置当前类和当前类对象
    current_class = get_class_name(c);
    current_class_obj = c;
    
    // 进入类的作用域
    object_table.enterscope();
    
    // 获取类的特性
    Features features = get_class_features(c);
    
    // 检查方法重写
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        method_class* method = dynamic_cast<method_class*>(f);
        if (method) {
            Symbol method_name = get_method_name(method);
            
            // 查找父类中的同名方法
            Symbol parent = get_class_parent(c);
            if (parent != No_class) {
                Feature parent_method = lookup_method(parent, method_name);
                if (parent_method) {
                    // 检查方法重写的合法性
                    check_method_override(c, method, parent_method);
                }
            }
        }
    }
    
    // 检查属性继承
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        attr_class* attr = dynamic_cast<attr_class*>(f);
        if (attr) {
            Symbol attr_name = get_attr_name(attr);
            
            // 查找父类中的同名属性
            Symbol parent = get_class_parent(c);
            if (parent != No_class) {
                Feature parent_attr = lookup_attribute(parent, attr_name);
                if (parent_attr) {
                    // 检查属性继承的合法性
                    check_attribute_inheritance(c, attr, parent_attr);
                }
            }
        }
    }
    
    // 检查方法和属性的定义
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        method_class* method = dynamic_cast<method_class*>(f);
        if (method) {
            // 检查方法定义
            check_method_definition(c, method);
        } else {
            attr_class* attr = dynamic_cast<attr_class*>(f);
            if (attr) {
                // 检查属性定义
                check_attribute_definition(c, attr);
            }
        }
    }
    
    // 退出类的作用域
    object_table.exitscope();
}

// 检查方法重写的合法性
void ClassTable::check_method_override(Class_ child_class, Feature child_method, Feature parent_method) {
    Symbol child_name = get_method_name(child_method);
    Symbol parent_name = get_method_name(parent_method);
    
    // 检查返回类型
    Symbol child_return_type = get_method_return_type(child_method);
    Symbol parent_return_type = get_method_return_type(parent_method);
    
    // 子类方法的返回类型必须与父类方法的返回类型相同
    if (child_return_type != parent_return_type) {
        semant_error(child_class->get_filename(), child_method) << "In redefined method " << child_name 
            << ", return type " << child_return_type 
            << " is different from original return type " << parent_return_type << "." << endl;
    }
    
    // 检查参数数量
    Formals child_formals = get_method_formals(child_method);
    Formals parent_formals = get_method_formals(parent_method);
    
    if (list_length(child_formals) != list_length(parent_formals)) {
        semant_error(child_class->get_filename(), child_method) << "In redefined method " << child_name 
            << ", number of formals " << list_length(child_formals)
            << " is different from original number of formals " << list_length(parent_formals) << "." << endl;
    }
    
    // 检查参数类型
    for (int i = child_formals->first(); child_formals->more(i) && parent_formals->more(i); 
         i = child_formals->next(i), i = parent_formals->next(i)) {
        Formal child_formal = child_formals->nth(i);
        Formal parent_formal = parent_formals->nth(i);
        
        Symbol child_type = get_formal_type_decl(child_formal);
        Symbol parent_type = get_formal_type_decl(parent_formal);
        
        // 子类方法的参数类型必须与父类方法的参数类型相同
        if (child_type != parent_type) {
            semant_error(child_class->get_filename(), child_method) << "In redefined method " << child_name 
                << ", parameter type " << child_type << " of parameter " << get_formal_name(child_formal)
                << " is different from original type " << parent_type << "." << endl;
        }
    }
}

// 检查属性继承的合法性
void ClassTable::check_attribute_inheritance(Class_ child_class, Feature child_attr, Feature parent_attr) {
    Symbol child_name = get_attr_name(child_attr);
    Symbol parent_name = get_attr_name(parent_attr);
    
    // 子类不能重新定义父类的属性
    semant_error(child_class->get_filename(), child_attr) << "Attribute " << child_name 
        << " is an attribute of an inherited class." << endl;
}

// 检查方法定义的合法性
void ClassTable::check_method_definition(Class_ c, Feature method) {
    Symbol method_name = get_method_name(method);
    current_method = method_name;
    
    // 进入方法的作用域
    object_table.enterscope();
    
    // 添加形式参数到符号表
    Formals formals = get_method_formals(method);
    for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
        Formal formal = formals->nth(i);
        Symbol formal_name = get_formal_name(formal);
        Symbol formal_type = get_formal_type_decl(formal);
        
        // 检查参数名是否重复
        SymbolEntry* entry = (SymbolEntry*)object_table.lookup(formal_name);
        if (entry) {
            semant_error(c->get_filename(), formal) << "Formal parameter " << formal_name 
                << " is multiply defined." << endl;
        } else {
            // 添加参数到符号表
            object_table.addid(formal_name, new SymbolEntry(formal_type));
        }
    }
    
    // 检查方法体
    Expression expr = get_method_expr(method);
    Symbol expr_type = expr->semant();
    
    // 检查返回类型
    Symbol return_type = get_method_return_type(method);
    if (return_type != SELF_TYPE && !conforms_to(expr_type, return_type)) {
        semant_error(c->get_filename(), method) << "Inferred return type " << expr_type 
            << " of method " << method_name 
            << " does not conform to declared return type " << return_type << "." << endl;
    }
    
    // 退出方法的作用域
    object_table.exitscope();
    
    current_method = NULL;
}

// 检查属性定义的合法性
void ClassTable::check_attribute_definition(Class_ c, Feature attr) {
    Symbol attr_name = get_attr_name(attr);
    Symbol attr_type = get_attr_type_decl(attr);
    Expression init = get_attr_init(attr);
    
    // 检查属性名是否与类名相同
    if (attr_name == get_class_name(c)) {
        semant_error(c->get_filename(), attr) << "Attribute " << attr_name 
            << " has the same name as the class." << endl;
    }
    
    // 检查属性名是否与方法名相同
    Features features = get_class_features(c);
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        method_class* method = dynamic_cast<method_class*>(f);
        if (method && get_method_name(method) == attr_name) {
            semant_error(c->get_filename(), attr) << "Attribute " << attr_name 
                << " has the same name as a method." << endl;
        }
    }
    
    // 检查初始化表达式
    if (init) {
        Symbol init_type = init->semant();
        // 检查初始化表达式类型是否与属性类型兼容
        if (!conforms_to(init_type, attr_type)) {
            semant_error(c->get_filename(), attr) << "Inferred type " << init_type 
                << " of initialization of attribute " << attr_name 
                << " does not conform to declared type " << attr_type << "." << endl;
        }
    }
    
    // 添加属性到符号表
    object_table.addid(attr_name, new SymbolEntry(attr_type));
}

// 查找类
Class_ ClassTable::lookup_class(Symbol name) {
    if (class_map.find(name) != class_map.end()) {
        return class_map[name];
    }
    return NULL;
}

// 检查是否是子类
bool ClassTable::is_subclass(Symbol child, Symbol parent) {
    if (child == parent) return true;
    
    Class_ child_class = lookup_class(child);
    if (!child_class) return false;
    
    Symbol child_parent = get_class_parent(child_class);
    if (child_parent == No_class) return false;
    
    return is_subclass(child_parent, parent);
}

// 计算最小公共祖先
Symbol ClassTable::least_common_ancestor(Symbol type1, Symbol type2) {
    if (type1 == type2) return type1;
    
    // 收集type1的所有祖先
    std::set<Symbol> ancestors1;
    Symbol current = type1;
    while (current != No_class) {
        ancestors1.insert(current);
        Class_ current_class = lookup_class(current);
        if (!current_class) break;
        current = get_class_parent(current_class);
    }
    
    // 查找type2的第一个在ancestors1中的祖先
    current = type2;
    while (current != No_class) {
        if (ancestors1.find(current) != ancestors1.end()) {
            return current;
        }
        Class_ current_class = lookup_class(current);
        if (!current_class) break;
        current = get_class_parent(current_class);
    }
    
    return Object;
}

// 错误报告
ostream& ClassTable::semant_error() {
    return semant_errors++;
}

ostream& ClassTable::semant_error(Class_ c) {
    return semant_error(c->get_filename(), c);
}

ostream& ClassTable::semant_error(Symbol filename, tree_node *t) {
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

// 检查是否有错误
bool ClassTable::errors() {
    return semant_errors;
}

// 初始化常量
void initialize_constants() {
    arg = idtable.add_string("arg");
    arg2 = idtable.add_string("arg2");
    Bool = idtable.add_string("Bool");
    concat = idtable.add_string("concat");
    cool_abort = idtable.add_string("abort");
    copy = idtable.add_string("copy");
    Int = idtable.add_string("Int");
    in_int = idtable.add_string("in_int");
    in_string = idtable.add_string("in_string");
    IO = idtable.add_string("IO");
    length = idtable.add_string("length");
    Main = idtable.add_string("Main");
    main_meth = idtable.add_string("main");
    No_class = idtable.add_string("_no_class");
    No_type = idtable.add_string("_no_type");
    Object = idtable.add_string("Object");
    out_int = idtable.add_string("out_int");
    out_string = idtable.add_string("out_string");
    prim_slot = idtable.add_string("_prim_slot");
    self = idtable.add_string("self");
    SELF_TYPE = idtable.add_string("SELF_TYPE");
    Str = idtable.add_string("String");
    str_field = idtable.add_string("str_field");
    substr = idtable.add_string("substr");
    type_name = idtable.add_string("type_name");
    val = idtable.add_string("val");
}