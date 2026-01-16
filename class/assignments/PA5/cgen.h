#include <assert.h>
#include <stdio.h>
#include <stack>
#include <vector>
#include <list>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"
#include <type_traits>
#include <string>

enum Basicness {
    Basic,
    NotBasic
};
#define TRUE 1
#define FALSE 0

extern Symbol No_class;

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

class CgenClassTable : public SymbolTable<Symbol,CgenNode> {
private:
    List<CgenNode> *nds;
    ostream& str;
    int stringclasstag; //// 字符串类的标签，用来标识字符串类的对象，生成的MIPS代码为str_const<stringclasstag>
    int intclasstag;
    int boolclasstag;
    std::vector<CgenNode*> m_class_nodes;
    std::map<Symbol, int> m_class_tags;

// The following methods emit code for
// constants and global declarations.

    void code_global_data();
    void code_global_text();
    void code_bools(int);
    void code_select_gc();
    void code_constants();
    void code_class_nameTab();
    void code_class_objTab();
    void code_dispatchTab();
    void code_protObjs();
    void code_class_inits();
    void code_class_methods();
// The following creates an inheritance graph from
// a list of classes.  The graph is implemented as
// a tree of `CgenNode', and class names are placed
// in the base class symbol table.

    void install_basic_classes();
    void install_class(CgenNodeP nd);
    void install_classes(Classes cs);
    void build_inheritance_tree();
    void set_relations(CgenNodeP nd);
public:
    CgenClassTable(Classes, ostream& str);
    void Execute() {    //--可以删除
        code();
        exitscope();
    }
    void code();
    CgenNodeP root();
    std::vector<CgenNode*> GetClassNodes();
    std::map<Symbol, int> GetClassTags();
    CgenNode* GetClassNode(Symbol class_name) {
        GetClassNodes();
        return m_class_nodes[m_class_tags[class_name]];
    }

    

    
};

enum eDbgFmt {
    NORMAL,
    EASY,
    EVIDENT,
    ABOVE,
    BELOW,
};
class DebugFile {
public:
    DebugFile(ostream& str) : str(str) {}
private:
    DebugFile() = default;
    DebugFile(const DebugFile&) = delete;
    DebugFile& operator=(const DebugFile&) = delete;
    DebugFile(DebugFile&&) = delete;
    DebugFile& operator=(DebugFile&&) = delete;
    ostream& str;
    
    void writeToFile(const std::string& msg) {
        str << msg;
    }

    std::string formatMsg(const std::string& content, eDbgFmt format) {
        std::stringstream ss;
        switch (format) {
            case NORMAL:
                ss << "#== " << content << " ==" << std::endl;
                break;
            case EASY:
                ss << "# " << content << std::endl;
                break;
            case EVIDENT:
                ss << std::endl << std::endl << "#+++++ " << content << " +++++" << std::endl << std::endl << std::endl;
                break;
            case ABOVE: 
                ss << std::endl << "#vvvvv " << content << " vvvvv" << std::endl;
                break;
            case BELOW:
                ss << std::endl << "#^^^^^ " << content << " ^^^^^" << std::endl;
                break;
            default:
                ss << content << std::endl;
        }
        return ss.str();
    }

public:
    // 兼容const char*写法
    void debug2file(const char* str2file, eDbgFmt format = NORMAL) {
        writeToFile(formatMsg(str2file, format));
    }

    // 兼容std::string
    void debug2file(const std::string& str2file, eDbgFmt format = NORMAL) {
        writeToFile(formatMsg(str2file, format));
    }

    // 内部辅助类：支持<<链式拼接
    class Stream {
    private:
        eDbgFmt m_format;
        std::stringstream m_ss;
        DebugFile& dbg;

    public:
        explicit Stream(DebugFile& dbg, eDbgFmt format = NORMAL) : m_format(format), dbg(dbg) {}
        ~Stream() {
            dbg.writeToFile(dbg.formatMsg(m_ss.str(), m_format));
        }

        // 检测类型T是否支持ostream输出
        template<typename, typename = void>
        struct is_ostreamable : std::false_type {};

        template<typename T>
        struct is_ostreamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};

