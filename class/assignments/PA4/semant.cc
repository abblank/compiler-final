

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <set>
#include "semant.h"
#include "utilities.h"

// 辅助函数，用于访问类的protected成员
Symbol get_class_name(Class_ c) {
    class__class* class_ptr = dynamic_cast<class__class*>(c);
    if (class_ptr) {
        return class_ptr->get_name();
    }
    return NULL;
}

Symbol get_class_parent(Class_ c) {
    class__class* class_ptr = dynamic_cast<class__class*>(c);
    if (class_ptr) {
        return class_ptr->get_parent();
    }
    return NULL;
}

Features get_class_features(Class_ c) {
    class__class* class_ptr = dynamic_cast<class__class*>(c);
    if (class_ptr) {
        return class_ptr->get_features();
    }
    return NULL;
}

Symbol get_method_name(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_name();
    }
    return NULL;
}

Symbol get_method_return_type(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_return_type();
    }
    return NULL;
}

Formals get_method_formals(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_formals();
    }
    return NULL;
}

Expression get_method_expr(Feature f) {
    method_class* method = dynamic_cast<method_class*>(f);
    if (method) {
        return method->get_expr();
    }
    return NULL;
}

Symbol get_attr_name(Feature f) {
    attr_class* attr = dynamic_cast<attr_class*>(f);
    if (attr) {
        return attr->get_name();
    }
    return NULL;
}

Symbol get_attr_type_decl(Feature f) {
    attr_class* attr = dynamic_cast<attr_class*>(f);
    if (attr) {
        return attr->get_type_decl();
    }
    return NULL;
}

Expression get_attr_init(Feature f) {
    attr_class* attr = dynamic_cast<attr_class*>(f);
    if (attr) {
        return attr->get_init();
    }
    return NULL;
}

Symbol get_formal_name(Formal f) {
    formal_class* formal = dynamic_cast<formal_class*>(f);
    if (formal) {
        return formal->get_name();
    }
    return NULL;
}

Symbol get_formal_type_decl(Formal f) {
    formal_class* formal = dynamic_cast<formal_class*>(f);
    if (formal) {
        return formal->get_type_decl();
    }
    return NULL;
}

Symbol get_branch_type(Case branch) {
    branch_class* bc = dynamic_cast<branch_class*>(branch);
    if (bc) {
        return bc->get_type_decl();
    }
    return NULL;
}

Symbol get_branch_name(Case branch) {
    branch_class* bc = dynamic_cast<branch_class*>(branch);
    if (bc) {
        return bc->get_name();
    }
    return NULL;
}

Expression get_branch_expr(Case branch) {
    branch_class* bc = dynamic_cast<branch_class*>(branch);
    if (bc) {
        return bc->get_expr();
    }
    return NULL;
}

// 全局ClassTable指针，用于表达式类型检查
static ClassTable *classtable = NULL;



// 为Formals类型添加特化版本
int list_length(Formals formals) {
    int count = 0;
    if (formals) {
        for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
            count++;
        }
    }
    return count;
}

extern int semant_debug;
extern char *curr_filename;

// 当前类
static Symbol current_class = NULL;

// 当前类对象
static Class_ current_class_obj = NULL;

// 当前方法
static Symbol current_method = NULL;

// 简单的Entry类，用于存储Symbol信息
class SymbolEntry : public Entry {
private:
    Symbol type;
public:
    SymbolEntry(Symbol t) : Entry("", 0, 0), type(t) {}
    Symbol get_type() { return type; }
};

// 对象符号表
static SymbolTable<Symbol, Entry> object_table;

// 辅助函数：检查类型是否兼容
bool conforms_to(Symbol type1, Symbol type2) {
    if (type1 == type2) return true;
    if (type1 == SELF_TYPE && type2 == SELF_TYPE) return true;
    if (type1 == SELF_TYPE) type1 = current_class;
    if (type2 == SELF_TYPE) type2 = current_class;
    return classtable->is_subclass(type1, type2);
}

