/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;
static int comment_level;

extern int curr_lineno;
extern int verbose_flag;

extern int yyleng;
extern char* yytext;

extern StrTable stringtable;
/*查看 stringtab.h可知不是含模板的类StringTable*/

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

%}

/*
 * Define names for regular expressions here.
 */
/* 第一部分：定义段 - Flex 配置（选项、状态、正则表达式） */
%option noyywrap
/* 禁用 yywrap() 函数（避免链接错误）*/
%option yylineno
/* 启用行号跟踪（curr_lineno 生效）*/

/* 状态声明（独占状态：仅匹配当前状态的规则） */
%x COMMENT
/* 注释处理状态 */
%x STRING
/*字符串处理状态*/

/*正则表达式定义、多字符运算符定义*/
DIGIT        [0-9]
LOWER        [a-z]
UPPER        [A-Z]	
/*a*/
LETTER       [a-zA-Z]
ALNUM        [a-zA-Z0-9_]  
/* 标识符允许字母、数字、下划线，这段注释必须放在这里（另起一行）*/
ASSIGN        <-           
/* 赋值操作符 */
LE            <=           
/* 小于等于 */

DARROW        =>					 
/* 箭头 */

%%
 /*在这一段写块标注*/
 /*
  *  Nested comments
  */
 /* 第二部分：规则段 - 词法规则（模式 + 动作） */
 /* 1. 空白字符处理（忽略空格、制表符，换行更新行号） */
[ \f\r\t\v]+    { /* 忽略空白字符 */ }
\n              { curr_lineno++; }  // 换行时行号+1

 /* 2. 关键字（大小写不敏感，如 class 可匹配 Class/CLASS） */
[cC][lL][aA][sS][sS]        { return CLASS; }
[eE][lL][sS][eE]            { return ELSE; }
[fF][iI]                    { return FI; }
[iI][fF]                    { return IF; }
[iI][nN]                    { return IN; }
[iI][nN][hH][eE][rR][iI][tT][sS] { return INHERITS; }
[iI][sS][vV][oO][iI][dD]    { return ISVOID; }
[lL][eE][tT]                { return LET; }
[lL][oO][oO][pP]            { return LOOP; }
[pP][oO][oO][lL]            { return POOL; }
[tT][hH][eE][nN]            { return THEN; }
[wW][hH][iI][lL][eE]        { return WHILE; }
[cC][aA][sS][eE]            { return CASE; }
[eE][sS][aA][cC]            { return ESAC; }
[nN][eE][wW]                { return NEW; }
[oO][fF]                    { return OF; }
[nN][oO][tT]                { return NOT; }

 /* 3. 布尔常量（必须小写开头） */
t[rR][uU][eE]                { cool_yylval.boolean = 1; return BOOL_CONST; }
f[aA][lL][sS][eE]            { cool_yylval.boolean = 0; return BOOL_CONST; }

 /* 4. 标识符（TYPEID 大写开头，OBJECTID 小写开头） */
{UPPER}{ALNUM}*              { 
                                cool_yylval.symbol = stringtable.add_string(yytext); 
                                return TYPEID; /* 类型标识符（如 Int、Main）*/
                              }
{LOWER}{ALNUM}*              { 
                                cool_yylval.symbol = stringtable.add_string(yytext); 
                                return OBJECTID;  // 对象标识符（如 x、self）
                              }

 /* 5. 整数常量（1+位数字） */
{DIGIT}+                     { 
                                cool_yylval.symbol = stringtable.add_string(yytext); 
                                return INT_CONST; 
                              }

 /* 6. 操作符与分隔符 这里面是可以在字符串外面出现的符号 */
{DARROW}                     { return DARROW; }
{ASSIGN}                     { return ASSIGN; }
{LE}                         { return LE; }
"--".*$                      { /* 忽略之后的一行内容，前面的$代表行末 */ }
"+"                          { return '+'; }
"-"                          { return '-'; }
"*"                          { return '*'; }
"/"                          { return '/'; }
"~"                          { return '~'; }
"<"                          { return '<'; }
"="                          { return '='; }
"."                          { return '.'; }
"@"                          { return '@'; }
","                          { return ','; }
";"                          { return ';'; }
"("                          { return '('; }
")"                          { return ')'; }
"{"                          { return '{'; }
"}"                          { return '}'; }
":"                          { return ':'; } /*对于不符合正则语法的字符可以不使用""包裹，比如":"可以写成:*/

 /* 7. 字符串处理（进入 STRING 状态，处理转义与边界） */
