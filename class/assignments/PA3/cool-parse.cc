/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cool_yyparse
#define yylex           cool_yylex
#define yyerror         cool_yyerror
#define yydebug         cool_yydebug
#define yynerrs         cool_yynerrs
#define yylval          cool_yylval
#define yychar          cool_yychar
#define yylloc          cool_yylloc

/* First part of user prologue.  */
#line 6 "cool.y"

  #include <iostream>
  #include "cool-tree.h"
  #include "stringtab.h"
  #include "utilities.h"

  extern char *curr_filename;


  /* Locations */
  #define YYLTYPE int              /* the type of locations */
  #define cool_yylloc curr_lineno  /* use the curr_lineno from the lexer
  for the location of tokens */

    extern int node_lineno;          /* set before constructing a tree node
    to whatever you want the line number
    for the tree node to be */


      #define YYLLOC_DEFAULT(Current, Rhs, N)         \
      Current = Rhs[1];                             \
      node_lineno = Current;


    #define SET_NODELOC(Current)  \
    node_lineno = Current;

    /* IMPORTANT NOTE ON LINE NUMBERS
    *********************************
    * The above definitions and macros cause every terminal in your grammar to
    * have the line number supplied by the lexer. The only task you have to
    * implement for line numbers to work correctly, is to use SET_NODELOC()
    * before constructing any constructs from non-terminals in your grammar.
    */



    void yyerror(char *s);        /*  defined below; called for each parse error */
    extern int yylex();           /*  the entry point to the lexer  */

    /************************************************************************/
    /*                DONT CHANGE ANYTHING IN THIS SECTION                  */

    Program ast_root;	      /* the result of the parse  */
    Classes parse_results;        /* for use in semantic analysis */
    int omerrs = 0;               /* number of errors in lexing and parsing */
    

