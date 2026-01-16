#include "semant.h"
#include "stringtab.h"

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