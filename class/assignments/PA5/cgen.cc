//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

#include "cgen.h"
#include "cgen_gc.h"



extern void emit_string_constant(ostream& str, char* s);
extern int cgen_debug;

int labelnum = 0;
CgenClassTable* codegen_classtable = nullptr;
DebugFile* pDbg;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol  //// 全局变量，反映有哪些符号，每个符号唯一标识一个类、方法、形参（formal）等 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void) {
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
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}

static char* gc_init_names[] =
{ "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char* gc_collect_names[] =
{ "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


//  BoolConst is a class that implements code generation for operations
//  on the two booleans, which are given global names here.
BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void program_class::cgen(ostream& os) {
/*
1. 构建CgenClassTable
    安装基本类
    安装用户定义类
    构建继承树
    调用CgenClassTable::code()生成代码
6. 退出作用域
*/
    // spim wants comments to start with '#'
    os << "# start of generated code\n";
    pDbg = new DebugFile(os);
    initialize_constants(); ////关联符号表和符号名（映射）
    codegen_classtable = new CgenClassTable(classes, os);   
    // codegen_classtable->code();
    // codegen_classtable->exitscope();
    ////首先，ast_parse.cc中的一个Program类型的ast_root指针
    ////存储了解析出的classes调用，然后cgen-phase.cc中调用了ast_root->cgen(s);
    codegen_classtable->Execute();

    os << "\n# end of generated code\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_load(const char* dest_reg, int offset, const char* source_reg, ostream& s) {
    s << LW << dest_reg << " " << offset* WORD_SIZE << "(" << source_reg << ")"
      << endl;
}

static void emit_store(const char* source_reg, int offset, const char* dest_reg, ostream& s) {
    s << SW << source_reg << " " << offset* WORD_SIZE << "(" << dest_reg << ")"
      << endl;
}

static void emit_load_imm(const char* dest_reg, int val, ostream& s) {
    s << LI << dest_reg << " " << val << endl;
}

static void emit_load_address(const char* dest_reg, const char* address, ostream& s) {
    s << LA << dest_reg << " " << address << endl;
}

static void emit_partial_load_address(const char* dest_reg, ostream& s) {
    s << LA << dest_reg << " ";
}

static void emit_load_bool(const char* dest, const BoolConst& b, ostream& s) {
    emit_partial_load_address(dest, s);
    b.code_ref(s);
    s << endl;
}

static void emit_load_string(const char* dest, StringEntry* str, ostream& s) {
    emit_partial_load_address(dest, s);
    str->code_ref(s);
    s << endl;
}

static void emit_load_int(const char* dest, IntEntry* i, ostream& s) {
    emit_partial_load_address(dest, s);
    i->code_ref(s);
    s << endl;
}

static void emit_move(const char* dest_reg, const char* source_reg, ostream& s) {
    s << MOVE << dest_reg << " " << source_reg << endl;
}

static void emit_neg(const char* dest, const char* src1, ostream& s) {
    s << NEG << dest << " " << src1 << endl;
}

static void emit_add(const char* dest, const char* src1, const char* src2, ostream& s) {
    s << ADD << dest << " " << src1 << " " << src2 << endl;
}

static void emit_addu(const char* dest, const char* src1, const char* src2, ostream& s) {
    s << ADDU << dest << " " << src1 << " " << src2 << endl;
}

static void emit_addiu(const char* dest, const char* src1, int imm, ostream& s) {
    s << ADDIU << dest << " " << src1 << " " << imm << endl;
}

static void emit_div(const char* dest, const char* src1, const char* src2, ostream& s) {
    s << DIV << dest << " " << src1 << " " << src2 << endl;
}

static void emit_mul(const char* dest, const char* src1, const char* src2, ostream& s) {
    s << MUL << dest << " " << src1 << " " << src2 << endl;
}

static void emit_sub(const char* dest, const char* src1, const char* src2, ostream& s) {
    s << SUB << dest << " " << src1 << " " << src2 << endl;
}

static void emit_sll(const char* dest, const char* src1, int num, ostream& s) {
    s << SLL << dest << " " << src1 << " " << num << endl;
}

static void emit_jalr(const char* dest, ostream& s) {
    s << JALR << "\t" << dest << endl;
}

static void emit_jal(const char* address, ostream& s) {
    s << JAL << address << endl;
}

static void emit_return(ostream& s) {
    s << RET << endl;
}

static void emit_gc_assign(ostream& s) {
    s << JAL << "_GenGC_Assign" << endl;
}

static void emit_disptable_ref(Symbol sym, ostream& s) {
    s << sym << DISPTAB_SUFFIX;
}

static void emit_init_ref(Symbol sym, ostream& s) {
    s << sym << CLASSINIT_SUFFIX;
}

static void emit_label_ref(int l, ostream& s) {
    s << "label" << l;
}

static void emit_protobj_ref(Symbol sym, ostream& s) {
    s << sym << PROTOBJ_SUFFIX;
}

static void emit_method_ref(Symbol classname, Symbol methodname, ostream& s) {
    s << classname << METHOD_SEP << methodname;
}

static void emit_label_def(int l, ostream& s) {
    emit_label_ref(l, s);
    s << ":" << endl;
}

static void emit_beqz(char* source, int label, ostream& s) {
    s << BEQZ << source << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_beq(const char* src1, const char* src2, int label, ostream& s) {
    s << BEQ << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_bne(const char* src1, const char* src2, int label, ostream& s) {
    s << BNE << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_bleq(const char* src1, const char* src2, int label, ostream& s) {
    s << BLEQ << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_blt(const char* src1, const char* src2, int label, ostream& s) {
    s << BLT << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_blti(const char* src1, int imm, int label, ostream& s) {
    s << BLT << src1 << " " << imm << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_bgti(const char* src1, int imm, int label, ostream& s) {
    s << BGT << src1 << " " << imm << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_branch(int l, ostream& s) {
    s << BRANCH;
    emit_label_ref(l, s);
    s << endl;
}

//
// Push a register on the stack. The stack grows towards smaller addresses.
//
static void emit_push(char* reg, ostream& str) {
    emit_store(reg, 0, SP, str);
    emit_addiu(SP, SP, -4, str);
}

//
// Fetch the integer value in an Int object.
// Emits code to fetch the integer value of the Integer object pointed
// to by register source into the register dest
//
static void emit_fetch_int(const char* dest, char* source, ostream& s) {
    emit_load(dest, DEFAULT_OBJFIELDS, source, s);
}

//
// Emits code to store the integer value contained in register source
// into the Integer object pointed to by dest.
//
static void emit_store_int(char* source, const char* dest, ostream& s) {
    emit_store(source, DEFAULT_OBJFIELDS, dest, s);
}


static void emit_test_collector(ostream& s) {
    emit_push(ACC, s);
    emit_move(ACC, SP, s); // stack end
    emit_move(A1, ZERO, s); // allocate nothing
    s << JAL << gc_collect_names[cgen_Memmgr] << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(ACC, 0, SP, s);
}

static void emit_gc_check(char* source, ostream& s) {
    // if (std::string(source) != std::string(A1)) {   
    //     emit_move(A1, source, s);
    // }
    if ((const char*)source != (const char*)A1) emit_move(A1, source, s); ////一般来说cpp编译器都会把一样的字符串字面量优化到同一个。不过前提是source是一个字符串字面量而非一个字符数组。
    s << JAL << "_gc_check" << endl;
} ////jal _gc_check，跳转到_gc_check函数，检查source寄存器是否需要垃圾回收。a1存放source的地址。


///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type StringEntry.  StringEntry methods are defined both for String
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream& s) {
    s << STRCONST_PREFIX << index;
}

//
// Emit code for a constant String.
// You should fill in the code naming the dispatch table.
//

void StringEntry::code_def(ostream& s, int stringclasstag) {
    IntEntryP lensym = inttable.add_int(len);

    // Add -1 eye catcher
    s << WORD << "-1" << endl;  /*这是一个特殊的标记值，用于：
1. 调试辅助 ：帮助调试器识别对象边界
2. 内存检查 ：作为对象开始的标识符
3. 垃圾回收 ：帮助垃圾回收器识别有效对象*/////每个对象的开始前都有一个-1的标记值。

    code_ref(s);    ////给每个不同的StrEntry（每个字符串常量）生成不同标签值（index）
    s  << LABEL                                             // label
       << WORD << stringclasstag << endl                                 // tag//// 字符串类的标签值，用来标识字符串对象的类型
       << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len + 4) / 4) << endl // size//// 字符串对象的大小，包括默认字段、字符串槽位和字符串长度（四字节对齐）。默认字段包括对象标签和对象大小。字符串槽位用于存储字符串的实际内容。字符串长度（包括空字符）需要四字节对齐。
       << WORD;


    /***** Add dispatch information for class String ******/
    s << Str << DISPTAB_SUFFIX;  ////在MIPS汇编中，这行代码生成的输出会引用String类的分发表（dispatch table），这是Cool语言对象系统中用于方法调度的关键数据结构。每个Cool类都有一个对应的分发表，其中包含了该类所有方法的地址。这个的输出类似为String_dispTab。

    s << endl;                                              // dispatch table
    s << WORD;
    lensym->code_ref(s);
    s << endl;            // string length
    emit_string_constant(s, str);    ////生成MIPS格式的字符串常量，包括字符串内容和空字符。（在cgen_supp.cc中实现MIPS格式封装）                           // ascii string
    s << ALIGN;                                                 // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the
// stringtable.
//
void StrTable::code_string_table(ostream& s, int stringclasstag) {
    for (List<StringEntry> *l = tbl; l; l = l->tl()) {
        l->hd()->code_def(s, stringclasstag);   ////开始生成字符串对象的MIPS格式汇编。stringclasstag。
    }
}

//
// Ints
//
void IntEntry::code_ref(ostream& s) {
    s << INTCONST_PREFIX << index;
}

//
// Emit code for a constant Integer.
// You should fill in the code naming the dispatch table.
//

void IntEntry::code_def(ostream& s, int intclasstag) {
    // Add -1 eye catcher
    s << WORD << "-1" << endl;

    code_ref(s);
    s << LABEL                                // label
      << WORD << intclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl  // object size
      << WORD;

    /***** Add dispatch information for class Int ******/
    s << Int << DISPTAB_SUFFIX;

    s << endl;                                          // dispatch table
    s << WORD << str << endl;                           // integer value
}


//
// IntTable::code_string_table
// Generate an Int object definition for every Int constant in the
// inttable.
//
void IntTable::code_string_table(ostream& s, int intclasstag) {
    for (List<IntEntry> *l = tbl; l; l = l->tl()) {
        l->hd()->code_def(s, intclasstag);
    }
}


//
// Bools
//
BoolConst::BoolConst(int i) : val(i) {
    assert(i == 0 || i == 1);
}

void BoolConst::code_ref(ostream& s) const {
    s << BOOLCONST_PREFIX << val;
}

//
// Emit code for a constant Bool.
// You should fill in the code naming the dispatch table.
//

void BoolConst::code_def(ostream& s, int boolclasstag) {
    // Add -1 eye catcher
    s << WORD << "-1" << endl;

    code_ref(s);
    s << LABEL                                  // label
      << WORD << boolclasstag << endl                       // class tag
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl   // object size
      << WORD;

    /***** Add dispatch information for class Bool ******/
    s << Bool << DISPTAB_SUFFIX;

    s << endl;                                            // dispatch table
    s << WORD << val << endl;                             // value (0 or 1)
}


int Environment::AddObstacle() {
    EnterScope();
    return AddVar(No_class);
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//***************************************************
//
//  Emit code to start the .data segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_data() {
    Symbol main    = idtable.lookup_string(MAINNAME);   ////从之前注册的idtable中查找MAINNAME字符串对应的符号，存储了String和其他信息，可供ostream直接输出（stringtab.cc有重载）
    Symbol string  = idtable.lookup_string(STRINGNAME);
    Symbol integer = idtable.lookup_string(INTNAME);
    Symbol boolc   = idtable.lookup_string(BOOLNAME);

    str << "\t.data\n" << ALIGN;
    //
    // The following global names must be defined first.
    //
    str << GLOBAL << CLASSNAMETAB << endl;
    str << GLOBAL;
    emit_protobj_ref(main, str);
    str << endl;
    str << GLOBAL;
    emit_protobj_ref(integer, str);
    str << endl;
    str << GLOBAL;
    emit_protobj_ref(string, str);
    str << endl;
    str << GLOBAL;
    falsebool.code_ref(str);
    str << endl;
    str << GLOBAL;
    truebool.code_ref(str);
    str << endl;
    str << GLOBAL << INTTAG << endl;
    str << GLOBAL << BOOLTAG << endl;
    str << GLOBAL << STRINGTAG << endl;

    //
    // We also need to know the tag of the Int, String, and Bool classes
    // during code generation.
    //
    str << INTTAG << LABEL
        << WORD << intclasstag << endl;
    str << BOOLTAG << LABEL
        << WORD << boolclasstag << endl;
    str << STRINGTAG << LABEL
        << WORD << stringclasstag << endl;
}


//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_text() {
    str << GLOBAL << HEAP_START << endl ////.globl	heap_start
        << HEAP_START << LABEL  ////heap_start:
        << WORD << 0 << endl
        << "\t.text" << endl
        << GLOBAL;
    emit_init_ref(idtable.add_string("Main"), str); ////反正根据规则，这个stringtable都只会拥有一个条目（在add_string的时候会检查是否已经存在），然后返回这个条目所在的地址（Symbol 等价于 Entry*）
    str << endl << GLOBAL;
    emit_init_ref(idtable.add_string("Int"), str);
    str << endl << GLOBAL;
    emit_init_ref(idtable.add_string("String"), str);
    str << endl << GLOBAL;
    emit_init_ref(idtable.add_string("Bool"), str);
    str << endl << GLOBAL;
    emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
    str << endl;
    /*
    .globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
    */
}

void CgenClassTable::code_bools(int boolclasstag) {
    falsebool.code_def(str, boolclasstag);
    truebool.code_def(str, boolclasstag);
}

void CgenClassTable::code_select_gc() {
    //
    // Generate GC choice constants (pointers to GC functions)
    //
    ////在handle_flags.cc中有给出命令行的参数，用于选择垃圾回收策略
    str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
    str << "_MemMgr_INITIALIZER:" << endl;
    str << WORD << gc_init_names[cgen_Memmgr] << endl;
    str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
    str << "_MemMgr_COLLECTOR:" << endl;
    str << WORD << gc_collect_names[cgen_Memmgr] << endl;
    str << GLOBAL << "_MemMgr_TEST" << endl;
    str << "_MemMgr_TEST:" << endl;
    str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}


//********************************************************
//
// Emit code to reserve space for and initialize all of
// the constants.  Class names should have been added to
// the string table (in the supplied code, is is done
// during the construction of the inheritance graph), and
// code for emitting string constants as a side effect adds
// the string's length to the integer table.  The constants
// are emmitted by running through the stringtable and inttable
// and producing code for each entry.
//
//********************************************************

void CgenClassTable::code_constants() {
    //
    // Add constants that are required by the code generator.
    //
    stringtable.add_string(""); ////即.byte 0 字段，作为字符串末尾
    inttable.add_string("0");

    stringtable.code_string_table(str, stringclasstag);
    inttable.code_string_table(str, intclasstag);
    code_bools(boolclasstag);
}

void CgenClassTable::code_class_nameTab() { //// 类名表，用于存储所有类的名称的字符串,每个类名的字符串占4个字节,类名表的起始地址存储在CLASSNAMETAB中
    str << CLASSNAMETAB << LABEL;   ////class_nameTab:

    std::vector<CgenNode*> class_nodes = GetClassNodes();
    for (CgenNode* class_node : class_nodes) {
        Symbol class_name = class_node->name;
        StringEntry* str_entry = stringtable.lookup_string(class_name->get_string());

        str << WORD;    ////.word
        str_entry->code_ref(str);   ////str_const8
        str << endl;
        std::vector<CgenNode*> _children = class_node->GetChildren();
        for (CgenNode* _child : _children) {
            pDbg->debug2file() << "child: " << _child->name;
        }
        str << std::endl;
    }
}

void CgenClassTable::code_class_objTab() {  //// 类对象表，存放类原型地址+类初始化函数地址
    str << CLASSOBJTAB << LABEL;
    // Find all class names.
    std::vector<CgenNode*> class_nodes = GetClassNodes();
    for (CgenNode* class_node : class_nodes) {
        Symbol class_name = class_node->name;
        StringEntry* str_entry = stringtable.lookup_string(class_name->get_string());

        str << WORD;
        emit_protobj_ref(str_entry, str);
        str << endl;
        str << WORD;
        emit_init_ref(str_entry, str);
        str << endl;
    }
}

void CgenClassTable::code_dispatchTab() {  //// 生成调度表/方法分派表（dispatchTabs），存放类方法地址
    std::vector<CgenNode*> class_nodes = GetClassNodes();

    for (CgenNode* _class_node : class_nodes) {
        emit_disptable_ref(_class_node->name, str);
        str << LABEL;
        std::vector<method_class*> full_methods = _class_node->GetFullMethods();
        std::map<Symbol, Symbol> dispatch_class_tab = _class_node->GetDispatchClassTab();
        std::map<Symbol, int> dispatch_idx_tab = _class_node->GetDispatchIdxTab();
        for (method_class* _method : full_methods) {
            Symbol _method_name = _method->name;
            Symbol _class_name = dispatch_class_tab[_method_name];
            int _idx = dispatch_idx_tab[_method_name];
            pDbg->debug2file() << "method # " << _idx;
            str << WORD;
            emit_method_ref(_class_name, _method_name, str);
            str << endl;
        }
    }
}

std::vector<CgenNode*> CgenClassTable::GetClassNodes() {
    if (m_class_nodes.empty()) {
        for (List<CgenNode> *l = nds; l; l = l->tl()) {
            CgenNode* class_node = l->hd();
            m_class_nodes.push_back(class_node);
        }
        std::reverse(m_class_nodes.begin(), m_class_nodes.end());
        for (int i = 0; i < m_class_nodes.size(); ++i) {
            m_class_nodes[i]->class_tag = i;
            m_class_tags.insert(std::make_pair(m_class_nodes[i]->get_name(), i));
        }
    }

    return m_class_nodes;
}

std::map<Symbol, int> CgenClassTable::GetClassTags() {
    GetClassNodes();
    return m_class_tags;
}

std::vector<CgenNode*> CgenNode::GetInheritance() {
    if (inheritance.empty()) {
        CgenNode* class_node = this;
        while (class_node->name != No_class) {
            inheritance.push_back(class_node);
            class_node = class_node->get_parentnd();
        }
        std::reverse(inheritance.begin(), inheritance.end());
    }

    return inheritance;
}

std::vector<attr_class*> CgenNode::GetFullAttribs() {
    if (m_full_attribs.empty()) {
        std::vector<CgenNode*> inheritance = GetInheritance();
        for (CgenNode* class_node : inheritance) {
            Features features = class_node->features;
            for (int j = features->first(); features->more(j); j = features->next(j)) {
                Feature feature = features->nth(j);
                if (!feature->IsMethod()) {
                    m_full_attribs.push_back((attr_class*)feature);
                }
            }
        }
        for (int i = 0; i < m_full_attribs.size(); ++i) {
            m_attrib_idx_tab[m_full_attribs[i]->name] = i;
        }
    }

    return m_full_attribs;
}

std::vector<attr_class*> CgenNode::GetAttribs() {
    if (m_attribs.empty()) {
        for (int j = features->first(); features->more(j); j = features->next(j)) {
            Feature feature = features->nth(j);
            if (!feature->IsMethod()) {
                m_attribs.push_back((attr_class*)feature);
            }
        }
    }

    return m_attribs;
}

std::map<Symbol, int> CgenNode::GetAttribIdxTab() {
    GetFullAttribs();
    return m_attrib_idx_tab;
}

std::vector<method_class*> CgenNode::GetMethods() {
    if (m_methods.empty()) {
        for (int i = features->first(); features->more(i); i = features->next(i)) {
            Feature feature = features->nth(i);
            if (feature->IsMethod()) {
                m_methods.push_back((method_class*)feature);
            }
        }
    }
    return m_methods;
}

std::vector<method_class*> CgenNode::GetFullMethods() {
    if (m_full_methods.empty()) {
        // We must update m_full_methods, m_dispatch_class_tab, m_dispatch_idx_tab.

        std::vector<CgenNode*> inheritance = GetInheritance();
        for (CgenNode* _class_node : inheritance) {
            Symbol _class_name = _class_node->name;
            std::vector<method_class*> _methods = _class_node->GetMethods();
            for (method_class* _method : _methods) {
                Symbol _method_name = _method->name;
                if (m_dispatch_idx_tab.find(_method_name) == m_dispatch_idx_tab.end()) {
                    // method need to be inserted.
                    m_full_methods.push_back(_method);
                    m_dispatch_idx_tab[_method_name] = m_full_methods.size() - 1;
                    m_dispatch_class_tab[_method_name] = _class_name;
                } else {
                    int idx = m_dispatch_idx_tab[_method_name];
                    m_full_methods[idx] = _method;
                    m_dispatch_class_tab[_method_name] = _class_name;
                }
            }
        }
    }
    return m_full_methods;
}

std::map<Symbol, Symbol> CgenNode::GetDispatchClassTab() {
    GetFullMethods();
    return m_dispatch_class_tab;
}

std::map<Symbol, int> CgenNode::GetDispatchIdxTab() {
    GetFullMethods();
    return m_dispatch_idx_tab;
}

void method_class::code(ostream& s, CgenNode* class_node) {
    emit_method_ref(class_node->name, name, s); 
    s << LABEL;
    s << "\t# push fp, s0, ra" << endl;
    emit_addiu(SP, SP, -12, s);
    emit_store(FP, 3, SP, s);
    emit_store(SELF, 2, SP, s);
    emit_store(RA, 1, SP, s);
    s << endl;
    
    s << "\t# fp now points to the return addr in stack" << endl;
    emit_addiu(FP, SP, 4, s);
    s << endl;

    s << "\t# SELF = a0" << endl;
    emit_move(SELF, ACC, s);
    s << endl;

    s << "\t# evaluating expression and put it to ACC" << endl; ////这里是生成方法代码和生成init代码不同的地方。init代码只需要创建栈帧、设置SELF为a0即可，不需要评估表达式。因为init代码只需要初始化对象的属性，而不需要执行任何表达式。
    Environment env;    //// 这里创建一个环境对象，用于存储方法的参数和局部变量。
    env.m_class_node = class_node;  //// 方法所在的类节点
    for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
        env.AddParam(formals->nth(i)->GetName());
    }   //// 这里将方法的参数添加到环境中，参数的偏移量从4开始，因为前4个寄存器分别为fp, s0, ra, self。
    expr->code(s, env); ////这是一个多态的写法，expr是纯虚类Expression的指针，在纯虚类中使用宏定义定义了一个纯虚函数code，动态多态，根据实际对象的类型调用对应的code方法，生成表达式对应的MIPS代码。expr的类型可以是Assign_class, let_class等等，分别表示了一种（最基础的）表达式。 
    s << endl;

    s << "\t# pop fp, s0, ra" << endl;  //// 这里弹出栈帧，恢复fp, s0, ra寄存器的值。
    emit_load(FP, 3, SP, s);
    emit_load(SELF, 2, SP, s);
    emit_load(RA, 1, SP, s);
    emit_addiu(SP, SP, 12, s);
    s << endl;

    s << "\t# Pop arguments" << endl;
    emit_addiu(SP, SP, GetArgNum() * 4, s);
    s << endl;

    s << "\t# return" << endl;
    emit_return(s);
    s << endl;
}

void CgenNode::code_protObj(ostream& s) {
    std::vector<attr_class*> attribs = GetFullAttribs();    ////一个类的所有属性，在安装类时进行了初始化

    s << WORD << "-1" << endl;
    s << get_name() << PROTOBJ_SUFFIX << LABEL;
    s << WORD << class_tag << "\t# class tag" << endl;
    s << WORD << (DEFAULT_OBJFIELDS + attribs.size()) << "\t# size" << endl;
    s << WORD << get_name() << DISPTAB_SUFFIX << endl;
    
    for (int i = 0; i < attribs.size(); ++i) {  ////扫描之前注册的feature的attr
        if (attribs[i]->name == val) { //// 获取属性为val（表示String类的长度/Int类的值等）：idtable.add_string("_val"); 
            if (get_name() == Str) {    ////如果当前节点是字符串类，初始化字符串长度为0
                s << WORD;
                inttable.lookup_string("0")->code_ref(s);
                s << "\t# int(0)";  //// 初始化字符串为0，即为空串
                s << endl;
            } else {
                s << WORD << "0\t# val(0)" << endl;
            }
        } else if (attribs[i]->name == str_field) { // _str_field
            s << WORD << "0\t# str(0)" << endl; //// 初始化字符串为空串
        } else { // normal attribute.
            Symbol type = attribs[i]->type_decl;
            if (type == Int) {
                s << WORD;
                inttable.lookup_string("0")->code_ref(s);  
                s << "\t# int(0)";
                s << endl;
            } else if (type == Bool) {
                s << WORD;
                falsebool.code_ref(s);
                s << "\t# bool(0)";
                s << endl;
            } else if (type == Str) {
                s << WORD;
                stringtable.lookup_string("")->code_ref(s);
                s << "\t# str("")";
                s << endl;
            } else {
                s << WORD;
                s << "0\t# void" << endl;
            }
        }
    }
}

/*
 * CgenNode::code_init - 生成类的初始化代码
 * 
 * 这个函数是COOL编译器代码生成阶段的核心函数之一，负责为每个类生成初始化代码。
 * 初始化函数的主要职责是：
 * 1. 设置栈帧，保存调用者的上下文（fp, s0, ra）
 * 2. 初始化对象的父类部分（通过调用父类的初始化函数）
 * 3. 初始化对象的所有属性（包括默认值和自定义初始化表达式）
 * 4. 返回初始化完成的对象引用
 * 
 * 参数：
 *   s - 输出流，用于写入生成的汇编代码
 * 
 * 调用约定：
 *   - 输入：a0寄存器包含对象的地址（由调用者分配）
 *   - 输出：a0寄存器返回初始化完成的对象地址
 *   - 副作用：修改对象的属性值，可能调用父类初始化函数
 */
void CgenNode::code_init(ostream& s) {
    /* 
     * 第一步：生成初始化函数的入口标签
     * 标签格式为：类名_init（例如：Main_init, Object_init等）
     * 这是MIPS汇编中的函数入口点，用于跳转到该类的初始化代码
     */
    s << get_name();
    s << CLASSINIT_SUFFIX;
    s << LABEL;
    
    // debug2file() << "Generating init method for class: " << get_name() << " at line " << __LINE__;
    
    /* 
     * 第二步：保存调用者的栈帧信息
     * 
     * 在MIPS调用约定中，我们需要保存以下寄存器：
     * - fp（帧指针）：指向当前栈帧的基地址
     * - s0（SELF寄存器）：指向当前操作的对象
     * - ra（返回地址）：函数返回时需要跳转的地址
     * 
     * 栈空间排布图（从高地址到低地址，栈向下增长）：
     * 
     * 高地址方向
     * +------------------+  <- 进入函数前的sp位置
     * |     参数n        |  <- 第n个参数（如果有）
     * +------------------+    
     * |       ...        |  <- 其他参数
     * +------------------+    
     * |     参数1        |  <- 第1个参数（如果有）
     * +------------------+    
     * |   [旧的fp]       |  <- 保存调用者的帧指针（偏移量12）
     * |                  |     sw $fp 12($sp)
     * +------------------+    
     * |   [旧的s0]       |  <- 保存调用者的SELF寄存器（偏移量8）
     * |                  |     sw $s0 8($sp)
     * +------------------+ <- 新的fp位置(新sp + 4)   
     * |   [旧的ra]       |  <- 保存调用者的返回地址（偏移量4）
     * |                  |     sw $ra 4($sp)
     * +------------------+  <- 新的sp指向这里（emit_addiu(SP, SP, -12, s)后）
     * 低地址方向
     * 
     * 栈帧结构说明：
     * - 总共分配12字节空间（3个寄存器 × 4字节）
     * - 新的fp = sp + 4，指向保存ra的位置
     * - 这种布局使得可以通过fp方便地访问栈中的参数和局部变量
     * - 恢复时按照相反顺序：先恢复寄存器，再释放栈空间
     */
    // s << "\t# push fp, s0, ra" << endl;
    pDbg->debug2file(NORMAL) << "save fp, s0, ra";
    emit_addiu(SP, SP, -12, s);        // 栈指针向下移动12字节，为保存寄存器分配空间addiu	$sp $sp -12
    emit_store(FP, 3, SP, s);          // 保存旧的帧指针到栈中（偏移量12）sw	$fp 12($sp)
    emit_store(SELF, 2, SP, s);        // 保存旧的SELF寄存器到栈中（偏移量8）sw	$s0 8($sp)
    emit_store(RA, 1, SP, s);          // 保存返回地址到栈中（偏移量4）sw	$ra 4($sp)
    s << endl;
    
    /* 
     * 第三步：设置新的栈帧
     * 
     * 新的帧指针（fp）指向返回地址的存储位置
     * 这样我们可以通过fp方便地访问栈中的参数和局部变量
     * fp = sp + 4，指向保存ra的位置
     */
    // s << "\t# fp now points to the return addr in stack" << endl;
    
    emit_addiu(FP, SP, 4, s);          // 设置新的帧指针addiu	$fp $sp 4
    pDbg->debug2file(BELOW) << "fp now points to the return addr in stack";
    s << endl;

    /* 
     * 第四步：设置SELF寄存器指向当前对象
     * 
     * 根据COOL的调用约定，对象地址通过a0寄存器传入
     * 我们将这个地址保存到SELF寄存器中，后续所有对象操作都使用这个寄存器
     * 这实现了COOL中的self关键字功能
     */
    pDbg->debug2file() << "SELF = a0(ACC), set current object pointer";
    emit_move(SELF, ACC, s);             // SELF = ACC (a0)，设置当前对象指针
    s << endl;
    
    /* 
     * 第五步：调用父类的初始化函数
     * 
     * 如果当前类不是Object类（即存在父类），我们需要先初始化继承自父类的部分
     * 这是通过递归调用父类的初始化函数实现的，确保继承链上的所有类都被正确初始化
     * 
     * 注意：Object类的父类是No_class，所以不需要调用父类初始化
     */
    Symbol parent_name = get_parentnd()->name;
    if (parent_name != No_class) {
        pDbg->debug2file() << "Calling parent init for class: " << get_name() << ", parent: " << parent_name;
        s << JAL;                        // 跳转到父类初始化函数
        emit_init_ref(parent_name, s);   // 生成父类初始化函数的引用
        s << endl << endl;
    }

    /* 
     * 第六步：初始化类的所有属性
     * 
     * 每个COOL类都有一组属性（成员变量），我们需要在这里为它们分配初始值
     * 属性的初始化分为两种情况：
     * 1. 有初始化表达式：执行表达式代码，将结果存储到对象中
     * 2. 无初始化表达式：为基本类型提供默认值（空字符串、0、false）
     * 
     * 属性在对象中的存储布局：
     * - 前3个字：对象头信息（类标签、对象大小、dispatch表指针）
     * - 后续字：属性值，按照定义顺序存储
     */
    std::vector<attr_class*> attribs = GetAttribs();
    std::map<Symbol, int> attrib_idx_tab = GetAttribIdxTab();
    
    pDbg->debug2file() << "Initializing " << attribs.size() << " attributes for class: " << get_name();
    
    for (attr_class* attrib : attribs) {
        pDbg->debug2file() << "Processing attribute: " << attrib->name << " of type " << attrib->type_decl;
        s << "\t# init attrib " << attrib->name << endl;
        int idx = attrib_idx_tab[attrib->name];  // 获取属性在对象中的索引位置

        if (attrib->init->IsEmpty()) {
            /* 
             * 情况1：属性没有初始化表达式
             * 为基本类型提供默认值：
             * - String类型：默认为空字符串""
             * - Int类型：默认为0
             * - Bool类型：默认为false（0）
             * 
             * 其他类型（对象引用）默认为null，不需要显式初始化
             */
            if (attrib->type_decl == Str) {
                emit_load_string(ACC, stringtable.lookup_string(""), s);    // 加载空字符串 la 
                emit_store(ACC, 3 + idx, SELF, s);                           // 存储到对象中
            } else if (attrib->type_decl == Int) {
                emit_load_int(ACC, inttable.lookup_string("0"), s);        // 加载整数0////la	$a0 int_const0
                emit_store(ACC, 3 + idx, SELF, s);                           // 存储到对象中////sw	$a0 12($s0)
            } else if (attrib->type_decl == Bool) {
                emit_load_bool(ACC, BoolConst(0), s);                        // 加载布尔值false
                emit_store(ACC, 3 + idx, SELF, s);                           // 存储到对象中
            }
        } else {
            /* 
             * 情况2：属性有初始化表达式
             * 
             * 我们需要：
             * 1. 创建环境对象，用于代码生成上下文
             * 2. 生成初始化表达式的代码
             * 3. 将表达式的结果（在ACC寄存器中）存储到对象的属性位置
             * 4. 如果使用垃圾回收，通知GC有新引用产生
             */
            Environment env;
            env.m_class_node = this;              // 设置当前类节点，用于符号查找
            
            // pDbg->debug2file(NORMAL) << "Generating code for attribute initialization: " << attrib->name;
            attrib->init->code(s, env);           // 生成初始化表达式的代码
            
            // 将表达式的结果存储到对象的属性位置
            emit_store(ACC, 3 + idx, SELF, s);
            
            /* 
             * 如果使用垃圾回收（cgen_Memmgr == 1），需要通知GC
             * _GenGC_Assign函数用于告诉垃圾回收器对象引用已更新
             * 参数：A1 = 属性地址，ACC = 新的属性值
             */
            if (cgen_Memmgr == 1) {
                emit_addiu(A1, SELF, 4 * (idx + 3), s);  // 计算属性地址
                emit_jal("_GenGC_Assign", s);             // 调用GC赋值函数
            }
            s << endl;
        }
    }

    /* 
     * 第七步：准备返回值
     * 
     * COOL的初始化函数返回初始化完成的对象引用
     * 对象地址已经保存在SELF寄存器中，我们将其复制到ACC寄存器
     * 作为函数的返回值
     */
    s << "\t# ret = SELF" << endl;
    emit_move(ACC, SELF, s);             // 将对象地址放入返回值寄存器
    s << endl;

    /* 
     * 第八步：恢复调用者的上下文
     * 
     * 在返回之前，我们需要恢复之前保存的寄存器值
     * 这样调用者可以继续执行而不受影响
     * 这是函数调用的标准清理过程
     */
    s << "\t# pop fp, s0, ra" << endl;
    emit_load(FP, 3, SP, s);             // 恢复帧指针
    emit_load(SELF, 2, SP, s);           // 恢复SELF寄存器
    emit_load(RA, 1, SP, s);             // 恢复返回地址
    emit_addiu(SP, SP, 12, s);           // 释放栈空间（向上移动12字节）
    s << endl;

    /* 
     * 第九步：返回调用者
     * 
     * 使用emit_return生成MIPS的返回指令
     * 程序将跳转到ra寄存器中保存的地址继续执行
     */
    s << "\t# return" << endl;
    emit_return(s);
    s << endl;
}

void CgenNode::code_methods(ostream& s) {
    std::vector<method_class*> methods = GetMethods();
    for (method_class* method : methods) {
        method->code(s, this);
    }
}

void CgenClassTable::code_protObjs() {
    std::vector<CgenNode*> class_nodes = GetClassNodes();
    for (CgenNode* class_node : class_nodes) {
        class_node->code_protObj(str);
    }
}

void CgenClassTable::code_class_inits() {
    std::vector<CgenNode*> class_nodes = GetClassNodes();
    for (CgenNode* class_node : class_nodes) {
        class_node->code_init(str);
    }
}

void CgenClassTable::code_class_methods() {
    std::vector<CgenNode*> class_nodes = GetClassNodes();
    for (CgenNode* class_node : class_nodes) {  ////每个表达式节点生成代码
        if (!class_node->basic()) { ////不需要为基本类生成代码，因为基本类的方法已经提前编写好了汇编代码，文件为trap.handler。
/*
- 基本类方法在trap.handler中预先实现
- 编译器生成的方法调用代码通过符号名称引用这些方法
- 链接器在spim最终执行时的链接阶段将符号引用与实际实现连接起来
*/
            class_node->code_methods(str);
        }
    }
}

CgenClassTable::CgenClassTable(Classes classes, ostream& s) : nds(NULL) , str(s) {  //// 传入的classes是一个类列表，每个类都是一个CgenNode对象。nds是一个指向CgenNode对象的指针列表，用于存储所有类的节点。
    enterscope();
    if (cgen_debug) {
        cout << "Building CgenClassTable" << endl;
    }
    install_basic_classes();
    install_classes(classes);
    build_inheritance_tree();
    
    std::map<Symbol, int> class_tags = GetClassTags();
    stringclasstag = class_tags[Str];
    intclasstag = class_tags[Int];
    boolclasstag = class_tags[Bool];

}

/*
 * install_basic_classes() - 安装COOL语言的基本类
 * 
 * 这个函数是COOL编译器代码生成阶段的核心初始化函数，负责安装COOL语言的内置基本类。
 * 这些基本类构成了COOL语言的运行时系统基础，为所有用户定义的类提供继承和使用的基准。
 * 
 * 基本类包括：Object（所有类的根）、IO（输入输出操作）、Int（整数类型）、
 * Bool（布尔类型）、Str（字符串类型），以及一些特殊的符号类。
 * 
 * 该函数在CgenClassTable构造函数中被调用，确保在代码生成之前，
 * 所有基本类都已经正确注册到符号表中，并建立了完整的继承层次结构。
 */
void CgenClassTable::install_basic_classes() {

    /* 
     * 为所有基本类设置统一的文件名标识
     * 这有助于调试和错误报告，表明这些类来自COOL运行时系统
     * stringtable.add_string()将字符串添加到全局字符串常量表中，确保内存高效使用
     */
    Symbol filename = stringtable.add_string("<basic class>");

    /*
     * 第一步：安装特殊的符号类
     * 
     * 这些类在符号表中存在，但不参与继承层次结构
     * 它们主要用于编译器内部处理和类型检查
     */

    /* 
     * No_class - 表示"无父类"的特殊符号
     * Object类使用No_class作为其父类，表示继承链的顶端
     * 这在语义分析阶段用于检测类定义的合法性
     */
    addid(No_class,
          new CgenNode(class_(No_class, No_class, nil_Features(), filename),
                       Basic, this));

    /* 
     * SELF_TYPE - 表示"自身类型"的特殊符号
     * 用于方法返回类型，表示返回调用该方法的对象的确切类型
     * 支持多态性，确保子类方法返回子类类型而非父类类型
     * 不能被重新定义或继承
     */
    addid(SELF_TYPE,
          new CgenNode(class_(SELF_TYPE, No_class, nil_Features(), filename),
                       Basic, this));

    /* 
     * prim_slot - 原始槽类型，用于基本数据类型的内部表示
     * 在代码生成阶段用于处理整数、布尔值等原始类型的存储
     * 这是编译器内部使用的特殊类型
     */
    addid(prim_slot,
          new CgenNode(class_(prim_slot, No_class, nil_Features(), filename),
                       Basic, this));   //// 原始槽类型，用于基本数据类型的内部表示

    /*
     * 第二步：安装Object类 - COOL类层次结构的根
     * 
     * Object是所有COOL类的最终父类，提供了所有对象的基本方法
     * 每个COOL对象都继承自Object，确保类型系统的完整性
     * 
     * Object类的方法：
     * - cool_abort(): 终止程序执行，用于运行时错误处理
     * - type_name(): 返回类名字符串，支持运行时类型识别
     * - copy(): 创建对象的浅拷贝，支持对象复制操作
     * 
     * 注意：基本类的方法体不需要在这里定义，它们已经内置在运行时系统中
     */
    install_class(
        new CgenNode(
            class_(Object,                    // 类名：Object
                   No_class,                  // 父类：无父类（根类）（或者说继承自空类）
                   append_Features(          // 方法列表：连接多个方法
                       append_Features(
                           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
                           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
                       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
                   filename),                 // 源文件标识
            Basic, this));                   // 类型：基本类

    /*
     * 第三步：安装IO类 - 输入输出操作类
     * 
     * IO类继承自Object，提供了所有输入输出操作的方法
     * 这是COOL程序与用户交互的主要接口
     * 
     * IO类的方法：
     * - out_string(Str): 输出字符串到标准输出，返回self支持链式调用
     * - out_int(Int): 输出整数到标准输出，返回self支持链式调用  
     * - in_string(): 从标准输入读取字符串，返回读取的字符串
     * - in_int(): 从标准输入读取整数，返回读取的整数
     * 
     * 设计特点：输出方法返回SELF_TYPE，支持链式调用如：out_string("Hello").out_int(42)
     */
    install_class(
        new CgenNode(
            class_(IO,                        // 类名：IO
                   Object,                    // 父类：Object
                   append_Features(          // 方法列表：连接多个方法
                       append_Features(
                           append_Features(
                               single_Features(method(out_string, single_Formals(formal(arg, Str)),
                                       SELF_TYPE, no_expr())),
                               single_Features(method(out_int, single_Formals(formal(arg, Int)),
                                       SELF_TYPE, no_expr()))),
                           single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
                       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
                   filename),                 // 源文件标识
            Basic, this));                   // 类型：基本类

    /*
     * 第四步：安装Int类 - 整数类型
     * 
     * Int类表示COOL语言的整数类型，继承自Object
     * 这是COOL的基本数据类型之一，用于存储整数值
     * 
     * Int类的结构：
     * - val属性：存储整数值，类型为prim_slot（原始槽类型）
     * - 没有定义方法，依赖Object类继承的基本方法
     * 
     * 注意：Int类是不可变的，创建后其值不能改变
     * 算术操作会创建新的Int对象而非修改现有对象
     */
    install_class(
        new CgenNode(
            class_(Int,                       // 类名：Int
                   Object,                    // 父类：Object
                   single_Features(attr(val, prim_slot, no_expr())), //// 单个属性：val，类型是prim_slot，用于直接存储值，no_expr()表示没有表达式初始化
                   filename),                 // 源文件标识
            Basic, this));                   // 类型：基本类

    /*
     * 第五步：安装Bool类 - 布尔类型
     * 
     * Bool类表示COOL语言的布尔类型，继承自Object
     * 用于存储真(true)或假(false)值
     * 
     * Bool类的结构：
     * - val属性：存储布尔值，类型为prim_slot（原始槽类型）
     * - 值约定：0表示false，非0表示true
     * - 没有定义方法，依赖Object类继承的基本方法
     */
    install_class(
        new CgenNode(
            class_(Bool, Object,              // 类名：Bool，父类：Object
                   single_Features(attr(val, prim_slot, no_expr())), // 单个属性：val
                   filename),                 // 源文件标识
            Basic, this));                     // 类型：基本类

    /*
     * 第六步：安装Str类 - 字符串类型
     * 
     * Str类表示COOL语言的字符串类型，继承自Object
     * 这是COOL的复杂数据类型，支持多种字符串操作
     * 
     * Str类的结构：
     * - val属性：字符串长度，类型为Int，缓存长度避免重复计算
     * - str_field属性：实际的字符串内容，类型为prim_slot
     * 
     * Str类的方法：
     * - length(): 返回字符串长度，使用缓存的val属性提高效率
     * - concat(arg: Str): 字符串连接，返回新字符串
     * - substr(arg: Int, arg2: Int): 子字符串提取，从指定位置开始指定长度
     * 
     * 设计特点：字符串是不可变的，所有操作都返回新的字符串对象
     */
    install_class(
        new CgenNode(
            class_(Str,                       // 类名：Str
                   Object,                    // 父类：Object
                   append_Features(          // 属性列表：连接多个属性
                       append_Features(
                           append_Features(
                               append_Features(
                                   single_Features(attr(val, Int, no_expr())),      //// 属性：长度，类型为Int类，无初始化表达式
                                   single_Features(attr(str_field, prim_slot, no_expr()))), //// 属性：字符串内容，原始槽类型
                               single_Features(method(length, nil_Formals(), Int, no_expr()))), //// 方法：获取长度，无形参，返回值为Int类，无初始化表达式
                           single_Features(method(concat,                           //// 方法：字符串连接，有一个参数arg，类型为Str类，返回值为Str类，无初始化表达式
                                           single_Formals(formal(arg, Str)),
                                           Str,
                                           no_expr()))),
                       single_Features(method(substr,                             // 方法：子字符串
                                       append_Formals(single_Formals(formal(arg, Int)),
                                               single_Formals(formal(arg2, Int))),
                                       Str,
                                       no_expr()))),
                   filename),                 // 源文件标识
            Basic, this));                   // 类型：基本类

}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_class(CgenNodeP nd) {  ////CgenNodeP nd是一个指向CgenNode对象的指针，一个CgenNode对象代表一个类，存储了类的所有信息，包括类名、父类、属性、方法等。
    Symbol name = nd->get_name();

    if (probe(name)) {
        return;
    }

    // The class name is legal, so add it to the list of classes
    // and the symbol table.
    nds = new List<CgenNode>(nd, nds);
    addid(name, nd);
}

void CgenClassTable::install_classes(Classes cs) {
    for (int i = cs->first(); cs->more(i); i = cs->next(i)) {   ////迭代器，遍历类列表，安装每个类
        install_class(new CgenNode(cs->nth(i), NotBasic, this));    ////这里的cs->nth实际上在解析的时候就已经“安装”好了，包含了类的完整信息（类名、父类、特征列表等），只需要我们注册进去（在符号表中注册类名到CgenNode的映射）。
    }
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree() { //// 构建继承树，将类列表中的每个类的父类指针设置为对应的CgenNode对象，即设置为对应的类。
    for (List<CgenNode> *l = nds; l; l = l->tl()) {
        set_relations(l->hd());
    }
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd) {  //// 用来设置一个类的父类指针和子类指针
    CgenNode* parent_node = probe(nd->get_parent()); //// 查找父类对应的CgenNode对象
    nd->set_parentnd(parent_node); //// 设置父类指针
    parent_node->add_child(nd); //// 添加子类指针
}

void CgenNode::add_child(CgenNodeP n) { ////用来添加一个类的子类指针，将其添加到子类列表中。
    children = new List<CgenNode>(n, children);
}

void CgenNode::set_parentnd(CgenNodeP p) {  ////用来设置一个类的父类指针，将其设置为对应的CgenNode对象，即设置为对应的类。
    assert(parentnd == NULL);
    assert(p != NULL);
    parentnd = p;
}



void CgenClassTable::code() {   //// 用来生成类的代码，包括全局数据、选择垃圾收集器、常量、类名表、对象表、调度表、原型对象、全局文本、对象初始化器和类方法。
    if (cgen_debug) {
        cout << "coding global data" << endl;
    }
    pDbg->debug2file(EVIDENT) << "starting CgenClassTable::code";
    pDbg->debug2file() << "generating global data";
    code_global_data(); //// 生成全局数据，包括字符串、整数、布尔值、类名表、对象表、调度表、原型对象、全局文本、对象初始化器和类方法。

    if (cgen_debug) {
        cout << "choosing gc" << endl;
    }
    pDbg->debug2file() << "generating gc";
    code_select_gc(); //// 选择垃圾收集器，默认是保守的垃圾收集器，也可以选择其他垃圾收集器，如标记-清除收集器。

    if (cgen_debug) {
        cout << "coding constants" << endl;
    }
    pDbg->debug2file() << "generating constants";
    code_constants();

    if (cgen_debug) {
        cout << "coding name table" << endl;
    }
    pDbg->debug2file() << "generating name table";
    code_class_nameTab();   //// 生成类名表（class_nameTab）

    if (cgen_debug) {
        cout << "coding object table" << endl;
    }
    pDbg->debug2file() << "generating object table";
    code_class_objTab();  //// 生成对象表（class_objTab），存放类原型地址+类初始化函数地址

    if (cgen_debug) {
        cout << "coding dispatch tables" << endl;
    }
    pDbg->debug2file() << "generating dispatch table";
    code_dispatchTab();    //// 生成调度表/方法分派表（dispatchTab），存放类方法地址
    //

    if (cgen_debug) {
        cout << "coding prototype objects" << endl;
    }
    pDbg->debug2file() << "generating prototype objects";
    code_protObjs();    //// 生成原型对象（proto），存放类标签、大小、分派表、默认值等

    if (cgen_debug) {
        cout << "coding global text" << endl;
    }
    pDbg->debug2file() << "generating global text";
    code_global_text();
    //// 生成全局文本段（.text段）的汇编代码
    //// 包括：堆起始符号、Main/Int/String/Bool的初始化入口、main方法入口等全局符号声明
    //                 Add your code to emit

//                 Add your code to emit
//                   - object initializer

    if (cgen_debug) {
        cout << "coding object initializers" << endl;
    }
    pDbg->debug2file() << "generating object initializers";
    code_class_inits(); ////负责为每个类生成初始化函数的代码
    /*
 * 初始化函数的主要职责是：
 * 1. 设置栈帧，保存调用者的上下文（fp, s0, ra）
 * 2. 初始化对象的父类部分（通过调用父类的初始化函数）
 * 3. 初始化对象的所有属性（包括默认值和自定义初始化表达式）
 * 4. 返回初始化完成的对象引用
    */

    if (cgen_debug) {
        cout << "coding class methods" << endl;
    }
    pDbg->debug2file() << "generating class methods";
    code_class_methods();   //// 生成表达式的方法调用代码
    //                   - the class methods
    //                   - etc...
    pDbg->debug2file(EVIDENT) << "ending CgenClassTable::code";
}


CgenNodeP CgenClassTable::root() {
    return probe(Object);
}


///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) :
    class__class((const class__class&) *nd),
    parentnd(NULL),
    children(NULL),
    basic_status(bstatus) {
    stringtable.add_string(name->get_string());          // Add class name to string table
}


//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************

/*
 * assign_class::code - 生成赋值语句的MIPS汇编代码
 * 
 * 功能：将表达式的值赋给指定的变量（let变量、参数或属性）
 * 实现逻辑：
 * 1. 首先计算右值表达式的值，结果存储在ACC寄存器中
 * 2. 通过Environment类查找变量的存储位置：
 *    - LookUpVar()：查找let语句引入的局部变量
 *    - LookUpParam()：查找方法参数
 *    - LookUpAttrib()：查找对象属性
 * 3. 根据变量类型将ACC中的值存储到相应位置
 * 4. 如果启用垃圾回收(cgen_Memmgr == 1)，调用_GenGC_Assign进行内存管理
 * 
 * 运行时布局：
 * - let变量：存储在栈上，偏移量基于SP寄存器
 * - 方法参数：存储在栈帧中，偏移量基于FP寄存器
 * - 对象属性：存储在对象实例中，偏移量基于SELF寄存器
 */
void assign_class::code(ostream& s, Environment env) {
    pDbg->debug2file() << "Assign. First eval the expr";
    expr->code(s, env);

    pDbg->debug2file() << "Now find the lvalue";
    int idx;

    if ((idx = env.LookUpVar(name)) != -1) {    ////这就说明变量是在env中局部定义的变量
        /*
在COOL编译器中，有三种变量存储位置：
- let 变量：通过 LookUpVar 查找，存储在栈上（存储let变量的变量名和引用，而给其赋值new出来的实例是存储在堆上的）
- 参数：通过 LookUpParam 查找，存储在栈帧中
- 对象属性：通过 LookUpAttrib 查找，存储在对象中
当使用 new 创建对象时：
1. 加载类的原型对象地址
2. 调用 Object.copy 复制原型对象（在堆上分配新对象）
3. 调用类的初始化方法
        */
        pDbg->debug2file() << "It is a let variable";
        emit_store(ACC, idx + 1, SP, s);
        if (cgen_Memmgr == 1) { ////是否启用垃圾回收器
            emit_addiu(A1, SP, 4 * (idx + 1), s);   //// 计算let变量在栈上的偏移量，从而获取let变量的地址
            emit_jal("_GenGC_Assign", s);
        }
    } else if ((idx = env.LookUpParam(name)) != -1){
        pDbg->debug2file() << "It is a param";
        emit_store(ACC, idx + 3, FP, s);
        if (cgen_Memmgr == 1) { 
            emit_addiu(A1, FP, 4 * (idx + 3), s);
            emit_jal("_GenGC_Assign", s);
        }
    }
    else if ((idx = env.LookUpAttrib(name)) != -1) {
        pDbg->debug2file() << "It is an attribute";
        emit_store(ACC, idx + 3, SELF, s);
        if (cgen_Memmgr == 1) {
            emit_addiu(A1, SELF, 4 * (idx + 3), s);
            emit_jal("_GenGC_Assign", s);
        }

    } else {
        pDbg->debug2file(EVIDENT) << "Error! assign to what?";
    }
}

/*
 * static_dispatch_class::code - 生成静态方法调用的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的静态方法调用（如@运算符）
 * 实现逻辑：
 * 1. 首先计算并保存所有实际参数的值到栈上
 * 2. 计算被调用对象的值，检查是否为void（空指针）
 * 3. 如果是void，调用_dispatch_abort进行错误处理
 * 4. 获取指定类的派发表(dispTab)地址
 * 5. 从派发表中获取目标方法的地址
 * 6. 通过jalr指令跳转到目标方法执行
 * 
 * 关键特点：
 * - 静态绑定：在编译时确定调用哪个类的方法
 * - 参数传递：通过栈传递实际参数
 * - 错误检查：运行时检查空指针
 * - 使用Environment管理作用域和栈布局
 */
void static_dispatch_class::code(ostream& s, Environment env) {
    s << "\t# Static dispatch. First eval and save the params." << endl;

    std::vector<Expression> actuals = GetActuals();
    for (Expression expr : actuals) {
        expr->code(s, env);
        emit_push(ACC, s);
        env.EnterScope();
        env.AddObstacle();
    }

    s << "\t# eval the obj in dispatch." << endl;
    expr->code(s, env);

    s << "\t# if obj = void: abort" << endl;
    emit_bne(ACC, ZERO, labelnum, s);
    s << LA << ACC << " str_const0" << endl;
    emit_load_imm(T1, 1, s);
    emit_jal("_dispatch_abort", s);

    emit_label_def(labelnum, s);
    ++labelnum;

    Symbol _class_name = type_name;
    CgenNode* _class_node = codegen_classtable->GetClassNode(type_name);
    s << "\t# Now we locate the method in the dispatch table." << endl;
    s << "\t# t1 = " << type_name << ".dispTab" << endl;

    std::string addr = type_name->get_string();
    addr += DISPTAB_SUFFIX;
    emit_load_address(T1, addr.c_str(), s);

    s << endl;

    int idx = _class_node->GetDispatchIdxTab()[name];
    s << "\t# t1 = dispTab[offset]" << endl;
    emit_load(T1, idx, T1, s);
    s << endl;

    s << "\t# jumpto " << name << endl;
    emit_jalr(T1, s);
    s << endl;

}

/*
 * dispatch_class::code - 生成动态方法调用的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的动态方法调用（虚函数调用）
 * 实现逻辑：
 * 1. 计算并保存所有实际参数的值到栈上
 * 2. 计算被调用对象的值，检查是否为void（空指针）
 * 3. 如果是void，调用_dispatch_abort进行错误处理
 * 4. 获取对象的实际类型（可能是表达式类型或当前类类型）
 * 5. 从对象的派发表(dispTab)中获取目标方法的地址
 * 6. 通过jalr指令跳转到目标方法执行
 * 
 * 关键特点：
 * - 动态绑定：运行时根据对象的实际类型确定调用哪个方法
 * - 多态支持：支持COOL语言的多态特性
 * - 错误检查：运行时检查空指针
 * - 使用Environment管理作用域和栈布局
 */
void dispatch_class::code(ostream& s, Environment env) {
    s << "\t# Dispatch. First eval and save the params." << endl;
    std::vector<Expression> actuals = GetActuals();

    for (Expression expr : actuals) {
        expr->code(s, env);
        emit_push(ACC, s);
        env.AddObstacle();
    }

    s << "\t# eval the obj in dispatch." << endl;
    expr->code(s, env);

    s << "\t# if obj = void: abort" << endl;
    emit_bne(ACC, ZERO, labelnum, s);
    s << LA << ACC << " str_const0" << endl;
    emit_load_imm(T1, 1, s);
    emit_jal("_dispatch_abort", s);

    emit_label_def(labelnum, s);
    ++labelnum;

    // Get current class name;
    Symbol _class_name = env.m_class_node->name;
    if (expr->get_type() != SELF_TYPE) {
        _class_name = expr->get_type();
    }

    CgenNode* _class_node = codegen_classtable->GetClassNode(_class_name);
    s << "\t# Now we locate the method in the dispatch table." << endl;
    s << "\t# t1 = self.dispTab" << endl;
    emit_load(T1, 2, ACC, s);
    s << endl;

    int idx = _class_node->GetDispatchIdxTab()[name];
    s << "\t# t1 = dispTab[offset]" << endl;
    emit_load(T1, idx, T1, s);
    s << endl;

    s << "\t# jumpto " << name << endl;
    emit_jalr(T1, s);
    s << endl;

}

/*
 * cond_class::code - 生成条件语句(if-then-else)的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的条件语句
 * 实现逻辑：
 * 1. 首先计算条件表达式的值
 * 2. 从布尔对象中提取整数值到T1寄存器
 * 3. 如果T1为0（false），跳转到false分支
 * 4. 否则执行then分支，执行完毕后跳转到finish标签
 * 5. false分支执行else表达式
 * 6. finish标签是代码结束位置
 * 
 * 控制流：
 * - 使用emit_beq实现条件跳转
 * - 使用emit_branch实现无条件跳转
 * - 使用标签(label)定义代码块位置
 */
void cond_class::code(ostream& s, Environment env) {
    s << "\t# If statement. First eval condition." << endl;
    pred->code(s, env);

    s << "\t# extract the bool content from acc to t1" << endl;
    emit_fetch_int(T1, ACC, s);
    s << endl;

    int labelnum_false = labelnum++;
    int labelnum_finish = labelnum++;
    // labelnum : false.
    // labelnum + 1: finish
    s << "\t# if t1 == 0 goto false" << endl;
    emit_beq(T1, ZERO, labelnum_false, s);
    s << endl;

    then_exp->code(s, env);

    s << "\t# jumpt finish" << endl;
    emit_branch(labelnum_finish, s);
    s << endl;

    s << "# False:" << endl;
    emit_label_def(labelnum_false, s);

    else_exp->code(s, env);

    s << "# Finish:" << endl;
    emit_label_def(labelnum_finish, s);

}

/*
 * loop_class::code - 生成循环语句(while)的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的while循环语句
 * 实现逻辑：
 * 1. 定义循环开始(start)和结束(finish)标签
 * 2. start标签处：计算循环条件表达式的值
 * 3. 从布尔对象中提取整数值到T1寄存器
 * 4. 如果T1为0（false），跳转到finish标签（循环结束）
 * 5. 否则执行循环体
 * 6. 无条件跳转回start标签（继续循环）
 * 7. finish标签处：将ACC设置为void（循环表达式的返回值）
 * 
 * 控制流：
 * - 使用条件跳转和无条件跳转实现循环
 * - 循环体至少执行0次（先判断后执行）
 */
void loop_class::code(ostream& s, Environment env) {
    int start = labelnum;
    int finish = labelnum + 1;
    labelnum += 2;

    s << "\t# While loop" << endl;
    s << "\t# start:" << endl;
    emit_label_def(start, s);

    s << "\t# ACC = pred" << endl;
    pred->code(s, env);

    s << "\t# extract int inside bool" << endl;
    emit_fetch_int(T1, ACC, s);
    s << endl;

    s << "\t# if pred == false jumpto finish" << endl;
    emit_beq(T1, ZERO, finish, s);
    s << endl;

    body->code(s, env);

    s << "\t# Jumpto start" << endl;
    emit_branch(start, s);

    s << "\t# Finish:" << endl;
    emit_label_def(finish, s);
    
    s << "\t# ACC = void" << endl;
    emit_move(ACC, ZERO, s);

}

/*
 * typcase_class::code - 生成类型分支(case)语句的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的case语句（类型分支）
 * 实现逻辑：
 * 1. 首先计算case表达式的值
 * 2. 检查表达式值是否为void，如果是则调用_case_abort2
 * 3. 获取对象的类型标签并存储到T1寄存器
 * 4. 生成类型匹配代码：按继承层次从上到下匹配
 * 5. 如果没有匹配项，调用_case_abort
 * 6. 为每个分支生成代码：
 *    - 创建新的作用域
 *    - 将匹配对象推入栈中
 *    - 执行分支表达式
 *    - 清理栈并跳转到结束位置
 * 
 * 算法特点：
 * - 支持继承层次匹配（子类匹配父类类型）
 * - 使用标签跳转实现分支选择
 * - 运行时类型检查确保类型安全
 */
void typcase_class::code(ostream& s, Environment env) {
    std::map<Symbol, int> _class_tags = codegen_classtable->GetClassTags();
    std::vector<CgenNode*> _class_nodes = codegen_classtable->GetClassNodes();
    
    s << "\t# case expr" << endl;
    s << "\t# First eval e0" << endl;
    expr->code(s, env);

    s << "\t# If e0 = void, abort" << endl;
    emit_bne(ACC, ZERO, labelnum, s);
    emit_load_address(ACC, "str_const0", s);
    emit_load_imm(T1, 1, s);
    emit_jal("_case_abort2", s);

    emit_label_def(labelnum, s);
    ++labelnum;

    s << "\t# T1 = type(acc)" << endl;
    emit_load(T1, 0, ACC, s);

    std::vector<branch_class*> _cases = GetCases();
    int labelbeg = labelnum;
    int finish = labelnum + _cases.size();
    int caseidx = 0;
    labelnum += _cases.size() + 1;

    auto GetChildrenTagsSet = [&](std::vector<int> __curr_tags) {
        std::vector<int> __children_tags; // for return.
        for (int __curr_tag : __curr_tags) { // find children of this class.
            CgenNode* __curr_node = _class_nodes[__curr_tag];
            std::vector<CgenNode*> __children_nodes = __curr_node->GetChildren();
            for (CgenNode* __children_node : __children_nodes) {
                int __children_tag = _class_tags[__children_node->name];
                if (std::find(__children_tags.begin(), __children_tags.end(), __children_tag) == __children_tags.end()) {
                    __children_tags.push_back(__children_tag);
                }
            }
        }
        return __children_tags;
    };

    auto HasFinished = [&](std::vector<std::vector<int> > __cases_tags) {
        for (std::vector<int> __case_tags : __cases_tags) {
            if (!__case_tags.empty()) {
                return false;
            }
        }
        return true;
    };

    // Generate first round cases_tags.
    std::vector<std::vector<int> > cases_tags;
    for (branch_class* _case : _cases) {
        Symbol _type_decl = _case->type_decl;
        int _class_tag = _class_tags[_type_decl];
        std::vector<int> case_tags = { _class_tag };
        cases_tags.push_back(case_tags);
    }

    while (!HasFinished(cases_tags)) {
        // Print cases_tags.
        for (int caseidx = 0; caseidx < cases_tags.size(); ++caseidx) {
            std::vector<int> case_tags = cases_tags[caseidx];
            for (int case_tag : case_tags) {
                s << "\t# tag = " << case_tag << " : goto case " << caseidx << endl;
                emit_load_imm(T2, case_tag, s);
                emit_beq(T1, T2, labelbeg + caseidx, s);
                s << endl;
            }
            
        }
        s << "\t# ----------------" << endl;

        for (int i = 0; i < cases_tags.size(); ++i) {
            cases_tags[i] = GetChildrenTagsSet(cases_tags[i]);
        }
    }

    s << "\t# No match" << endl;
    emit_jal("_case_abort", s);
    emit_branch(finish, s);
    
    for (branch_class* _case : _cases) {
        Symbol _name = _case->name;
        Symbol _type_decl = _case->type_decl;
        Expression _expr = _case->expr;

        s << "# eval expr " << caseidx << endl;
        emit_label_def(labelbeg + caseidx, s);
        env.EnterScope();
        env.AddVar(_name);
        emit_push(ACC, s);
        _expr->code(s, env);
        emit_addiu(SP, SP, 4, s);

        s << "\t# Jumpto finish" << endl;
        emit_branch(finish, s);
        ++caseidx;
    }

    s << "#finish:" << endl;
    emit_label_def(finish, s);
    s << endl;
}

/*
 * block_class::code - 生成代码块(block)的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的代码块（一系列按顺序执行的表达式）
 * 实现逻辑：
 * 1. 遍历代码块中的所有表达式
 * 2. 依次生成每个表达式的MIPS代码
 * 3. 每个表达式的结果存储在ACC寄存器中
 * 4. 代码块的值是最后一个表达式的值
 * 
 * 特点：
 * - 顺序执行：表达式按定义顺序执行
 * - 副作用累积：每个表达式都可能影响后续表达式
 * - 返回值：整个块的值是最后一个表达式的值
 */
void block_class::code(ostream& s, Environment env) {
    for (int i = body->first(); body->more(i); i = body->next(i)) {
        body->nth(i)->code(s, env);
    }
}

/*
 * let_class::code - 生成let绑定语句的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的let语句（局部变量绑定）
 * 实现逻辑：
 * 1. 首先计算初始化表达式的值
 * 2. 如果初始化表达式为空，为基本类型提供默认值
 *    - String类型：加载空字符串
 *    - Int类型：加载整数0
 *    - Bool类型：加载false
 * 3. 将初始化的值推入栈中
 * 4. 创建新的作用域并添加变量绑定
 * 5. 生成主体表达式的代码
 * 6. 清理栈（弹出变量值）
 * 
 * 作用域管理：
 * - 使用EnterScope()创建新作用域
 * - 使用AddVar()添加变量到符号表
 * - 自动管理变量的生命周期
 */
void let_class::code(ostream& s, Environment env) {
    s << "\t# Let expr" << endl;
    s << "\t# First eval init" << endl;
    init->code(s, env);

    if (init->IsEmpty()) {
        // We still need to deal with basic types.
        if (type_decl == Str) {
            emit_load_string(ACC, stringtable.lookup_string(""), s);
        } else if (type_decl == Int) {
            emit_load_int(ACC, inttable.lookup_string("0"), s);
        } else if (type_decl == Bool) {
            emit_load_bool(ACC, BoolConst(0), s);
        }
    }

    s << "\t# push" << endl;
    emit_push(ACC, s);
    s << endl;

    env.EnterScope();
    env.AddVar(identifier);

    body->code(s, env);

    s << "\t# pop" << endl;
    emit_addiu(SP, SP, 4, s);
    s << endl;
}

/*
 * plus_class::code - 生成整数加法运算的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数加法运算（e1 + e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 调用Object.copy创建新的Int对象作为结果
 * 4. 从栈中弹出e1的值到T1寄存器
 * 5. 将e2的值移到T2寄存器
 * 6. 从两个Int对象中提取整数值（偏移量3）
 * 7. 执行整数加法：T3 = T1 + T2
 * 8. 将结果存储到新Int对象中
 * 
 * 内存管理：
 * - 创建新的Int对象存储结果
 * - 使用AddObstacle()管理栈布局
 */
void plus_class::code(ostream& s, Environment env) {
    s << "\t# Int operation : Add" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2 and make a copy for result." << endl;
    e2->code(s, env);
    emit_jal("Object.copy", s);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    s << "\t# Extract the int inside the object." << endl;
    emit_load(T1, 3, T1, s);
    emit_load(T2, 3, T2, s);
    s << endl;

    s << "\t# Modify the int inside t2." << endl;
    emit_add(T3, T1, T2, s);
    emit_store(T3, 3, ACC, s);
    s << endl;

}

/*
 * sub_class::code - 生成整数减法运算的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数减法运算（e1 - e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 调用Object.copy创建新的Int对象作为结果
 * 4. 从栈中弹出e1的值到T1寄存器
 * 5. 将e2的值移到T2寄存器
 * 6. 从两个Int对象中提取整数值（偏移量3）
 * 7. 执行整数减法：T3 = T1 - T2
 * 8. 将结果存储到新Int对象中
 * 
 * 内存布局：
 * - Int对象结构：对象头(3字) + 整数值(1字)
 * - 整数值存储在偏移量3的位置
 * - 结果存储在新的Int对象中
 */
void sub_class::code(ostream& s, Environment env) {
    s << "\t# Int operation : Sub" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2 and make a copy for result." << endl;
    e2->code(s, env);
    emit_jal("Object.copy", s);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    s << "\t# Extract the int inside the object." << endl;
    emit_load(T1, 3, T1, s);
    emit_load(T2, 3, T2, s);
    s << endl;

    s << "\t# Modify the int inside t2." << endl;
    emit_sub(T3, T1, T2, s);
    emit_store(T3, 3, ACC, s);
    s << endl;

}

/*
 * mul_class::code - 生成整数乘法运算的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数乘法运算（e1 * e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 调用Object.copy创建新的Int对象作为结果
 * 4. 从栈中弹出e1的值到T1寄存器
 * 5. 将e2的值移到T2寄存器
 * 6. 从两个Int对象中提取整数值（偏移量3）
 * 7. 执行整数乘法：T3 = T1 * T2
 * 8. 将结果存储到新Int对象中
 * 
 * 寄存器使用：
 * - T1：左操作数的整数值
 * - T2：右操作数的整数值  
 * - T3：乘法结果
 * - ACC：结果对象引用
 */
void mul_class::code(ostream& s, Environment env) {
    s << "\t# Int operation : Mul" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2 and make a copy for result." << endl;
    e2->code(s, env);
    emit_jal("Object.copy", s);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    s << "\t# Extract the int inside the object." << endl;
    emit_load(T1, 3, T1, s);
    emit_load(T2, 3, T2, s);
    s << endl;

    s << "\t# Modify the int inside t2." << endl;
    emit_mul(T3, T1, T2, s);
    emit_store(T3, 3, ACC, s);
    s << endl;
}

/*
 * divide_class::code - 生成整数除法运算的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数除法运算（e1 / e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 调用Object.copy创建新的Int对象作为结果
 * 4. 从栈中弹出e1的值到T1寄存器
 * 5. 将e2的值移到T2寄存器
 * 6. 从两个Int对象中提取整数值（偏移量3）
 * 7. 执行整数除法：T3 = T1 / T2
 * 8. 将结果存储到新Int对象中
 * 
 * 注意事项：
 * - 整数除法结果向零取整
 * - 除数为零行为由MIPS架构定义
 * - 结果存储在新的Int对象中
 */
void divide_class::code(ostream& s, Environment env) {
    s << "\t# Int operation : Div" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2 and make a copy for result." << endl;
    e2->code(s, env);
    emit_jal("Object.copy", s);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    s << "\t# Extract the int inside the object." << endl;
    emit_load(T1, 3, T1, s);
    emit_load(T2, 3, T2, s);
    s << endl;

    s << "\t# Modify the int inside t2." << endl;
    emit_div(T3, T1, T2, s);
    emit_store(T3, 3, ACC, s);
    s << endl;

}

/*
 * neg_class::code - 生成整数取负运算的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数取负运算（-e1）
 * 实现逻辑：
 * 1. 计算操作数e1的值
 * 2. 调用Object.copy创建新的Int对象作为结果
 * 3. 从Int对象中提取整数值到T1寄存器（偏移量3）
 * 4. 执行取负运算：T1 = -T1
 * 5. 将结果存储到新的Int对象中
 * 
 * 特点：
 * - 一元运算：只需要一个操作数
 * - 创建新对象：不修改原操作数
 * - 结果类型：返回新的Int对象
 */
void neg_class::code(ostream& s, Environment env) {
    s << "\t# Neg" << endl;
    s << "\t# Eval e1 and make a copy for result" << endl;
    e1->code(s, env);
    emit_jal("Object.copy", s);
    s << endl;

    emit_load(T1, 3, ACC, s);
    emit_neg(T1, T1, s);
    emit_store(T1, 3, ACC, s);
    s << endl;

}

/*
 * lt_class::code - 生成整数小于比较的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数小于比较运算（e1 < e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 从栈中弹出e1的值到T1寄存器
 * 4. 将e2的值移到T2寄存器
 * 5. 从两个Int对象中提取整数值（偏移量3）
 * 6. 预设结果为true（加载BoolConst(1)）
 * 7. 如果T1 < T2，跳转到finish标签（保持true结果）
 * 8. 否则设置结果为false（加载BoolConst(0)）
 * 
 * 返回值：新的Bool对象（true或false）
 */
void lt_class::code(ostream& s, Environment env) {
    s << "\t# Int operation : Less than" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2." << endl;
    e2->code(s, env);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    s << "\t# Extract the int inside the object." << endl;
    emit_load(T1, 3, T1, s);
    emit_load(T2, 3, T2, s);
    s << endl;

    s << "\t# Pretend that t1 < t2" << endl;
    emit_load_bool(ACC, BoolConst(1), s);
    s << "\t# If t1 < t2 jumpto finish" << endl;
    emit_blt(T1, T2, labelnum, s);

    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(labelnum, s);

    ++labelnum;
}

/*
 * eq_class::code - 生成相等比较的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的相等比较运算（e1 = e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 从栈中弹出e1的值到T1寄存器
 * 4. 将e2的值移到T2寄存器
 * 5. 特殊处理基本类型（Int、String、Bool）：
 *    - 调用equality_test函数进行值比较
 * 6. 对于引用类型：
 *    - 预设结果为true（加载BoolConst(1)）
 *    - 如果T1 == T2（指针相等），跳转到finish标签
 *    - 否则设置结果为false（加载BoolConst(0)）
 * 
 * 特点：
 * - 基本类型按值比较
 * - 引用类型按引用比较
 * - 支持运行时类型检查
 */
void eq_class::code(ostream& s, Environment env) {
    s << "\t# equal" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2." << endl;
    e2->code(s, env);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    if (e1->type == Int || e1->type == Str || e1->type == Bool)
        if (e2->type == Int || e2->type == Str || e2->type == Bool) {
            emit_load_bool(ACC, BoolConst(1), s);
            emit_load_bool(A1, BoolConst(0), s);
            emit_jal("equality_test", s);
            return;
        }

    s << "\t# Pretend that t1 = t2" << endl;
    emit_load_bool(ACC, BoolConst(1), s);
    s << "\t# Compare the two pointers." << endl;
    emit_beq(T1, T2, labelnum, s);
    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(labelnum, s);
    ++labelnum;
}

/*
 * leq_class::code - 生成整数小于等于比较的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的整数小于等于比较运算（e1 <= e2）
 * 实现逻辑：
 * 1. 首先计算左操作数e1的值并推入栈中
 * 2. 计算右操作数e2的值
 * 3. 从栈中弹出e1的值到T1寄存器
 * 4. 将e2的值移到T2寄存器
 * 5. 从两个Int对象中提取整数值（偏移量3）
 * 6. 预设结果为true（加载BoolConst(1)）
 * 7. 如果T1 <= T2，跳转到finish标签（保持true结果）
 * 8. 否则设置结果为false（加载BoolConst(0)）
 * 
 * 返回值：新的Bool对象（true表示e1 <= e2，false表示e1 > e2）
 */
void leq_class::code(ostream& s, Environment env) {
    s << "\t# Int operation : Less or equal" << endl;
    s << "\t# First eval e1 and push." << endl;
    e1->code(s, env);
    emit_push(ACC, s);
    env.AddObstacle();
    s << endl;

    s << "\t# Then eval e2." << endl;
    e2->code(s, env);
    s << endl;

    s << "\t# Let's pop e1 to t1, move e2 to t2" << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(T1, 0, SP, s);
    emit_move(T2, ACC, s);
    s << endl;

    s << "\t# Extract the int inside the object." << endl;
    emit_load(T1, 3, T1, s);
    emit_load(T2, 3, T2, s);
    s << endl;

    s << "\t# Pretend that t1 < t2" << endl;
    emit_load_bool(ACC, BoolConst(1), s);
    s << "\t# If t1 < t2 jumpto finish" << endl;
    emit_bleq(T1, T2, labelnum, s);

    emit_load_bool(ACC, BoolConst(0), s);
    emit_label_def(labelnum, s);

    ++labelnum;
}

/*
 * comp_class::code - 生成布尔取反运算的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的布尔取反运算（not e1）
 * 实现逻辑：
 * 1. 计算布尔操作数e1的值
 * 2. 从Bool对象中提取整数值到T1寄存器（偏移量3）
 * 3. 预设结果为true（加载BoolConst(1)）
 * 4. 如果T1为0（false），跳转到finish标签（保持true结果）
 * 5. 否则设置结果为false（加载BoolConst(0)）
 * 
 * 真值表：
 * - not true = false
 * - not false = true
 * 
 * 特点：
 * - 一元运算：只需要一个布尔操作数
 * - 创建新的Bool对象存储结果
 */
void comp_class::code(ostream& s, Environment env) {
    s << "\t# the 'not' operator" << endl;
    s << "\t# First eval the bool" << endl;
    e1->code(s, env);

    s << "\t# Extract the int inside the bool" << endl;
    emit_load(T1, 3, ACC, s);

    s << "\t# Pretend ACC = false, then we need to construct true" << endl;
    emit_load_bool(ACC, BoolConst(1), s);

    s << "\t# If ACC = false, jumpto finish" << endl;
    emit_beq(T1, ZERO, labelnum, s);

    s << "\t# Load false" << endl;
    emit_load_bool(ACC, BoolConst(0), s);

    s << "\t# finish:" << endl;
    emit_label_def(labelnum, s);

    ++labelnum;

}

/*
 * int_const_class::code - 生成整数常量的MIPS汇编代码
 * 
 * 功能：加载整数常量到ACC寄存器
 * 实现逻辑：
 * 1. 从整数表(inttable)中查找常量字符串
 * 2. 调用emit_load_int加载整数对象到ACC寄存器
 * 
 * 整数常量处理：
 * - 所有整数常量都存储在全局整数表中
 * - 运行时创建对应的Int对象实例
 * - 对象包含整数类的元信息和实际的整数值
 */
void int_const_class::code(ostream& s, Environment env) {
    //
    // Need to be sure we have an IntEntry *, not an arbitrary Symbol
    //
    emit_load_int(ACC, inttable.lookup_string(token->get_string()), s);
}

/*
 * string_const_class::code - 生成字符串常量的MIPS汇编代码
 * 
 * 功能：加载字符串常量到ACC寄存器
 * 实现逻辑：
 * 1. 从字符串表(stringtable)中查找常量字符串
 * 2. 调用emit_load_string加载字符串对象到ACC寄存器
 * 
 * 字符串常量处理：
 * - 所有字符串常量都存储在全局字符串表中
 * - 运行时创建对应的String对象实例
 * - 对象包含字符串类的元信息和实际的字符串数据
 * - 支持字符串的不可变性
 */
void string_const_class::code(ostream& s, Environment env) {
    emit_load_string(ACC, stringtable.lookup_string(token->get_string()), s);
}

/*
 * bool_const_class::code - 生成布尔常量的MIPS汇编代码
 * 
 * 功能：加载布尔常量到ACC寄存器
 * 实现逻辑：
 * 1. 根据val的值（true或false）创建对应的BoolConst
 * 2. 调用emit_load_bool加载布尔对象到ACC寄存器
 * 
 * 布尔常量处理：
 * - true和false是预定义的布尔常量
 * - 运行时创建对应的Bool对象实例
 * - 对象包含布尔类的元信息和实际的布尔值（1或0）
 */
void bool_const_class::code(ostream& s, Environment env) {
    emit_load_bool(ACC, BoolConst(val), s);
}

/*
 * new__class::code - 生成对象创建(new)的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的new运算符（对象创建）
 * 实现逻辑：
 * 1. 处理SELF_TYPE特殊情况：
 *    - 加载类对象表(class_objTab)地址
 *    - 获取当前对象的类标签
 *    - 计算原型对象(protObj)地址
 *    - 复制原型对象
 *    - 调用类的初始化方法
 * 2. 处理普通类型：
 *    - 加载指定类的原型对象地址
 *    - 复制原型对象
 *    - 调用类的初始化方法
 * 
 * 对象创建过程：
 * - 原型对象包含类的默认属性值
 * - Object.copy创建对象实例
 * - 类初始化方法设置对象状态
 */
void new__class::code(ostream& s, Environment env) {
    if (type_name == SELF_TYPE) {
        emit_load_address(T1, "class_objTab", s);

        s << "\t# Find class tag." << endl;
        emit_load(T2, 0, SELF, s);
        s << endl;

        s << "\t# Mult 3: Get protObj." << endl;
        emit_sll(T2, T2, 3, s);
        s << endl;

        emit_addu(T1, T1, T2, s);

        s << "\t# Push." << endl;
        emit_push(T1, s);
        s << endl;

        s << "\t# Load protObj to ACC." << endl;
        emit_load(ACC, 0, T1, s);
        s << endl;

        emit_jal("Object.copy", s);

        s << "\t# Pop protObj addr." << endl;
        emit_load(T1, 1, SP, s);
        emit_addiu(SP, SP, 4, s);
        s << endl;

        s << "\t# Get init addr." << endl;
        emit_load(T1, 1, T1, s);
        s << endl;

        s << "\t# Goto init." << endl;
        emit_jalr(T1, s);
        s << endl;

        return;
    }

    std::string dest = type_name->get_string();
    dest += PROTOBJ_SUFFIX;
    emit_load_address(ACC, dest.c_str(), s);
    emit_jal("Object.copy", s);
    dest = type_name->get_string();
    dest += CLASSINIT_SUFFIX;
    emit_jal(dest.c_str(), s);
}

/*
 * isvoid_class::code - 生成void类型检查(isvoid)的MIPS汇编代码
 * 
 * 功能：实现COOL语言中的isvoid运算符（检查对象是否为void）
 * 实现逻辑：
 * 1. 计算表达式e1的值到ACC寄存器
 * 2. 将结果移动到T1寄存器
 * 3. 预设结果为false（加载BoolConst(0)）
 * 4. 检查T1是否为0（void指针）
 * 5. 如果为0，跳转到finish标签（保持false结果）
 * 6. 否则设置结果为true（加载BoolConst(1)）
 * 
 * void检查规则：
 * - 值为0表示void
 * - 非零值表示有效对象引用
 * - 返回新的Bool对象
 */
void isvoid_class::code(ostream& s, Environment env) {
    e1->code(s, env);

    s << "\t# t1 = acc" << endl;
    emit_move(T1, ACC, s);

    s << "\t# First pretend t1 = void: acc = bool(1)" << endl;
    emit_load_bool(ACC, BoolConst(1), s);

    s << "\t# if t1 = void: jumpto finish" << endl;
    emit_beq(T1, ZERO, labelnum, s);
    s << endl;

    s << "\t# acc != void" << endl;
    emit_load_bool(ACC, BoolConst(0), s);

    s << "# finish:" << endl;
    emit_label_def(labelnum, s);

    ++labelnum;
}

/*
 * no_expr_class::code - 生成空表达式的MIPS汇编代码
 * 
 * 功能：处理COOL语言中的空表达式（无操作）
 * 实现逻辑：
 * 不生成任何代码，保持当前状态
 * 
 * 应用场景：
 * - 默认参数值
 * - 占位表达式
 * - 语法分析中的空节点
 * 
 * 特点：
 * - 无代码生成
 * - 不影响寄存器状态
 * - 不改变程序控制流
 */
void no_expr_class::code(ostream& s, Environment env) {
    emit_move(ACC, ZERO, s);
}

/*
 * object_class::code - 生成对象引用的MIPS汇编代码
 * 
 * 功能：加载对象变量或self到ACC寄存器
 * 实现逻辑：
 * 1. 处理self引用：
 *    - 直接加载SELF寄存器值到ACC
 * 2. 处理普通变量：
 *    - 通过Environment查找变量位置
 *    - 根据变量类型（参数/let变量/属性）确定加载方式
 *    - 从栈或对象属性中加载值到ACC
 * 
 * 变量类型处理：
 * - 参数：从函数参数区域加载
 * - let变量：从let作用域栈帧加载
 * - 属性：从对象属性区域加载
 * - self：当前对象引用
 */
void object_class::code(ostream& s, Environment env) {
    s << "\t# Object:" << endl;
    int idx;

    if ((idx = env.LookUpVar(name)) != -1) {
        s << "\t# It is a let variable." << endl;
        emit_load(ACC, idx + 1, SP, s);
        if (cgen_Memmgr == 1) {
            emit_addiu(A1, SP, 4 * (idx + 1), s);
            emit_jal("_GenGC_Assign", s);
        }
    } else if ((idx = env.LookUpParam(name)) != -1) {
        s << "\t# It is a param." << endl;
        emit_load(ACC, idx + 3, FP, s);
        if (cgen_Memmgr == 1) {
            emit_addiu(A1, FP, 4 * (idx + 3), s);
            emit_jal("_GenGC_Assign", s);
        }
    } else if ((idx = env.LookUpAttrib(name)) != -1) {
        s << "\t# It is an attribute." << endl;
        emit_load(ACC, idx + 3, SELF, s);
        if (cgen_Memmgr == 1) {
            emit_addiu(A1, SELF, 4 * (idx + 3), s);
            emit_jal("_GenGC_Assign", s);
        }
    } else if (name == self) {
        s << "\t# It is self." << endl;
        emit_move(ACC, SELF, s);
    } else {
        s << "Error! object class" << endl;
    }

    s << endl;
}