// 辅助函数：获取最小公共祖先
Symbol join(Symbol type1, Symbol type2) {
    if (type1 == SELF_TYPE && type2 == SELF_TYPE) return SELF_TYPE;
    if (type1 == SELF_TYPE) type1 = current_class;
    if (type2 == SELF_TYPE) type2 = current_class;
    return classtable->least_common_ancestor(type1, type2);
}

// 辅助函数：查找方法
Feature lookup_method(Symbol class_name, Symbol method_name) {
    Class_ c = classtable->lookup_class(class_name);
    if (!c) return NULL;
    
    Features features = get_class_features(c);
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        method_class* method = dynamic_cast<method_class*>(f);
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
Feature lookup_attribute(Symbol class_name, Symbol attr_name) {
    Class_ c = classtable->lookup_class(class_name);
    if (!c) return NULL;
    
    Features features = get_class_features(c);
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        attr_class* attr = dynamic_cast<attr_class*>(f);
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
void program_class::semant()
{
    // 初始化常量
    initialize_constants();
    
    // 初始化对象符号表 - 首先进入作用域
    if (semant_debug) {
        cerr << "Entering global scope" << endl;
    }
    object_table.enterscope();
    
    // 创建类表
    ::classtable = new ClassTable(classes);
    
    // 检查所有类的特性
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        current_class = get_class_name(classes->nth(i));
        if (semant_debug) {
            cerr << "Checking class features for " << current_class << endl;
        }
        classtable->check_class_features(classes->nth(i));
    }
    
    // 退出全局作用域
    if (semant_debug) {
        cerr << "Exiting global scope" << endl;
    }
    object_table.exitscope();
    
    // 如果有错误，退出
    if (classtable->errors()) {
        cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}

// 实现各种表达式类型的semant方法

// 常量表达式
Symbol int_const_class::semant()
{
    set_type(Int);
    return Int;
}

Symbol bool_const_class::semant()
{
    set_type(Bool);
    return Bool;
}

Symbol string_const_class::semant()
{
    set_type(Str);
    return Str;
}

// 变量表达式
Symbol object_class::semant()
{
    // 查找变量在对象符号表中的类型
    SymbolEntry* entry = (SymbolEntry*)object_table.lookup(name);
    if (entry) {
        Symbol obj_type = entry->get_type();
        set_type(obj_type);
        return obj_type;
    }
    
    // 如果在对象符号表中找不到，查找属性
    Feature attr = lookup_attribute(current_class, name);
    if (attr) {
        Symbol attr_type = get_attr_type_decl(attr);
        set_type(attr_type);
        return attr_type;
    }
    
    // 如果都找不到，报错
    classtable->semant_error(current_class_obj->get_filename(), this) << "Undeclared identifier " << name << "." << endl;
    set_type(Object);
    return Object;
}

// 赋值表达式
Symbol assign_class::semant()
{
    // 检查变量是否已声明
    SymbolEntry* entry = (SymbolEntry*)object_table.lookup(name);
    Symbol var_type;
    if (!entry) {
        // 查找属性
        Feature attr = lookup_attribute(current_class, name);
        if (!attr) {
            classtable->semant_error(current_class_obj->get_filename(), this) << "Undeclared identifier " << name << "." << endl;
            set_type(Object);
            return Object;
        }
        var_type = get_attr_type_decl(attr);
    } else {
        var_type = entry->get_type();
    }
    
    // 检查表达式的类型
    Symbol expr_type = expr->semant();
    
    // 检查类型是否兼容
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
Symbol new__class::semant()
{
    // 检查类型是否存在
    if (type_name == SELF_TYPE) {
        set_type(SELF_TYPE);
        return SELF_TYPE;
    }
    
    Class_ c = classtable->lookup_class(type_name);
    if (!c) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "new is used with undefined class " 
            << type_name << "." << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(type_name);
    return type_name;
}

// isvoid表达式
Symbol isvoid_class::semant()
{
    e1->semant();
    set_type(Bool);
    return Bool;
}

// no_expr表达式
Symbol no_expr_class::semant()
{
    set_type(No_type);
    return No_type;
}

// 算术表达式
Symbol plus_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " + " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Int);
    return Int;
}

Symbol sub_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " - " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Int);
    return Int;
}