#line 128 "cool.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "cool.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FI = 5,                         /* FI  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_IN = 7,                         /* IN  */
  YYSYMBOL_INHERITS = 8,                   /* INHERITS  */
  YYSYMBOL_LET = 9,                        /* LET  */
  YYSYMBOL_LOOP = 10,                      /* LOOP  */
  YYSYMBOL_POOL = 11,                      /* POOL  */
  YYSYMBOL_THEN = 12,                      /* THEN  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_CASE = 14,                      /* CASE  */
  YYSYMBOL_ESAC = 15,                      /* ESAC  */
  YYSYMBOL_OF = 16,                        /* OF  */
  YYSYMBOL_DARROW = 17,                    /* DARROW  */
  YYSYMBOL_NEW = 18,                       /* NEW  */
  YYSYMBOL_ISVOID = 19,                    /* ISVOID  */
  YYSYMBOL_STR_CONST = 20,                 /* STR_CONST  */
  YYSYMBOL_INT_CONST = 21,                 /* INT_CONST  */
  YYSYMBOL_BOOL_CONST = 22,                /* BOOL_CONST  */
  YYSYMBOL_TYPEID = 23,                    /* TYPEID  */
  YYSYMBOL_OBJECTID = 24,                  /* OBJECTID  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_LE = 27,                        /* LE  */
  YYSYMBOL_ERROR = 28,                     /* ERROR  */
  YYSYMBOL_29_ = 29,                       /* '<'  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '~'  */
  YYSYMBOL_36_ = 36,                       /* '@'  */
  YYSYMBOL_37_ = 37,                       /* '.'  */
  YYSYMBOL_38_ = 38,                       /* ';'  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* ':'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_class_list = 47,                /* class_list  */
  YYSYMBOL_class = 48,                     /* class  */
  YYSYMBOL_feature_list = 49,              /* feature_list  */
  YYSYMBOL_feature = 50,                   /* feature  */
  YYSYMBOL_formal_list = 51,               /* formal_list  */
  YYSYMBOL_formal = 52,                    /* formal  */
  YYSYMBOL_expr_block = 53,                /* expr_block  */
  YYSYMBOL_expr_list = 54,                 /* expr_list  */
  YYSYMBOL_case_list = 55,                 /* case_list  */
  YYSYMBOL_branch = 56,                    /* branch  */
  YYSYMBOL_expr = 57,                      /* expr  */
  YYSYMBOL_let_chain = 58                  /* let_chain  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   286

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    33,    31,    44,    32,    37,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    38,
      29,    30,     2,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,    35,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     2
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   133,   133,   137,   140,   143,   149,   153,   156,   166,
     167,   171,   174,   180,   186,   187,   189,   193,   198,   200,
     205,   206,   208,   212,   214,   218,   224,   227,   230,   233,
     236,   239,   242,   248,   253,   256,   259,   262,   265,   268,
     271,   274,   277,   280,   283,   286,   289,   292,   295,   298,
     301,   308,   315,   318,   325
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "ELSE", "FI",
  "IF", "IN", "INHERITS", "LET", "LOOP", "POOL", "THEN", "WHILE", "CASE",
  "ESAC", "OF", "DARROW", "NEW", "ISVOID", "STR_CONST", "INT_CONST",
  "BOOL_CONST", "TYPEID", "OBJECTID", "ASSIGN", "NOT", "LE", "ERROR",
  "'<'", "'='", "'+'", "'-'", "'*'", "'/'", "'~'", "'@'", "'.'", "';'",
  "'{'", "'}'", "'('", "')'", "':'", "','", "$accept", "program",
  "class_list", "class", "feature_list", "feature", "formal_list",
  "formal", "expr_block", "expr_list", "case_list", "branch", "expr",
  "let_chain", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-108)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-10)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,    -1,    30,    66,  -108,    -7,  -108,    18,  -108,    38,
       1,  -108,    25,    33,   -16,  -108,    32,     4,    36,    52,
     -14,  -108,    70,    92,  -108,  -108,    55,    74,    43,  -108,
      93,  -108,    96,    77,    70,    86,  -108,   100,  -108,    86,
     102,    86,    86,   101,    86,  -108,  -108,  -108,     8,    86,
      86,    86,    86,   238,    89,   153,    87,  -108,   130,   165,
    -108,   -18,    86,    86,   238,   -18,    62,   202,   176,    86,
      86,    86,    86,    86,    86,    86,   106,   107,    86,    86,
     110,    86,   119,   238,    47,   238,  -108,   214,  -108,  -108,
     249,   249,   249,    26,    26,   -18,   -18,   108,   114,   190,
     105,    -2,   141,   113,    -4,  -108,  -108,    86,  -108,   134,
      86,  -108,    86,    86,    86,   102,  -108,   146,  -108,  -108,
     238,   135,    69,   117,   238,    21,  -108,   162,    86,  -108,
    -108,    86,   102,    86,    72,   238,  -108,   226,  -108,  -108
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     3,     0,     1,     0,     4,     0,
       0,     5,     0,     0,     0,     9,     0,     0,     0,     0,
       0,     8,    14,     0,     6,    10,     0,     0,     0,    15,
      12,     7,     0,     0,     0,     0,    17,     0,    16,     0,
       0,     0,     0,     0,     0,    49,    48,    50,    47,     0,
       0,     0,     0,    13,     0,     0,     0,    33,     0,     0,
      35,    36,     0,    20,    45,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,    21,    32,     0,    18,    46,
      43,    42,    44,    37,    38,    39,    40,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    29,     0,    19,     0,
      20,    11,     0,     0,     0,     0,    31,     0,    34,    24,
      22,     0,     0,     0,    51,     0,    53,     0,    20,    27,
      30,     0,     0,     0,     0,    52,    54,     0,    28,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,   185,   178,  -108,  -108,   157,  -108,  -107,
    -108,   111,   -35,  -103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    14,    19,    28,    29,    66,    84,
     104,   105,    85,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,     9,    13,   122,    55,   113,    58,    59,    17,    61,
      17,   118,   126,     1,    64,    65,    67,    68,    76,    77,
     103,   134,     5,   114,    18,    -9,    26,    83,   131,   136,
       6,    87,    10,    62,    90,    91,    92,    93,    94,    95,
      96,    -9,   115,    99,   100,    22,   102,    23,    69,    63,
      70,    71,    72,    73,    74,    75,    11,    76,    77,    74,
      75,    12,    76,    77,    15,   132,    -2,     7,    39,     1,
      21,    40,   120,    16,    24,    41,    42,   123,   124,   125,
      43,    44,    45,    46,    47,    33,    48,    34,    49,   106,
      25,   107,    39,    31,    27,    40,   135,    50,   137,    41,
      42,    51,    86,    52,    43,    44,    45,    46,    47,   112,
      48,   129,    49,   107,   138,    30,   107,    32,    35,    36,
      37,    50,   130,    54,    60,    51,    56,    52,    78,    97,
      80,    98,    69,   101,    70,    71,    72,    73,    74,    75,
      81,    76,    77,   103,    69,   109,    70,    71,    72,    73,
      74,    75,   116,    76,    77,   110,   117,    69,   121,    70,
      71,    72,    73,    74,    75,    79,    76,    77,    69,   127,
      70,    71,    72,    73,    74,    75,   128,    76,    77,   133,
      69,    82,    70,    71,    72,    73,    74,    75,     8,    76,
      77,    38,    69,    20,    70,    71,    72,    73,    74,    75,
       0,    76,    77,    69,     0,    70,    71,    72,    73,    74,
      75,     0,    76,    77,     0,   119,     0,    69,    89,    70,
      71,    72,    73,    74,    75,     0,    76,    77,     0,    69,
     111,    70,    71,    72,    73,    74,    75,     0,    76,    77,
      88,    69,     0,    70,    71,    72,    73,    74,    75,     0,
      76,    77,   108,    69,     0,    70,    71,    72,    73,    74,
      75,     0,    76,    77,   139,    69,     0,    70,    71,    72,
      73,    74,    75,     0,    76,    77,   -10,     0,   -10,   -10,
      72,    73,    74,    75,     0,    76,    77
};

static const yytype_int16 yycheck[] =
{
      35,     8,     1,   110,    39,     7,    41,    42,    24,    44,
      24,    15,   115,     3,    49,    50,    51,    52,    36,    37,
      24,   128,    23,    25,    40,    24,    40,    62,     7,   132,
       0,    66,    39,    25,    69,    70,    71,    72,    73,    74,
      75,    40,    44,    78,    79,    41,    81,    43,    27,    41,
      29,    30,    31,    32,    33,    34,    38,    36,    37,    33,
      34,    23,    36,    37,    39,    44,     0,     1,     6,     3,
      38,     9,   107,    40,    38,    13,    14,   112,   113,   114,
      18,    19,    20,    21,    22,    42,    24,    44,    26,    42,
      38,    44,     6,    38,    24,     9,   131,    35,   133,    13,
      14,    39,    40,    41,    18,    19,    20,    21,    22,     4,
      24,    42,    26,    44,    42,    23,    44,    43,    25,    23,
      43,    35,     5,    23,    23,    39,    24,    41,    39,    23,
      43,    24,    27,    23,    29,    30,    31,    32,    33,    34,
      10,    36,    37,    24,    27,    37,    29,    30,    31,    32,
      33,    34,    11,    36,    37,    41,    43,    27,    24,    29,
      30,    31,    32,    33,    34,    12,    36,    37,    27,    23,
      29,    30,    31,    32,    33,    34,    41,    36,    37,    17,
      27,    16,    29,    30,    31,    32,    33,    34,     3,    36,
      37,    34,    27,    15,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    27,    -1,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    -1,   104,    -1,    27,    42,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    -1,    27,
      40,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    27,    -1,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    27,    -1,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    27,    -1,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    27,    -1,    29,    30,
      31,    32,    33,    34,    -1,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    46,    47,    48,    23,     0,     1,    48,     8,
      39,    38,    23,     1,    49,    39,    40,    24,    40,    50,
      49,    38,    41,    43,    38,    38,    40,    24,    51,    52,
      23,    38,    43,    42,    44,    25,    23,    43,    52,     6,
       9,    13,    14,    18,    19,    20,    21,    22,    24,    26,
      35,    39,    41,    57,    23,    57,    24,    58,    57,    57,
      23,    57,    25,    41,    57,    57,    53,    57,    57,    27,
      29,    30,    31,    32,    33,    34,    36,    37,    39,    12,
      43,    10,    16,    57,    54,    57,    40,    57,    38,    42,
      57,    57,    57,    57,    57,    57,    57,    23,    24,    57,
      57,    23,    57,    24,    55,    56,    42,    44,    38,    37,
      41,    40,     4,     7,    25,    44,    11,    43,    15,    56,
      57,    24,    54,    57,    57,    57,    58,    23,    41,    42,
       5,     7,    44,    17,    54,    57,    58,    57,    42,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    47,    48,    48,    48,    49,
      49,    50,    50,    50,    51,    51,    51,    52,    53,    53,
      54,    54,    54,    55,    55,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    58,    58,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     6,     8,     6,     0,
       3,     9,     3,     5,     0,     1,     3,     3,     2,     3,
       0,     1,     3,     1,     2,     6,     3,     6,     8,     4,
       7,     5,     3,     2,     5,     2,     2,     3,     3,     3,
       3,     2,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     5,     7,     5,     7
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: class_list  */
#line 133 "cool.y"
                                { (yyloc) = (yylsp[0]); ast_root = program((yyvsp[0].classes)); }
