#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// 预定义符号
extern Symbol arg;
extern Symbol arg2;
extern Symbol Bool;
extern Symbol concat;
extern Symbol cool_abort;
extern Symbol copy;
extern Symbol Int;
extern Symbol in_int;
extern Symbol in_string;
extern Symbol IO;
extern Symbol length;
extern Symbol Main;
extern Symbol main_meth;
extern Symbol No_class;
extern Symbol No_type;
extern Symbol Object;
extern Symbol out_int;
extern Symbol out_string;
extern Symbol prim_slot;
extern Symbol self;
extern Symbol SELF_TYPE;
extern Symbol Str;
extern Symbol str_field;
extern Symbol substr;
extern Symbol type_name;
extern Symbol val;

// 辅助函数，用于访问类的protected成员
// 辅助函数声明
Symbol get_class_name(Class_ c);
Symbol get_class_parent(Class_ c);
Features get_class_features(Class_ c);
Symbol get_attr_name(Feature f);
Symbol get_attr_type_decl(Feature f);
Expression get_attr_init(Feature f);
Symbol get_method_name(Feature f);
Formals get_method_formals(Feature f);
Symbol get_method_return_type(Feature f);
Expression get_method_expr(Feature f);
Symbol get_formal_name(Formal f);
Symbol get_formal_type_decl(Formal f);

// 获取列表长度
int list_length(Formals formals);
int list_length(Expressions exprs);
int list_length(Cases cases);
int list_length(Expressions exprs);
int list_length(Cases cases);

// 初始化常量符号
void initialize_constants(void);

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {
private:
  int semant_errors;
  void install_basic_classes();
  ostream& error_stream;
  
  // 类列表
  Classes classes;
  
  // 基本类的存储
  Class_ Object_class;
  Class_ IO_class;
  Class_ Int_class;
  Class_ Bool_class;
  Class_ Str_class;
  
  // 类符号表
  SymbolTable<Symbol, Class_> class_table;
  
  void check_attribute_inheritance(Class_ c);

public:
  // 检查类特性
  void check_class_features(Class_ c);
  void check_method_override(Class_ c);
  bool is_subclass(Symbol child, Symbol parent);
  Symbol least_common_ancestor(Symbol type1, Symbol type2);
  ClassTable(Classes);
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
  
  // 获取基本类的方法
  Class_ get_Object_class() { return Object_class; }
  Class_ get_IO_class() { return IO_class; }
  Class_ get_Int_class() { return Int_class; }
  Class_ get_Bool_class() { return Bool_class; }
  Class_ get_Str_class() { return Str_class; }
  
  // 获取基本类
  Class_ get_Object();
  Class_ get_IO();
  Class_ get_Int();
  Class_ get_Bool();
  Class_ get_Str();
  
  // 查找类的方法
  Class_ lookup_class(Symbol name);
  
  // 语义分析主方法
  void semant();
};


#endif