        template <typename T>
        std::enable_if_t<is_ostreamable<T>::value && !std::is_same_v<T, Symbol>, Stream&>
        operator<<(const T& data) {
            m_ss << data;
            return *this;
        }

        Stream& operator<<(std::ostream& (*func)(std::ostream&)) {
            func(m_ss); // 将 endl 应用于内部的 stringstream
            return *this;
        }

        Stream& operator<<(const Symbol& sym) {
            if (sym) {
                m_ss << sym->get_string();
            } else {
                m_ss << "<null Symbol>";
            }
            return *this;
        }
    };

    // 返回Stream对象（支持指定格式）
    Stream debug2file(eDbgFmt format = NORMAL) {
        return Stream(*this, format);
    }
};


class CgenNode : public class__class {
private:
    CgenNodeP parentnd;                        // Parent of class
    List<CgenNode> *children;                  // Children of class
    Basicness basic_status;                    // `Basic' if class is basic
    // `NotBasic' otherwise

public:
    CgenNode(Class_ c,
             Basicness bstatus,
             CgenClassTableP class_table);

    void add_child(CgenNodeP child);

    List<CgenNode>* get_children() {
        return children;
    }

    std::vector<CgenNode*> GetChildren() {
        std::vector<CgenNode*> ret;
        List<CgenNode>* _children = get_children();
        while (_children != nullptr) {
            ret.push_back(_children->hd());
            _children = _children->tl();
        }
        return ret;
    }

    void set_parentnd(CgenNodeP p);

    CgenNodeP get_parentnd() {
        return parentnd;
    }

    int basic() {
        return (basic_status == Basic);
    }

    void code_protObj(ostream& s);
    void code_init(ostream& s);
    void code_methods(ostream& s);

    std::vector<method_class*> GetMethods();
    std::vector<method_class*> m_methods;

    std::vector<method_class*> GetFullMethods();
    std::vector<method_class*> m_full_methods;

    std::map<Symbol, Symbol> GetDispatchClassTab();
    std::map<Symbol, Symbol> m_dispatch_class_tab;

    std::map<Symbol, int> GetDispatchIdxTab();
    std::map<Symbol, int> m_dispatch_idx_tab;

    std::vector<attr_class*> GetAttribs();
    std::vector<attr_class*> m_attribs;

    std::vector<attr_class*> GetFullAttribs();
    std::vector<attr_class*> m_full_attribs;

    std::map<Symbol, int> GetAttribIdxTab();
    std::map<Symbol, int> m_attrib_idx_tab;

    std::vector<CgenNode*> GetInheritance();
    std::vector<CgenNode*> inheritance;

    int class_tag;
};

class BoolConst
{
private:
    int val;
public:
    BoolConst(int);
    void code_def(ostream&, int boolclasstag);
    void code_ref(ostream&) const;
};


/*********************************************************************
 * Environment类 - 代码生成环境管理器
 * 
 * 作用：在COOL到MIPS代码生成过程中，管理变量、参数和属性的符号查找，
 *       维护作用域栈，提供符号到运行时位置的映射。
 * 
 * 设计原理：
 * 1. 采用栈式符号表，支持嵌套作用域（let表达式、代码块等）
 * 2. 区分三种符号类型：局部变量、函数参数、对象属性
 * 3. 提供运行时位置计算：栈偏移量、参数偏移量、属性偏移量
 * 
 * 使用场景：
 * - 所有表达式类的code()方法都需要Environment参数
 * - 变量引用时查找符号位置
 * - let表达式创建新作用域
 * - 函数调用时处理参数传递
 *********************************************************************/
class Environment {
public:
    /* 
     * 构造函数：初始化空环境
     * m_class_node初始化为nullptr，需要在实际使用前设置
     */
    Environment() : m_class_node(nullptr) {}

    /* 
     * 进入新作用域
     * 用于let表达式、代码块等创建新的变量作用域
     * 在栈顶添加新的作用域长度计数器（初始为0）
     */
    void EnterScope() {
        m_scope_lengths.push_back(0);
    }

    /* 
     * 退出当前作用域
     * 弹出栈顶作用域，删除该作用域中定义的所有变量
     * 与EnterScope()配对使用，实现作用域的栈式管理
     */
    void ExitScope() {
        for (int i = 0; i < m_scope_lengths[m_scope_lengths.size() - 1]; ++i) {
            m_var_idx_tab.pop_back();
        }
        m_scope_lengths.pop_back();
    }