#line 1397 "cool.tab.c"
    break;

  case 3: /* class_list: class  */
#line 138 "cool.y"
    { (yyval.classes) = single_Classes((yyvsp[0].class_));
    parse_results = (yyval.classes); }
#line 1404 "cool.tab.c"
    break;

  case 4: /* class_list: class_list class  */
#line 141 "cool.y"
    { (yyval.classes) = append_Classes((yyvsp[-1].classes),single_Classes((yyvsp[0].class_)));
    parse_results = (yyval.classes); }
#line 1411 "cool.tab.c"
    break;

  case 5: /* class_list: class_list error ';'  */
#line 144 "cool.y"
    { (yyval.classes) = (yyvsp[-2].classes); 
      parse_results = (yyval.classes); }
#line 1418 "cool.tab.c"
    break;

  case 6: /* class: CLASS TYPEID '{' feature_list '}' ';'  */
#line 150 "cool.y"
    {   SET_NODELOC((yylsp[-5]));
        (yyval.class_) = class_((yyvsp[-4].symbol),idtable.add_string("Object"),(yyvsp[-2].features),
        stringtable.add_string(curr_filename)); }
#line 1426 "cool.tab.c"
    break;

  case 7: /* class: CLASS TYPEID INHERITS TYPEID '{' feature_list '}' ';'  */