Symbol mul_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " * " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Int);
    return Int;
}

Symbol divide_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " / " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Int);
    return Int;
}

// 取负表达式
Symbol neg_class::semant()
{
    Symbol e1_type = e1->semant();
    
    // 检查操作数是否是Int类型
    if (e1_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Argument of '~' has type " 
            << e1_type << " instead of Int." << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Int);
    return Int;
}

// 比较表达式
Symbol lt_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " < " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Bool);
    return Bool;
}

Symbol eq_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否是基本类型
    if ((e1_type == Int || e1_type == Str || e1_type == Bool) &&
        (e2_type == Int || e2_type == Str || e2_type == Bool) &&
        e1_type != e2_type) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Illegal comparison with a basic type." << endl;
    }
    
    set_type(Bool);
    return Bool;
}

Symbol leq_class::semant()
{
    Symbol e1_type = e1->semant();
    Symbol e2_type = e2->semant();
    
    // 检查两个操作数是否都是Int类型
    if (e1_type != Int || e2_type != Int) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "non-Int arguments: " 
            << e1_type << " <= " << e2_type << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Bool);
    return Bool;
}

// 逻辑表达式
Symbol comp_class::semant()
{
    Symbol e1_type = e1->semant();
    
    // 检查操作数是否是Bool类型
    if (e1_type != Bool) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Argument of 'not' has type " 
            << e1_type << " instead of Bool." << endl;
        set_type(Object);
        return Object;
    }
    
    set_type(Bool);
    return Bool;
}

// 控制流表达式

// if表达式
Symbol cond_class::semant()
{
    Symbol pred_type = pred->semant();
    
    // 检查条件表达式是否是Bool类型
    if (pred_type != Bool) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Predicate of 'if' does not have type Bool." << endl;
    }
    
    Symbol then_type = then_exp->semant();
    Symbol else_type = else_exp->semant();
    
    // if表达式的类型是then分支和else分支的最小公共祖先
    Symbol result_type = join(then_type, else_type);
    set_type(result_type);
    return result_type;
}

// loop表达式
Symbol loop_class::semant()
{
    Symbol pred_type = pred->semant();
    
    // 检查条件表达式是否是Bool类型
    if (pred_type != Bool) {
        classtable->semant_error(current_class_obj->get_filename(), this) << "Loop condition does not have type Bool." << endl;
    }
    
    body->semant();
    
    // loop表达式的类型是Object
    set_type(Object);
    return Object;
}

// block表达式
Symbol block_class::semant()
{
    Symbol last_type = Object;  // 默认返回Object类型
    
    // 依次检查每个表达式
    for (int i = body->first(); body->more(i); i = body->next(i)) {
        Expression expr = body->nth(i);
        last_type = expr->semant();
    }
    
    set_type(last_type);
    return last_type;
}

// let表达式
Symbol let_class::semant()
{
    // 保存当前对象符号表
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
    object_table.addid(identifier, new SymbolEntry(type_decl));
    
    // 检查body表达式
    Symbol body_type = body->semant();
    
    // 恢复对象符号表
    object_table.exitscope();
    
    set_type(body_type);
    return body_type;
}