    /* 
     * 查找对象属性
     * 在当前类及其父类的属性表中查找符号
     * 返回属性在对象中的偏移量（相对于对象基地址）
     * 未找到返回-1
     * 
     * 使用场景：self.attr、obj.attr等属性访问
     */
    int LookUpAttrib(Symbol sym) {
        std::map<Symbol, int> attrib_idx_tab = m_class_node->GetAttribIdxTab();
        if (attrib_idx_tab.find(sym) != attrib_idx_tab.end()) {
            return attrib_idx_tab[sym];
        }
        return -1;
    }

    /* 
     * 查找局部变量
     * 在当前作用域栈中从后往前查找（最近定义优先）
     * 返回变量在栈中的偏移量（相对于当前fp）
     * 未找到返回-1
     * 
     * 变量存储布局：
     * - 索引0：最近定义的变量（栈顶）
     * - 索引n：最早定义的变量（栈底）
     * - 偏移量计算：m_var_idx_tab.size() - 1 - idx
     */
    // The vars are in reverse order.
    int LookUpVar(Symbol sym) {
        for (int idx = m_var_idx_tab.size() - 1; idx >= 0; --idx) {
            if (m_var_idx_tab[idx] == sym) {
                return m_var_idx_tab.size() - 1 - idx;
            }
        }
        return -1;
    }

    /* 
     * 添加局部变量
     * 在当前作用域中添加新变量符号
     * 返回变量索引（内部使用，不直接对应运行时位置）
     * 同时更新当前作用域的变量计数器
     */
    int AddVar(Symbol sym) {
        m_var_idx_tab.push_back(sym);
        ++m_scope_lengths[m_scope_lengths.size() - 1];
        return m_var_idx_tab.size() - 1;
    }

    /* 
     * 添加栈障碍（参数传递时使用）
     * 在表达式求值过程中，当需要临时保存寄存器值时，
     * 添加障碍标记以区分表达式求值产生的临时值和真正的局部变量
     * 
     * 使用场景：函数参数求值、复杂表达式计算等
     */
    int AddObstacle();

    /* 
     * 查找函数参数
     * 在当前函数的参数列表中查找符号
     * 返回参数在栈中的偏移量（相对于当前fp）
     * 未找到返回-1
     * 
     * 参数存储布局：
     * - 参数从右到左依次压栈
     * - 参数1：fp + 8（跳过ra和fp）
     * - 参数2：fp + 12
     * - 参数n：fp + 8 + 4*(n-1)
     */
    int LookUpParam(Symbol sym) {
        for (int idx = 0; idx < m_param_idx_tab.size(); ++idx) {
            if (m_param_idx_tab[idx] == sym) {
                return m_param_idx_tab.size() - 1 - idx;
            }
        }
        return -1;
    }

    /* 
     * 添加函数参数
     * 在当前函数中添加新参数符号
     * 返回参数索引（从0开始，从左到右顺序）
     * 
     * 调用约定：
     * - 参数通过栈传递（MIPS O32调用约定）
     * - 调用者负责压栈和清理
     * - 被调用者通过fp访问参数
     */
    int AddParam(Symbol sym) {
        m_param_idx_tab.push_back(sym);
        return m_param_idx_tab.size() - 1;
    }

    /* 
     * 成员变量：作用域长度栈
     * 每个元素记录对应作用域中的变量数量
     * 用于ExitScope()时正确删除变量
     */
    std::vector<int> m_scope_lengths;

    /* 
     * 成员变量：变量符号表
     * 按定义顺序存储所有局部变量符号
     * 运行时位置通过索引计算得到
     */
    std::vector<Symbol> m_var_idx_tab;

    /* 
     * 成员变量：参数符号表
     * 按定义顺序存储函数参数符号
     * 与m_var_idx_tab分开管理，因为参数生命周期不同
     */
    std::vector<Symbol> m_param_idx_tab;

    /* 
     * 成员变量：当前类节点指针
     * 指向当前正在生成代码的类
     * 用于属性查找和类型信息获取
     * 必须在实际使用前设置（非nullptr）
     */
    CgenNode* m_class_node;

};