#line 154 "cool.y"
    {   SET_NODELOC((yylsp[-7]));
        (yyval.class_) = class_((yyvsp[-6].symbol),(yyvsp[-4].symbol),(yyvsp[-2].features),stringtable.add_string(curr_filename)); }
#line 1433 "cool.tab.c"
    break;

  case 8: /* class: CLASS TYPEID '{' error '}' ';'  */
#line 157 "cool.y"
    {   yyerror("error in feature list");
        /* Error recovery: create a dummy class node */
        SET_NODELOC((yylsp[-5]));
        (yyval.class_) = class_((yyvsp[-4].symbol), idtable.add_string("Object"), nil_Features(), stringtable.add_string(curr_filename));
    }
#line 1443 "cool.tab.c"
    break;

  case 9: /* feature_list: %empty  */
#line 166 "cool.y"
    {  (yyval.features) = nil_Features(); }
#line 1449 "cool.tab.c"
    break;

  case 10: /* feature_list: feature_list feature ';'  */
#line 168 "cool.y"
    {  (yyval.features) = append_Features((yyvsp[-2].features), single_Features((yyvsp[-1].feature))); }
#line 1455 "cool.tab.c"
    break;

  case 11: /* feature: OBJECTID '(' formal_list ')' ':' TYPEID '{' expr '}'  */