// case表达式
Symbol typcase_class::semant()
{
    // 检查case表达式的类型
    Symbol expr_type = expr->semant();
    
    // 保存当前对象符号表
    object_table.enterscope();
    
    Symbol result_type = No_type;
    std::set<Symbol> case_types;  // 用于检查重复的case类型
    
    // 依次检查每个分支
    for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
        Case branch = cases->nth(i);
        
        // 获取分支的类型和变量名
        Symbol branch_type = get_branch_type(branch);
        Symbol branch_name = get_branch_name(branch);
        Expression branch_expr = get_branch_expr(branch);
        
        // 检查case类型是否重复
        if (case_types.find(branch_type) != case_types.end()) {
            classtable->semant_error(current_class_obj->get_filename(), this) << "Duplicate branch " << branch_type << " in case statement." << endl;
        } else {
            case_types.insert(branch_type);
        }
        
        // 将变量添加到对象符号表
        object_table.enterscope();
        object_table.addid(branch_name, new SymbolEntry(branch_type));
        
        // 检查分支表达式
        Symbol branch_expr_type = branch_expr->semant();
        
        // 更新结果类型
        if (result_type == No_type) {
            result_type = branch_expr_type;
        } else {
            result_type = join(result_type, branch_expr_type);
        }
        
        // 恢复对象符号表
        object_table.exitscope();
    }
    
    // 恢复对象符号表
    object_table.exitscope();
    
    // 如果没有分支，结果是Object
    if (result_type == No_type) {
        result_type = Object;
    }
    
    set_type(result_type);
    return result_type;
}

// 方法调用表达式

// 静态分派表达式
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
// dispatch_class的semant方法实现
Symbol dispatch_class::semant() {
    // 检查表达式类型
    Symbol expr_type = expr->semant();
    
    // 如果表达式类型是SELF_TYPE，则使用当前类
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






ClassTable::ClassTable(Classes classes_) : 
    semant_errors(0), 
    error_stream(cerr),
    classes(classes_)
{
    // 初始化类符号表
    class_table.enterscope();
    
    // 安装基本类
    install_basic_classes();
    
    // 检查用户定义的类
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        Class_ c = classes->nth(i);
        
        // 检查类名是否重复
        if (class_table.probe(get_class_name(c))) {
            semant_error(c->get_filename(), c) << "Class " << get_class_name(c) << " was previously defined." << endl;
        } else {
            Class_ *class_ptr = new Class_(c);
            class_table.addid(get_class_name(c), class_ptr);
        }
    }
    
    // 检查继承关系
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        Class_ c = classes->nth(i);
        
        // 检查父类是否存在
        if (get_class_parent(c) != No_class && !class_table.lookup(get_class_parent(c))) {
            semant_error(c->get_filename(), c) << "Class " << get_class_name(c) << " inherits from an undefined class " << get_class_parent(c) << "." << endl;
        }
        
        // 检查是否继承自Int、Bool或Str
        if (get_class_parent(c) == Int || get_class_parent(c) == Bool || get_class_parent(c) == Str) {
            semant_error(c->get_filename(), c) << "Class " << get_class_name(c) << " cannot inherit class " << get_class_parent(c) << "." << endl;
        }
    }
    
    // 检查Main类是否存在
    if (!class_table.lookup(Main)) {
        semant_error() << "Class Main is not defined." << endl;
    } else {
        // 检查Main类中是否有main方法
        Class_ main_class = lookup_class(Main);
        Features features = get_class_features(main_class);
        bool has_main_method = false;
        for (int i = features->first(); features->more(i); i = features->next(i)) {
            Feature f = features->nth(i);
            method_class* method = dynamic_cast<method_class*>(f);
            if (method && get_method_name(method) == main_meth) {
                has_main_method = true;
                break;
            }
        }
        
        if (!has_main_method) {
            semant_error(main_class->get_filename(), main_class) << "No 'main' method in class Main." << endl;
        }
    }
}

void ClassTable::install_basic_classes() {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built in to the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
    Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

    //
    // Bool also has only the "val" slot.
    //
    Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               self + arg
    //       substr(arg: Int, arg2: Int) : Str    substring from arg to arg2
    //
    Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(attr(val, Int, no_expr())),
							       single_Features(attr(str_field, prim_slot, no_expr()))),
					       single_Features(method(length, nil_Formals(), Int, no_expr()))),
			       append_Features(
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, no_expr())),
					       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)),
							     single_Formals(formal(arg2, Int))),
						      Str, no_expr())))),
	       filename);

    // 添加基本类到符号表
    class_table.addid(Object, &Object_class);
    class_table.addid(IO, &IO_class);
    class_table.addid(Int, &Int_class);
    class_table.addid(Bool, &Bool_class);
    class_table.addid(Str, &Str_class);
}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//    ostream& ClassTable::semant_error(Class_ c)
//       ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
//
/////////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(), c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
}