\"                           { 
                                BEGIN(STRING);          // 切换到字符串状态
                                string_buf_ptr = string_buf;  // 重置缓冲区指针
                              }
<STRING>\"                   { 
                                BEGIN(INITIAL);         // 退出字符串状态，回到初始状态
                                *string_buf_ptr = '\0'; // 字符串末尾加结束符
                                
                                // 检查字符串长度（避免缓冲区溢出）
                                if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
                                  cool_yylval.error_msg = "String constant too long";
                                  return ERROR;
                                }
                                
                                // 字符串加入字符串表，返回 STR_CONST
                                cool_yylval.symbol = stringtable.add_string(string_buf);
                                return STR_CONST;
                              }
<STRING>\n                   { 
                                BEGIN(INITIAL);         // 字符串跨行，报错
                                curr_lineno++;
                                cool_yylval.error_msg = "Unterminated string constant (encountered a newline)";
                                return ERROR;
                              }
<STRING><<EOF>>              { 
                                BEGIN(INITIAL);         // 字符串未结束遇到 EOF，报错
                                cool_yylval.error_msg = "EOF in string constant";
                                return ERROR;
                              }
<STRING>\\n                  { *string_buf_ptr++ = '\n'; }  // 转义：\n → 换行符
<STRING>\\t                  { *string_buf_ptr++ = '\t'; }  // 转义：\t → 制表符
<STRING>\\b                  { *string_buf_ptr++ = '\b'; }  // 转义：\b → 退格符
<STRING>\\f                  { *string_buf_ptr++ = '\f'; }  // 转义：\f → 换页符
<STRING>\\.                  { *string_buf_ptr++ = yytext[1]; }  // 其他转义（如 \\" → "）
<STRING>.                    { 
                                // 检查空字符（COOL 不允许字符串包含空字符）
                                if (yytext[0] == '\0') {
                                  cool_yylval.error_msg = "String contains null character";
                                  BEGIN(INITIAL);
                                  return ERROR;
                                }
                                // 检查长度，避免溢出
                                if (string_buf_ptr - string_buf >= MAX_STR_CONST - 1) {
                                  cool_yylval.error_msg = "String constant too long";
                                  BEGIN(INITIAL);
                                  return ERROR;
                                }
                                *string_buf_ptr++ = yytext[0];  // 普通字符加入缓冲区
                              }

 /* 8. 注释处理（支持嵌套，进入 COMMENT 状态） */
"(*"                         { 
                                BEGIN(COMMENT);         // 切换到注释状态
                                comment_level = 1;      // 初始化嵌套层级为 1
                              }
<COMMENT>"(*"                { comment_level++; }      // 嵌套注释：层级+1
<COMMENT>"*)"                { 
                                comment_level--;        // 嵌套注释：层级-1
                                if (comment_level == 0) {
                                  BEGIN(INITIAL);       // 层级为 0 时退出注释状态
                                }
                              }
<COMMENT><<EOF>>             { 
                                BEGIN(INITIAL);         // 注释未结束遇到 EOF，报错
                                cool_yylval.error_msg = "EOF in comment";
                                return ERROR;
                              }
<COMMENT>\n                  { curr_lineno++; }        // 注释内换行，更新行号
<COMMENT>.                   { /* 忽略注释内容 */ }

 /* 9. 错误处理（匹配所有未定义的字符，返回 ERROR） */
"*)"                           {
																cool_yylval.error_msg = "Unmatched \'*)\'";
                                return ERROR;
															}
.                            { 
                                cool_yylval.error_msg = yytext;  // 传递错误字符
                                return ERROR;
                              }



 /*
  *  The multiple-character operators.
  */
 /*{DARROW}		{ return (DARROW); }   !! defined before */

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */


%%