#line 172 "cool.y"
    {   SET_NODELOC((yylsp[-8]));
        (yyval.feature) = method((yyvsp[-8].symbol), (yyvsp[-6].formals), (yyvsp[-3].symbol), (yyvsp[-1].expression)); }
#line 1462 "cool.tab.c"
    break;

  case 12: /* feature: OBJECTID ':' TYPEID  */
#line 175 "cool.y"
    {   int saved_line = node_lineno;
        node_lineno = 0;
        Expression no_expr_node = no_expr();
        node_lineno = (yylsp[-2]);  // 使用属性名的位置作为attr节点的行号
        (yyval.feature) = attr((yyvsp[-2].symbol), (yyvsp[0].symbol), no_expr_node); }
#line 1472 "cool.tab.c"
    break;

  case 13: /* feature: OBJECTID ':' TYPEID ASSIGN expr  */
#line 181 "cool.y"
    {   SET_NODELOC((yylsp[-4]));
        (yyval.feature) = attr((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression)); }
#line 1479 "cool.tab.c"
    break;

  case 14: /* formal_list: %empty  */
#line 186 "cool.y"
    {   (yyval.formals) = nil_Formals(); }
#line 1485 "cool.tab.c"
    break;

  case 15: /* formal_list: formal  */
#line 188 "cool.y"
    {   (yyval.formals) = single_Formals((yyvsp[0].formal)); }
#line 1491 "cool.tab.c"
    break;

  case 16: /* formal_list: formal_list ',' formal  */
#line 190 "cool.y"
    {   (yyval.formals) = append_Formals((yyvsp[-2].formals), single_Formals((yyvsp[0].formal))); }
#line 1497 "cool.tab.c"
    break;

  case 17: /* formal: OBJECTID ':' TYPEID  */
#line 194 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.formal) = formal((yyvsp[-2].symbol), (yyvsp[0].symbol)); }
#line 1504 "cool.tab.c"
    break;

  case 18: /* expr_block: expr ';'  */
#line 199 "cool.y"
    {   (yyval.expressions) = single_Expressions((yyvsp[-1].expression)); }
#line 1510 "cool.tab.c"
    break;

  case 19: /* expr_block: expr_block expr ';'  */
#line 201 "cool.y"
    {   (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[-1].expression))); }
#line 1516 "cool.tab.c"
    break;

  case 20: /* expr_list: %empty  */
#line 205 "cool.y"
    {   (yyval.expressions) = nil_Expressions(); }
#line 1522 "cool.tab.c"
    break;

  case 21: /* expr_list: expr  */
#line 207 "cool.y"
    {   (yyval.expressions) = single_Expressions((yyvsp[0].expression)); }
#line 1528 "cool.tab.c"
    break;

  case 22: /* expr_list: expr_list ',' expr  */
#line 209 "cool.y"
    {   (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[0].expression))); }
#line 1534 "cool.tab.c"
    break;

  case 23: /* case_list: branch  */
#line 213 "cool.y"
    {   (yyval.cases) = single_Cases((yyvsp[0].case_)); }
#line 1540 "cool.tab.c"
    break;

  case 24: /* case_list: case_list branch  */
#line 215 "cool.y"
    {   (yyval.cases) = append_Cases((yyvsp[-1].cases), single_Cases((yyvsp[0].case_))); }
#line 1546 "cool.tab.c"
    break;

  case 25: /* branch: OBJECTID ':' TYPEID DARROW expr ';'  */