// 获取基本类
Class_ ClassTable::get_Object() { return Object_class; }
Class_ ClassTable::get_IO() { return IO_class; }
Class_ ClassTable::get_Int() { return Int_class; }
Class_ ClassTable::get_Bool() { return Bool_class; }
Class_ ClassTable::get_Str() { return Str_class; }

// 查找类
Class_ ClassTable::lookup_class(Symbol name) {
    Class_ *class_ptr = class_table.lookup(name);
    if (class_ptr) {
        return *class_ptr;
    }
    return nullptr;
}

/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be written in a check second pass using
     the reference to the information you set in 1).  */

// 检查是否是子类关系
bool ClassTable::is_subclass(Symbol child, Symbol parent) {
    // 如果child和parent相同，则是子类
    if (child == parent) {
        return true;
    }
    
    // 如果parent是Object，任何类都是Object的子类
    if (parent == Object) {
        return true;
    }
    
    // 获取child类
    Class_ child_class = lookup_class(child);
    if (!child_class) {
        return false;
    }
    
    // 获取child的父类
    Symbol child_parent = get_class_parent(child_class);
    
    // 如果child没有父类或者是Object，则不是parent的子类
    if (child_parent == No_class || child_parent == Object) {
        return false;
    }
    
    // 递归检查child的父类是否是parent的子类
    return is_subclass(child_parent, parent);
}

// 获取两个类的最小公共祖先
Symbol ClassTable::least_common_ancestor(Symbol type1, Symbol type2) {
    // 如果其中一个类型是No_type，返回另一个类型
    if (type1 == No_type) return type2;
    if (type2 == No_type) return type1;
    
    // 如果类型相同，返回该类型
    if (type1 == type2) return type1;
    
    // 如果type2是Object，返回Object
    if (type2 == Object) return Object;
    
    // 检查type1是否是type2的子类
    if (is_subclass(type1, type2)) {
        return type2;
    }
    
    // 检查type2是否是type1的子类
    if (is_subclass(type2, type1)) {
        return type1;
    }
    
    // 递归查找type1的父类与type2的最小公共祖先
    Class_ type1_class = lookup_class(type1);
    if (type1_class) {
        Symbol type1_parent = get_class_parent(type1_class);
        if (type1_parent != No_class) {
            return least_common_ancestor(type1_parent, type2);
        }
    }
    
    // 默认返回Object
    return Object;
}