#line 219 "cool.y"
    {   SET_NODELOC((yylsp[-5]));
        (yyval.case_) = branch((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression)); }
#line 1553 "cool.tab.c"
    break;

  case 26: /* expr: OBJECTID ASSIGN expr  */
#line 225 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = assign((yyvsp[-2].symbol), (yyvsp[0].expression)); }
#line 1560 "cool.tab.c"
    break;

  case 27: /* expr: expr '.' OBJECTID '(' expr_list ')'  */
#line 228 "cool.y"
    {   SET_NODELOC((yylsp[-5]));
        (yyval.expression) = dispatch((yyvsp[-5].expression), (yyvsp[-3].symbol), (yyvsp[-1].expressions)); }
#line 1567 "cool.tab.c"
    break;

  case 28: /* expr: expr '@' TYPEID '.' OBJECTID '(' expr_list ')'  */
#line 231 "cool.y"
    {   SET_NODELOC((yylsp[-7]));
        (yyval.expression) = static_dispatch((yyvsp[-7].expression), (yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expressions)); }
#line 1574 "cool.tab.c"
    break;

  case 29: /* expr: OBJECTID '(' expr_list ')'  */
#line 234 "cool.y"
    {   SET_NODELOC((yylsp[-3]));
        (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-3].symbol), (yyvsp[-1].expressions)); }
#line 1581 "cool.tab.c"
    break;

  case 30: /* expr: IF expr THEN expr ELSE expr FI  */
#line 237 "cool.y"
    {   SET_NODELOC((yylsp[-6]));
        (yyval.expression) = cond((yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 1588 "cool.tab.c"
    break;

  case 31: /* expr: WHILE expr LOOP expr POOL  */
#line 240 "cool.y"
    {   SET_NODELOC((yylsp[-4]));
        (yyval.expression) = loop((yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 1595 "cool.tab.c"
    break;

  case 32: /* expr: '{' expr_block '}'  */
#line 243 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = block((yyvsp[-1].expressions)); }
#line 1602 "cool.tab.c"
    break;

  case 33: /* expr: LET let_chain  */
#line 249 "cool.y"
    {   SET_NODELOC((yylsp[-1]));
        (yyval.expression) = (yyvsp[0].expression); }
#line 1609 "cool.tab.c"
    break;

  case 34: /* expr: CASE expr OF case_list ESAC  */
#line 254 "cool.y"
    {   SET_NODELOC((yylsp[-4]));
        (yyval.expression) = typcase((yyvsp[-3].expression), (yyvsp[-1].cases)); }
#line 1616 "cool.tab.c"
    break;

  case 35: /* expr: NEW TYPEID  */
#line 257 "cool.y"
    {   SET_NODELOC((yylsp[-1]));
        (yyval.expression) = new_((yyvsp[0].symbol)); }
#line 1623 "cool.tab.c"
    break;

  case 36: /* expr: ISVOID expr  */
#line 260 "cool.y"
    {   SET_NODELOC((yylsp[-1]));
        (yyval.expression) = isvoid((yyvsp[0].expression)); }
#line 1630 "cool.tab.c"
    break;

  case 37: /* expr: expr '+' expr  */
#line 263 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = plus((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1637 "cool.tab.c"
    break;

  case 38: /* expr: expr '-' expr  */
#line 266 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = sub((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1644 "cool.tab.c"
    break;

  case 39: /* expr: expr '*' expr  */
#line 269 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = mul((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1651 "cool.tab.c"
    break;

  case 40: /* expr: expr '/' expr  */
#line 272 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = divide((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1658 "cool.tab.c"
    break;

  case 41: /* expr: '~' expr  */
#line 275 "cool.y"
    {   SET_NODELOC((yylsp[-1]));
        (yyval.expression) = neg((yyvsp[0].expression)); }
#line 1665 "cool.tab.c"
    break;

  case 42: /* expr: expr '<' expr  */
#line 278 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = lt((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1672 "cool.tab.c"
    break;

  case 43: /* expr: expr LE expr  */
#line 281 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = leq((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1679 "cool.tab.c"
    break;

  case 44: /* expr: expr '=' expr  */
#line 284 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = eq((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1686 "cool.tab.c"
    break;

  case 45: /* expr: NOT expr  */
#line 287 "cool.y"
    {   SET_NODELOC((yylsp[-1]));
        (yyval.expression) = comp((yyvsp[0].expression)); }
#line 1693 "cool.tab.c"
    break;

  case 46: /* expr: '(' expr ')'  */
#line 290 "cool.y"
    {   SET_NODELOC((yylsp[-2]));
        (yyval.expression) = (yyvsp[-1].expression); }
#line 1700 "cool.tab.c"
    break;

  case 47: /* expr: OBJECTID  */
#line 293 "cool.y"
    {   SET_NODELOC((yylsp[0]));
        (yyval.expression) = object((yyvsp[0].symbol)); }
#line 1707 "cool.tab.c"
    break;

  case 48: /* expr: INT_CONST  */
#line 296 "cool.y"
    {   SET_NODELOC((yylsp[0]));
        (yyval.expression) = int_const((yyvsp[0].symbol)); }
#line 1714 "cool.tab.c"
    break;

  case 49: /* expr: STR_CONST  */
#line 299 "cool.y"
    {   SET_NODELOC((yylsp[0]));
        (yyval.expression) = string_const((yyvsp[0].symbol)); }
#line 1721 "cool.tab.c"
    break;

  case 50: /* expr: BOOL_CONST  */
#line 302 "cool.y"
    {   SET_NODELOC((yylsp[0]));
        (yyval.expression) = bool_const((yyvsp[0].boolean)); }
#line 1728 "cool.tab.c"
    break;

  case 51: /* let_chain: OBJECTID ':' TYPEID IN expr  */
#line 309 "cool.y"
    {   SET_NODELOC((yylsp[-4]));
        int saved_line = node_lineno;
        node_lineno = 0;
        Expression no_expr_node = no_expr();
        node_lineno = saved_line;
        (yyval.expression) = let((yyvsp[-4].symbol), (yyvsp[-2].symbol), no_expr_node, (yyvsp[0].expression)); }
#line 1739 "cool.tab.c"
    break;

  case 52: /* let_chain: OBJECTID ':' TYPEID ASSIGN expr IN expr  */
#line 316 "cool.y"
    {   SET_NODELOC((yylsp[-6]));
        (yyval.expression) = let((yyvsp[-6].symbol), (yyvsp[-4].symbol), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1746 "cool.tab.c"
    break;

  case 53: /* let_chain: OBJECTID ':' TYPEID ',' let_chain  */
#line 319 "cool.y"
    {   SET_NODELOC((yylsp[-4]));
        int saved_line = node_lineno;
        node_lineno = 0;
        Expression no_expr_node = no_expr();
        node_lineno = saved_line;
        (yyval.expression) = let((yyvsp[-4].symbol), (yyvsp[-2].symbol), no_expr_node, (yyvsp[0].expression)); }
#line 1757 "cool.tab.c"
    break;

  case 54: /* let_chain: OBJECTID ':' TYPEID ASSIGN expr ',' let_chain  */
#line 326 "cool.y"
    {   SET_NODELOC((yylsp[-6]));
        (yyval.expression) = let((yyvsp[-6].symbol), (yyvsp[-4].symbol), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1764 "cool.tab.c"
    break;


#line 1768 "cool.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 333 "cool.y"


    /* This function is called automatically when Bison detects a parse error. */
    void yyerror(char *s)
    {
      extern int curr_lineno;

      cerr << "\"" << curr_filename << "\", line " << curr_lineno << ": " \
      << s << " at or near ";
      print_cool_token(yychar);
      cerr << endl;
      omerrs++;

      if(omerrs>50) {fprintf(stdout, "More than 50 errors\n"); exit(1);}
    }