void ClassTable::check_class_features(Class_ c)
{
    // 检查方法重写
    check_method_override(c);
    
    // 检查属性继承
    check_attribute_inheritance(c);
    
    // 检查类中的特性
    Features features = get_class_features(c);
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature f = features->nth(i);
        
        // 检查是否是方法
        method_class* method = dynamic_cast<method_class*>(f);
        if (method) {
            // 设置当前类和方法
            current_class = get_class_name(c);
            current_class_obj = c;
            current_method = get_method_name(method);
            
            // 创建新的作用域
            if (semant_debug) {
                cerr << "Entering scope for method " << current_method << endl;
            }
            object_table.enterscope();
            
            // 添加self到作用域
            if (semant_debug) {
                cerr << "Adding self to scope in method " << current_method << endl;
            }
            object_table.addid(self, new SymbolEntry(SELF_TYPE));
            
            // 添加参数到作用域
            Formals formals = get_method_formals(method);
            for (int j = formals->first(); formals->more(j); j = formals->next(j)) {
                Formal formal = formals->nth(j);
                Symbol formal_name = get_formal_name(formal);
                Symbol formal_type = get_formal_type_decl(formal);
                object_table.addid(formal_name, new SymbolEntry(formal_type));
            }
            
            // 检查方法返回类型是否存在
            if (get_method_return_type(method) != SELF_TYPE) {
                Class_ return_class = lookup_class(get_method_return_type(method));
                if (!return_class) {
                    semant_error(c->get_filename(), method) << "Undefined return type " << get_method_return_type(method) 
                        << " in method " << get_method_name(method) << "." << endl;
                }
            }
            
            // 检查方法参数类型是否存在
            for (int j = formals->first(); formals->more(j); j = formals->next(j)) {
                Formal formal = formals->nth(j);
                if (get_formal_type_decl(formal) != SELF_TYPE) {
                    Class_ param_class = lookup_class(get_formal_type_decl(formal));
                    if (!param_class) {
                        semant_error(c->get_filename(), formal) << "Undefined parameter type " << get_formal_type_decl(formal) 
                            << " in method " << get_method_name(method) << "." << endl;
                    }
                }
            }
            
            // 检查方法体的类型
            Expression method_body = get_method_expr(method);
            Symbol body_type = method_body->semant();
            Symbol return_type = get_method_return_type(method);
            
            // 检查方法体的类型是否与返回类型兼容
            if (body_type != No_type && !conforms_to(body_type, return_type)) {
                semant_error(c->get_filename(), method_body) << "Inferred type " << body_type 
                    << " of method body does not conform to declared return type " 
                    << return_type << " for method " << get_method_name(method) << "." << endl;
            }
            
            // 退出作用域
            if (semant_debug) {
                cerr << "Exiting scope for method " << current_method << endl;
            }
            object_table.exitscope();
        }
        
        // 检查是否是属性
        attr_class* attr = dynamic_cast<attr_class*>(f);
        if (attr) {
            // 检查属性类型是否存在
            if (get_attr_type_decl(attr) != SELF_TYPE) {
                Class_ attr_class = lookup_class(get_attr_type_decl(attr));
                if (!attr_class) {
                    semant_error(c->get_filename(), attr) << "Undefined type " << get_attr_type_decl(attr) 
                        << " in attribute " << get_attr_name(attr) << "." << endl;
                }
            }
            
            // 检查属性初始化表达式
            if (get_attr_init(attr)) {
                // 设置当前类
                current_class = get_class_name(c);
                current_class_obj = c;
                
                // 创建新的作用域并添加self
                object_table.enterscope();
                object_table.addid(self, new SymbolEntry(SELF_TYPE));
                
                // 检查初始化表达式的类型
                Expression init_expr = get_attr_init(attr);
                Symbol init_type = init_expr->semant();
                Symbol attr_type = get_attr_type_decl(attr);
                
                // 检查初始化表达式的类型是否与属性类型兼容
                if (init_type != No_type && !conforms_to(init_type, attr_type)) {
                    semant_error(c->get_filename(), init_expr) << "Inferred type " << init_type 
                        << " of initialization of attribute " << get_attr_name(attr) 
                        << " does not conform to declared type " << attr_type << "." << endl;
                }
                
                // 退出作用域
                object_table.exitscope();
            }
        }
    }
}

void ClassTable::check_method_override(Class_ c)
{
    // 如果是Object类，没有父类，不需要检查
    if (get_class_name(c) == Object || get_class_parent(c) == No_class) {
        return;
    }
    
    // 获取父类
    Class_ parent_class = lookup_class(get_class_parent(c));
    if (!parent_class) {
        return; // 父类不存在，已经在构造函数中报错
    }
    
    // 获取当前类和父类的方法
    Features child_features = get_class_features(c);
    Features parent_features = get_class_features(parent_class);
    
    // 遍历当前类的方法
    for (int i = child_features->first(); child_features->more(i); i = child_features->next(i)) {
        Feature child_feature = child_features->nth(i);
        
        // 检查是否是方法
        method_class* child_method = dynamic_cast<method_class*>(child_feature);
        if (!child_method) {
            continue; // 不是方法，跳过
        }
        
        // 在父类中查找同名方法
        method_class* parent_method = NULL;
        for (int j = parent_features->first(); parent_features->more(j); j = parent_features->next(j)) {
            Feature parent_feature = parent_features->nth(j);
            method_class* method = dynamic_cast<method_class*>(parent_feature);
            if (method && get_method_name(method) == get_method_name(child_method)) {
                parent_method = method;
                break;
            }
        }
        
        // 如果父类中有同名方法，检查重写规则
        if (parent_method) {
            // 检查返回类型是否相同
            if (get_method_return_type(child_method) != get_method_return_type(parent_method)) {
                semant_error(c->get_filename(), child_method) << "In redefined method " << get_method_name(child_method) 
                    << ", return type " << get_method_return_type(child_method) 
                    << " is different from original return type " << get_method_return_type(parent_method) << "." << endl;
            }
            
            // 检查参数数量是否相同
            Formals child_formals = get_method_formals(child_method);
            Formals parent_formals = get_method_formals(parent_method);
            
            if (list_length(child_formals) != list_length(parent_formals)) {
                semant_error(c->get_filename(), child_method) << "Incompatible number of formal parameters in redefined method " 
                    << get_method_name(child_method) << "." << endl;
                continue;
            }
            
            // 检查每个参数的类型是否相同
            for (int k = child_formals->first(); child_formals->more(k); k = child_formals->next(k)) {
                Formal child_formal = child_formals->nth(k);
                Formal parent_formal = parent_formals->nth(k);
                
                if (get_formal_type_decl(child_formal) != get_formal_type_decl(parent_formal)) {
                    semant_error(c->get_filename(), child_formal) << "In redefined method " << get_method_name(child_method) 
                        << ", parameter type " << get_formal_type_decl(child_formal) 
                        << " is different from original type " << get_formal_type_decl(parent_formal) << "." << endl;
                }
            }
        }
    }
}

void ClassTable::check_attribute_inheritance(Class_ c)
{
    // 如果是Object类，没有父类，不需要检查
    if (get_class_name(c) == Object || get_class_parent(c) == No_class) {
        return;
    }
    
    // 获取父类
    Class_ parent_class = lookup_class(get_class_parent(c));
    if (!parent_class) {
        return; // 父类不存在，已经在构造函数中报错
    }
    
    // 获取当前类和父类的特性
    Features child_features = get_class_features(c);
    Features parent_features = get_class_features(parent_class);
    
    // 遍历当前类的属性
    for (int i = child_features->first(); child_features->more(i); i = child_features->next(i)) {
        Feature child_feature = child_features->nth(i);
        
        // 检查是否是属性
        attr_class* child_attr = dynamic_cast<attr_class*>(child_feature);
        if (!child_attr) {
            continue; // 不是属性，跳过
        }
        
        // 在父类中查找同名属性
        attr_class* parent_attr = NULL;
        for (int j = parent_features->first(); parent_features->more(j); j = parent_features->next(j)) {
            Feature parent_feature = parent_features->nth(j);
            attr_class* attr = dynamic_cast<attr_class*>(parent_feature);
            if (attr && get_attr_name(attr) == get_attr_name(child_attr)) {
                parent_attr = attr;
                break;
            }
        }
        
        // 如果父类中有同名属性，报错
        if (parent_attr) {
            semant_error(c->get_filename(), child_attr) << "Attribute " << get_attr_name(child_attr) 
                << " is an attribute of an inherited class." << endl;
        }
    }
}



void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name    = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}

// 符号定义
Symbol arg;
Symbol arg2;
Symbol Bool;
Symbol concat;
Symbol cool_abort;
Symbol copy;
Symbol Int;
Symbol in_int;
Symbol in_string;
Symbol IO;
Symbol length;
Symbol Main;
Symbol main_meth;
Symbol No_class;
Symbol No_type;
Symbol Object;
Symbol out_int;
Symbol out_string;
Symbol prim_slot;
Symbol self;
Symbol SELF_TYPE;
Symbol Str;
Symbol str_field;
Symbol substr;
Symbol type_name;
Symbol val;



// 获取列表长度


int list_length(Expressions exprs) {
    int count = 0;
    if (exprs) {
        for (int i = exprs->first(); exprs->more(i); i = exprs->next(i)) {
            count++;
        }
    }
    return count;
}

int list_length(Cases cases) {
    int count = 0;
    if (cases) {
        for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
            count++;
        }
    }
    return count;
}
