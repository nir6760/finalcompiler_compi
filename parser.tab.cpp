/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"
 /* Declarations section */
	#include "helper.hpp"
	#include "Comp.hpp"
	#include "hw3_output.hpp"
	
	
	#include <iostream>
	#include <stdlib.h>
	#define YYDEBUG 1

	#include <tuple>

	using namespace std;
	using namespace output;
	extern int yylex();
	extern int yylineno;
	int yyerror(const char * message);
	extern size_t yyleng;

	static SymbolTable table; //save the symbol table with the hash
	// static StackScopes stack_scope;
	// static SymbolHash symbol_table_hash;

    static Comp comp(table); //class for tranlation to llvm

	static vector<cut_type*> curr_call_exps;
	static vector<cut_type*> nested_while;
	static vector<cut_type*> nested_switch;
	static vector<cut_type*> nested_break;



#line 104 "parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASSIGN = 3,                     /* ASSIGN  */
  YYSYMBOL_OR = 4,                         /* OR  */
  YYSYMBOL_AND = 5,                        /* AND  */
  YYSYMBOL_EQUALOP = 6,                    /* EQUALOP  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_NOT = 8,                        /* NOT  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_INT = 10,                       /* INT  */
  YYSYMBOL_BYTE = 11,                      /* BYTE  */
  YYSYMBOL_B = 12,                         /* B  */
  YYSYMBOL_BOOL = 13,                      /* BOOL  */
  YYSYMBOL_TRUE = 14,                      /* TRUE  */
  YYSYMBOL_FALSE = 15,                     /* FALSE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_BREAK = 18,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 19,                  /* CONTINUE  */
  YYSYMBOL_SWITCH = 20,                    /* SWITCH  */
  YYSYMBOL_CASE = 21,                      /* CASE  */
  YYSYMBOL_DEFAULT = 22,                   /* DEFAULT  */
  YYSYMBOL_COLON = 23,                     /* COLON  */
  YYSYMBOL_SC = 24,                        /* SC  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_ID = 26,                        /* ID  */
  YYSYMBOL_NUM = 27,                       /* NUM  */
  YYSYMBOL_STRING = 28,                    /* STRING  */
  YYSYMBOL_ENDOFFILE = 29,                 /* ENDOFFILE  */
  YYSYMBOL_RELOP = 30,                     /* RELOP  */
  YYSYMBOL_PLUS = 31,                      /* PLUS  */
  YYSYMBOL_MINUS = 32,                     /* MINUS  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_MULT = 34,                      /* MULT  */
  YYSYMBOL_LPAREN = 35,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 36,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 37,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 38,                    /* RBRACE  */
  YYSYMBOL_ELSE = 39,                      /* ELSE  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_Funcs = 42,                     /* Funcs  */
  YYSYMBOL_FuncDecl = 43,                  /* FuncDecl  */
  YYSYMBOL_FuncDeclBegin = 44,             /* FuncDeclBegin  */
  YYSYMBOL_RetType = 45,                   /* RetType  */
  YYSYMBOL_Formals = 46,                   /* Formals  */
  YYSYMBOL_FormalList = 47,                /* FormalList  */
  YYSYMBOL_FormalDecl = 48,                /* FormalDecl  */
  YYSYMBOL_Statements = 49,                /* Statements  */
  YYSYMBOL_Statement = 50,                 /* Statement  */
  YYSYMBOL_SwitchExp = 51,                 /* SwitchExp  */
  YYSYMBOL_SwitchOpen = 52,                /* SwitchOpen  */
  YYSYMBOL_OPENTHIS = 53,                  /* OPENTHIS  */
  YYSYMBOL_CLOSETHIS = 54,                 /* CLOSETHIS  */
  YYSYMBOL_WHILECHECKEXP = 55,             /* WHILECHECKEXP  */
  YYSYMBOL_WHILEOPENSCOPE = 56,            /* WHILEOPENSCOPE  */
  YYSYMBOL_MExp = 57,                      /* MExp  */
  YYSYMBOL_MStatement = 58,                /* MStatement  */
  YYSYMBOL_Call = 59,                      /* Call  */
  YYSYMBOL_ExpList = 60,                   /* ExpList  */
  YYSYMBOL_Type = 61,                      /* Type  */
  YYSYMBOL_Exp = 62,                       /* Exp  */
  YYSYMBOL_CaseList = 63,                  /* CaseList  */
  YYSYMBOL_CaseDeal = 64                   /* CaseDeal  */
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
typedef yytype_int8 yy_state_t;

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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    51,    51,    53,    54,    56,    64,    70,    71,    73,
      77,    81,    86,    91,    95,    98,   104,   105,   111,   114,
     127,   128,   131,   135,   139,   144,   151,   158,   163,   171,
     177,   179,   181,   183,   190,   192,   195,   198,   208,   215,
     222,   230,   231,   232,   234,   236,   240,   244,   249,   254,
     261,   262,   272,   283,   286,   287,   288,   292,   296,   300,
     303,   310,   314,   317,   319
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
  "\"end of file\"", "error", "\"invalid token\"", "ASSIGN", "OR", "AND",
  "EQUALOP", "IF", "NOT", "VOID", "INT", "BYTE", "B", "BOOL", "TRUE",
  "FALSE", "RETURN", "WHILE", "BREAK", "CONTINUE", "SWITCH", "CASE",
  "DEFAULT", "COLON", "SC", "COMMA", "ID", "NUM", "STRING", "ENDOFFILE",
  "RELOP", "PLUS", "MINUS", "DIV", "MULT", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "ELSE", "$accept", "Program", "Funcs", "FuncDecl",
  "FuncDeclBegin", "RetType", "Formals", "FormalList", "FormalDecl",
  "Statements", "Statement", "SwitchExp", "SwitchOpen", "OPENTHIS",
  "CLOSETHIS", "WHILECHECKEXP", "WHILEOPENSCOPE", "MExp", "MStatement",
  "Call", "ExpList", "Type", "Exp", "CaseList", "CaseDeal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     141,   -43,   -43,   -43,   -43,     4,   -22,   141,   146,   -17,
     -43,   -43,   -43,   -43,   -24,   216,   -19,     8,    24,   -13,
       2,   -43,   109,   -43,    26,    27,    19,   231,   231,   -43,
     -43,   -43,    30,    54,   -43,   231,   -43,    64,   231,   -43,
     -43,   231,   231,    -2,   146,   -43,   -43,   -43,     5,    10,
      31,   195,    52,   -43,    13,   231,   231,   231,   -43,   231,
     231,   231,   231,   231,    36,   195,    38,   195,   163,   -43,
      39,   173,   123,   231,   -43,    41,   -43,    53,    61,   146,
     -43,   179,    75,    52,   189,    -3,    -3,   -43,   -43,   -43,
      55,   -43,   -43,   231,   -43,   184,    62,    10,   -43,   -43,
      50,   146,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
      18,   146,    77,    68,    73,    18,   -43,    89,   146,   -43,
     -43,   146,   146,   146
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     8,    41,    42,    43,     0,     0,     4,     0,     0,
       7,     1,     2,     3,     0,     0,     0,     0,     0,     0,
       0,    31,     0,    15,     0,     0,     0,     0,     0,    54,
      55,    22,    49,    52,    53,     0,    50,     0,     0,    26,
      27,     0,     0,     0,     0,     5,    14,    20,     0,    10,
       0,    35,    56,    51,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,     0,    33,     0,    29,     0,    38,
       0,    40,     0,     0,    18,     0,     9,    12,     0,     0,
      44,    58,    57,    60,    59,    48,    47,    46,    45,    34,
       0,    19,    37,     0,    32,     0,     0,     0,    13,    36,
      23,     0,    30,    39,    16,    17,     6,    11,    31,    25,
       0,     0,     0,     0,     0,    62,    24,     0,     0,    28,
      61,     0,    63,    64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   110,   -43,   -43,   -43,   -43,    21,   -43,   -42,
     -21,   -43,   -43,    15,   -43,   -43,   -43,   -43,   -43,    -8,
      28,     3,     0,     9,   -43
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    75,    76,    77,    22,
      23,    66,   110,    44,   104,    64,   101,    50,   100,    36,
      70,    25,    71,   114,   115
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      24,    46,    72,    10,    11,    42,    28,    12,    73,    26,
      10,    27,    29,    30,    24,    37,    38,    55,    56,    57,
       2,     3,    41,     4,    32,    33,    34,    51,    52,    74,
      62,    63,    39,    35,    69,    54,    24,    43,    65,   112,
     113,    67,    68,    59,    60,    61,    62,    63,    40,    80,
      47,    46,    78,    48,    49,    81,    82,    83,    99,    84,
      85,    86,    87,    88,    24,    43,    53,    79,    55,    56,
      57,    24,    89,    95,    90,    92,   122,    96,    97,   123,
     109,    57,    59,    60,    61,    62,    63,    98,    58,   108,
     116,   118,   102,    24,    59,    60,    61,    62,    63,   106,
      78,    46,    46,    24,   117,    59,    60,    61,    62,    63,
      24,   119,   121,    24,    24,    24,    14,    13,   107,     2,
       3,   103,     4,   111,   120,    15,    16,    17,    18,    19,
      14,     0,     0,     2,     3,    20,     4,     0,     0,    15,
      16,    17,    18,    19,     0,     0,    21,    45,     0,    20,
       1,     2,     3,    14,     4,     0,     2,     3,     0,     4,
      21,    94,    15,    16,    17,    18,    19,    55,    56,    57,
       0,     0,    20,     0,     0,     0,     0,    55,    56,    57,
       0,     0,     0,    21,    56,    57,     0,    91,    55,    56,
      57,     0,     0,    59,    60,    61,    62,    63,    93,    55,
      56,    57,     0,    59,    60,    61,    62,    63,   105,    59,
      60,    61,    62,    63,    59,    60,    61,    62,    63,    -1,
      60,    61,    62,    63,    28,    59,    60,    61,    62,    63,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    28,
      31,     0,    32,    33,    34,    29,    30,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,    32,    33,    34,
       0,     0,     0,     0,     0,     0,    35
};

static const yytype_int8 yycheck[] =
{
       8,    22,    44,     0,     0,     3,     8,    29,     3,    26,
       7,    35,    14,    15,    22,    15,    35,     4,     5,     6,
      10,    11,    35,    13,    26,    27,    28,    27,    28,    24,
      33,    34,    24,    35,    36,    35,    44,    35,    38,    21,
      22,    41,    42,    30,    31,    32,    33,    34,    24,    36,
      24,    72,    49,    26,    35,    55,    56,    57,    79,    59,
      60,    61,    62,    63,    72,    35,    12,    36,     4,     5,
       6,    79,    36,    73,    36,    36,   118,    36,    25,   121,
     101,     6,    30,    31,    32,    33,    34,    26,    24,    39,
     111,    23,    37,   101,    30,    31,    32,    33,    34,    37,
      97,   122,   123,   111,    27,    30,    31,    32,    33,    34,
     118,    38,    23,   121,   122,   123,     7,     7,    97,    10,
      11,    93,    13,   108,   115,    16,    17,    18,    19,    20,
       7,    -1,    -1,    10,    11,    26,    13,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    -1,    37,    38,    -1,    26,
       9,    10,    11,     7,    13,    -1,    10,    11,    -1,    13,
      37,    38,    16,    17,    18,    19,    20,     4,     5,     6,
      -1,    -1,    26,    -1,    -1,    -1,    -1,     4,     5,     6,
      -1,    -1,    -1,    37,     5,     6,    -1,    24,     4,     5,
       6,    -1,    -1,    30,    31,    32,    33,    34,    25,     4,
       5,     6,    -1,    30,    31,    32,    33,    34,    24,    30,
      31,    32,    33,    34,    30,    31,    32,    33,    34,    30,
      31,    32,    33,    34,     8,    30,    31,    32,    33,    34,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      24,    -1,    26,    27,    28,    14,    15,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    11,    13,    41,    42,    43,    44,    45,
      61,     0,    29,    42,     7,    16,    17,    18,    19,    20,
      26,    37,    49,    50,    59,    61,    26,    35,     8,    14,
      15,    24,    26,    27,    28,    35,    59,    62,    35,    24,
      24,    35,     3,    35,    53,    38,    50,    24,    26,    35,
      57,    62,    62,    12,    62,     4,     5,     6,    24,    30,
      31,    32,    33,    34,    55,    62,    51,    62,    62,    36,
      60,    62,    49,     3,    24,    46,    47,    48,    61,    36,
      36,    62,    62,    62,    62,    62,    62,    62,    62,    36,
      36,    24,    36,    25,    38,    62,    36,    25,    26,    50,
      58,    56,    37,    60,    54,    24,    37,    47,    39,    50,
      52,    53,    21,    22,    63,    64,    50,    27,    23,    38,
      63,    23,    49,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    44,    45,    45,    46,
      46,    47,    47,    48,    49,    49,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    59,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    63,    63,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     3,     6,     1,     1,     1,
       0,     3,     1,     2,     2,     1,     5,     5,     3,     4,
       2,     3,     2,     5,     8,     6,     2,     2,     8,     1,
       0,     0,     0,     1,     0,     1,     1,     4,     3,     3,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     2,     1,     1,     1,     1,     2,     3,     3,     3,
       3,     2,     1,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
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
    goto yyexhaustedlab;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Funcs ENDOFFILE  */
#line 51 "parser.ypp"
                         {table.checkWasMain();}
#line 1273 "parser.tab.cpp"
    break;

  case 3: /* Funcs: FuncDecl Funcs  */
#line 53 "parser.ypp"
                       {}
#line 1279 "parser.tab.cpp"
    break;

  case 4: /* Funcs: %empty  */
#line 54 "parser.ypp"
                  {}
#line 1285 "parser.tab.cpp"
    break;

  case 5: /* FuncDecl: FuncDeclBegin Statements RBRACE  */
#line 56 "parser.ypp"
                                          {
	
						table.closeScope(true);
						/*comp.handle_one_statment($2); */
						comp.end_func(yyvsp[-2] ,yyvsp[-1]);
						
						}
#line 1297 "parser.tab.cpp"
    break;

  case 6: /* FuncDeclBegin: RetType ID LPAREN Formals RPAREN LBRACE  */
#line 64 "parser.ypp"
                                                       {
	table.addFunc(yyvsp[-4]->str, yyvsp[-5]->str, yyvsp[-2]->params_type, yyvsp[-2]->params_names );
	yyval = comp.handle_func(yyvsp[-5]->str, yyvsp[-4]->str, yyvsp[-2]->params_type, yyvsp[-2]->params_names);
	}
#line 1306 "parser.tab.cpp"
    break;

  case 7: /* RetType: Type  */
#line 70 "parser.ypp"
                {yyval=new cut_type();yyval->str = yyvsp[0]->str;}
#line 1312 "parser.tab.cpp"
    break;

  case 8: /* RetType: VOID  */
#line 71 "parser.ypp"
                  {yyval=new cut_type();yyval->str = "VOID";}
#line 1318 "parser.tab.cpp"
    break;

  case 9: /* Formals: FormalList  */
#line 73 "parser.ypp"
                      {yyval=new cut_type();
	yyval->params_type = yyvsp[0]->params_type;
	yyval->params_names = yyvsp[0]->params_names;
}
#line 1327 "parser.tab.cpp"
    break;

  case 10: /* Formals: %empty  */
#line 77 "parser.ypp"
                                    {yyval=new cut_type();
				yyval->params_type = {};
				yyval->params_names = {};}
#line 1335 "parser.tab.cpp"
    break;

  case 11: /* FormalList: FormalDecl COMMA FormalList  */
#line 81 "parser.ypp"
                                        {yyval=new cut_type();
				yyval->params_type = yyvsp[-2]->params_type;
				table.mergeVectors(yyval->params_type,yyvsp[0]->params_type );
             	yyval->params_names = yyvsp[-2]->params_names;
				table.mergeVectors(yyval->params_names,yyvsp[0]->params_names );}
#line 1345 "parser.tab.cpp"
    break;

  case 12: /* FormalList: FormalDecl  */
#line 86 "parser.ypp"
                                   {yyval=new cut_type();
						yyval->params_type = yyvsp[0]->params_type; 
						yyval->params_names = yyvsp[0]->params_names;}
#line 1353 "parser.tab.cpp"
    break;

  case 13: /* FormalDecl: Type ID  */
#line 91 "parser.ypp"
                    {yyval=new cut_type();
					yyval->params_names = {yyvsp[0]->str};
					 yyval->params_type = {yyvsp[-1]->str};}
#line 1361 "parser.tab.cpp"
    break;

  case 14: /* Statements: Statements Statement  */
#line 95 "parser.ypp"
                                    {
	
				yyval = comp.handle_statments(yyvsp[-1], yyvsp[0]);}
#line 1369 "parser.tab.cpp"
    break;

  case 15: /* Statements: Statement  */
#line 98 "parser.ypp"
                                          {
					yyval = yyvsp[0];
					}
#line 1377 "parser.tab.cpp"
    break;

  case 16: /* Statement: LBRACE OPENTHIS Statements RBRACE CLOSETHIS  */
#line 104 "parser.ypp"
                                                        {yyval=yyvsp[-2];}
#line 1383 "parser.tab.cpp"
    break;

  case 17: /* Statement: Type ID ASSIGN Exp SC  */
#line 105 "parser.ypp"
                                              {
								 table.insertVarToSymbolTable(yyvsp[-3]->str, yyvsp[-4]->str);
								 table.checkValidTypes(yyvsp[-4]->str, yyvsp[-1]->str);
								 table.checkValidCast(yyvsp[-4]->str, yyvsp[-1]->str);
								 yyval = comp.handle_decl(yyvsp[-4], yyvsp[-3]->str, yyvsp[-1]);
								 }
#line 1394 "parser.tab.cpp"
    break;

  case 18: /* Statement: Type ID SC  */
#line 111 "parser.ypp"
                       {
				table.insertVarToSymbolTable(yyvsp[-1]->str, yyvsp[-2]->str);
				yyval = comp.handle_decl(yyvsp[-2], yyvsp[-1]->str, nullptr);}
#line 1402 "parser.tab.cpp"
    break;

  case 19: /* Statement: ID ASSIGN Exp SC  */
#line 114 "parser.ypp"
                             {
				
				table.checkValidID(yyvsp[-3]->str);
				 
				string id_name = yyvsp[-3]->str;
				
				yyvsp[-3]->str = table.typeOfSym(yyvsp[-3]->str);
				
			
				
				table.checkValidTypes(yyvsp[-3]->str, yyvsp[-1]->str);
				yyval = comp.handle_ass(id_name, yyvsp[-1]);
				}
#line 1420 "parser.tab.cpp"
    break;

  case 20: /* Statement: Call SC  */
#line 127 "parser.ypp"
                    {yyval=yyvsp[-1];}
#line 1426 "parser.tab.cpp"
    break;

  case 21: /* Statement: RETURN Exp SC  */
#line 128 "parser.ypp"
                          {table.checkRetType(yyvsp[-1]->str);
							yyval = comp.handle_return(yyvsp[-1]);
							}
#line 1434 "parser.tab.cpp"
    break;

  case 22: /* Statement: RETURN SC  */
#line 131 "parser.ypp"
                                  {table.checkVoidRetType();
						yyval = comp.handle_return(nullptr);
						}
#line 1442 "parser.tab.cpp"
    break;

  case 23: /* Statement: IF LPAREN MExp RPAREN MStatement  */
#line 135 "parser.ypp"
                                                         {

				yyval = comp.handle_only_if(yyvsp[-2], yyvsp[0]);
				}
#line 1451 "parser.tab.cpp"
    break;

  case 24: /* Statement: IF LPAREN MExp RPAREN MStatement ELSE OPENTHIS Statement  */
#line 140 "parser.ypp"
                                                {
						table.closeScope(true);
						yyval = comp.handle_if_else(yyvsp[-5], yyvsp[-3],yyvsp[0]);
						}
#line 1460 "parser.tab.cpp"
    break;

  case 25: /* Statement: WHILE LPAREN WHILECHECKEXP RPAREN WHILEOPENSCOPE Statement  */
#line 144 "parser.ypp"
                                                                       {
				table.closeScope(true);
				
				yyval = comp.handle_while(yyvsp[-3], yyvsp[0], nested_break.back());
				nested_while.pop_back();
				nested_break.pop_back();
				}
#line 1472 "parser.tab.cpp"
    break;

  case 26: /* Statement: BREAK SC  */
#line 151 "parser.ypp"
                     {
				
				table.checkUnexpected("BREAK");
				
				yyval = comp.handle_break(nested_break.back());
				
			}
#line 1484 "parser.tab.cpp"
    break;

  case 27: /* Statement: CONTINUE SC  */
#line 158 "parser.ypp"
                        {
				table.checkUnexpected("CONTINUE");
				yyval = comp.handle_continue(nested_while.back());
				}
#line 1493 "parser.tab.cpp"
    break;

  case 28: /* Statement: SWITCH LPAREN SwitchExp RPAREN LBRACE SwitchOpen CaseList RBRACE  */
#line 163 "parser.ypp"
                                                                             {
				
				table.closeScope(true);
				yyval = comp.handle_switch(yyvsp[-5], yyvsp[-1], nested_break.back());
				nested_break.pop_back();
			}
#line 1504 "parser.tab.cpp"
    break;

  case 29: /* SwitchExp: Exp  */
#line 171 "parser.ypp"
                           {
	table.isIntByte(yyvsp[0]->str); 
	yyval=yyvsp[0];
	nested_break.push_back(new cut_type());
}
#line 1514 "parser.tab.cpp"
    break;

  case 30: /* SwitchOpen: %empty  */
#line 177 "parser.ypp"
                {table.openScope(false,true);}
#line 1520 "parser.tab.cpp"
    break;

  case 31: /* OPENTHIS: %empty  */
#line 179 "parser.ypp"
                        {table.openScope(false,false);}
#line 1526 "parser.tab.cpp"
    break;

  case 32: /* CLOSETHIS: %empty  */
#line 181 "parser.ypp"
                        {table.closeScope(true);}
#line 1532 "parser.tab.cpp"
    break;

  case 33: /* WHILECHECKEXP: Exp  */
#line 183 "parser.ypp"
                           {
		table.isBool(yyvsp[0]->str);
		nested_while.push_back(yyvsp[0]);
		nested_break.push_back(new cut_type());
		yyval = yyvsp[0];
		}
#line 1543 "parser.tab.cpp"
    break;

  case 34: /* WHILEOPENSCOPE: %empty  */
#line 190 "parser.ypp"
                        {table.openScope(true,false);}
#line 1549 "parser.tab.cpp"
    break;

  case 35: /* MExp: Exp  */
#line 192 "parser.ypp"
           {table.isBool(yyvsp[0]->str);table.openScope(false,false);
			yyval = yyvsp[0];}
#line 1556 "parser.tab.cpp"
    break;

  case 36: /* MStatement: Statement  */
#line 195 "parser.ypp"
                         {table.closeScope(true);
						yyval=yyvsp[0];}
#line 1563 "parser.tab.cpp"
    break;

  case 37: /* Call: ID LPAREN ExpList RPAREN  */
#line 198 "parser.ypp"
                                {
									
									table.checkFuncDecl(yyvsp[-3]->str, yyvsp[-1]->params_names);
									
									yyval=new cut_type();
									yyval->str = table.typeOfSym(yyvsp[-3]->str);
									yyval = comp.handle_call(yyvsp[-3]->str, curr_call_exps);

									curr_call_exps={};
									}
#line 1578 "parser.tab.cpp"
    break;

  case 38: /* Call: ID LPAREN RPAREN  */
#line 208 "parser.ypp"
                         {	table.checkFuncDecl(yyvsp[-2]->str, vector<string>());
							yyval=new cut_type();
							yyval->str =table.typeOfSym(yyvsp[-2]->str);
							yyval = comp.handle_call(yyvsp[-2]->str, curr_call_exps);
							curr_call_exps = {};
							 }
#line 1589 "parser.tab.cpp"
    break;

  case 39: /* ExpList: Exp COMMA ExpList  */
#line 215 "parser.ypp"
                                 {
							yyval=new cut_type();yyval->params_names = {yyvsp[-2]->str};
							 table.mergeVectors(yyval->params_names,yyvsp[0]->params_names );
							 curr_call_exps.push_back(yyvsp[-2]);
							 
    								
							 }
#line 1601 "parser.tab.cpp"
    break;

  case 40: /* ExpList: Exp  */
#line 222 "parser.ypp"
                            {
			yyval=new cut_type();
			yyval->params_names = {yyvsp[0]->str};

			curr_call_exps.push_back(yyvsp[0]);
			}
#line 1612 "parser.tab.cpp"
    break;

  case 41: /* Type: INT  */
#line 230 "parser.ypp"
          {yyval = yyvsp[0];}
#line 1618 "parser.tab.cpp"
    break;

  case 42: /* Type: BYTE  */
#line 231 "parser.ypp"
             {yyval = yyvsp[0];}
#line 1624 "parser.tab.cpp"
    break;

  case 43: /* Type: BOOL  */
#line 232 "parser.ypp"
             {yyval = yyvsp[0];}
#line 1630 "parser.tab.cpp"
    break;

  case 44: /* Exp: LPAREN Exp RPAREN  */
#line 234 "parser.ypp"
                       {yyval = yyvsp[-1]; 
					/*only cast from byte to int allowed*/}
#line 1637 "parser.tab.cpp"
    break;

  case 45: /* Exp: Exp MULT Exp  */
#line 236 "parser.ypp"
                 {table.checkValidNumeric(yyvsp[-2]->str, yyvsp[0]->str);
					yyval=new cut_type();
				  yyval->str =table.findExpType(yyvsp[-2]->str, yyvsp[0]->str);
				  yyval = comp.expBin(*yyvsp[-2], "mul", *yyvsp[0]); }
#line 1646 "parser.tab.cpp"
    break;

  case 46: /* Exp: Exp DIV Exp  */
#line 240 "parser.ypp"
                    {table.checkValidNumeric(yyvsp[-2]->str, yyvsp[0]->str);
				yyval=new cut_type();
				  yyval->str =table.findExpType(yyvsp[-2]->str, yyvsp[0]->str);
				  yyval = comp.expBin(*yyvsp[-2], "sdiv", *yyvsp[0]); }
#line 1655 "parser.tab.cpp"
    break;

  case 47: /* Exp: Exp MINUS Exp  */
#line 244 "parser.ypp"
                      {table.checkValidNumeric(yyvsp[-2]->str, yyvsp[0]->str);
				  yyval=new cut_type();
				  yyval->str =table.findExpType(yyvsp[-2]->str, yyvsp[0]->str);
				  yyval = comp.expBin(*yyvsp[-2], "sub", *yyvsp[0]);
				  }
#line 1665 "parser.tab.cpp"
    break;

  case 48: /* Exp: Exp PLUS Exp  */
#line 249 "parser.ypp"
                     {table.checkValidNumeric(yyvsp[-2]->str, yyvsp[0]->str);
				yyval=new cut_type();
				  yyval->str =table.findExpType(yyvsp[-2]->str, yyvsp[0]->str);
				  yyval = comp.expBin(*yyvsp[-2], "add", *yyvsp[0]); }
#line 1674 "parser.tab.cpp"
    break;

  case 49: /* Exp: ID  */
#line 254 "parser.ypp"
       {table.checkValidID(yyvsp[0]->str);
		yyval=new cut_type();
		yyval->str = table.typeOfSym(yyvsp[0]->str);
		
		yyval = comp.handle_id(yyvsp[0]);

		}
#line 1686 "parser.tab.cpp"
    break;

  case 50: /* Exp: Call  */
#line 261 "parser.ypp"
         {yyval = yyvsp[0];}
#line 1692 "parser.tab.cpp"
    break;

  case 51: /* Exp: NUM B  */
#line 262 "parser.ypp"
              {
			table.checkOverFlowByte(atoi(yyvsp[-1]->str.c_str()));
	 		

			/*compilation NumB + 0*/
			cut_type t_num = cut_type("BYTE",yyvsp[-1]->str);
			cut_type t0 = cut_type("BYTE","0");
			yyval = comp.expBin(t_num, "add", t0);
			yyval->str = "BYTE";
			}
#line 1707 "parser.tab.cpp"
    break;

  case 52: /* Exp: NUM  */
#line 272 "parser.ypp"
        {
		
		/*compilation Num + 0*/
		
		cut_type t_num = cut_type("INT",yyvsp[0]->str);
		cut_type t0 = cut_type("INT","0");
		yyval = comp.expBin(t_num, "add", t0);
		yyval->str = "INT";
		

	}
#line 1723 "parser.tab.cpp"
    break;

  case 53: /* Exp: STRING  */
#line 283 "parser.ypp"
           {
	yyval = comp.handle_str(yyvsp[0]->str);
	}
#line 1731 "parser.tab.cpp"
    break;

  case 54: /* Exp: TRUE  */
#line 286 "parser.ypp"
         {yyval = comp.bool_val(1);}
#line 1737 "parser.tab.cpp"
    break;

  case 55: /* Exp: FALSE  */
#line 287 "parser.ypp"
          {yyval = comp.bool_val(0);}
#line 1743 "parser.tab.cpp"
    break;

  case 56: /* Exp: NOT Exp  */
#line 288 "parser.ypp"
            {table.isBool(yyvsp[0]->str);
			 yyval = comp.handle_not(yyvsp[0]);
			 }
#line 1751 "parser.tab.cpp"
    break;

  case 57: /* Exp: Exp AND Exp  */
#line 292 "parser.ypp"
                {table.isBool(yyvsp[-2]->str);
				table.isBool(yyvsp[0]->str);
				yyval = comp.handle_and(yyvsp[-2], yyvsp[0]);
				}
#line 1760 "parser.tab.cpp"
    break;

  case 58: /* Exp: Exp OR Exp  */
#line 296 "parser.ypp"
               {table.isBool(yyvsp[-2]->str);
				table.isBool(yyvsp[0]->str);
				yyval = comp.handle_or(yyvsp[-2], yyvsp[0]);
				}
#line 1769 "parser.tab.cpp"
    break;

  case 59: /* Exp: Exp RELOP Exp  */
#line 300 "parser.ypp"
                  {	table.checkValidNumeric(yyvsp[-2]->str, yyvsp[0]->str);
					yyval = comp.handle_relop_equalop(yyvsp[-2], yyvsp[-1]->str, yyvsp[0]);
					}
#line 1777 "parser.tab.cpp"
    break;

  case 60: /* Exp: Exp EQUALOP Exp  */
#line 303 "parser.ypp"
                        {table.checkValidNumeric(yyvsp[-2]->str, yyvsp[0]->str);
					yyval = comp.handle_relop_equalop(yyvsp[-2],yyvsp[-1]->str, yyvsp[0]);
					}
#line 1785 "parser.tab.cpp"
    break;

  case 61: /* CaseList: CaseDeal CaseList  */
#line 310 "parser.ypp"
                             {


			yyval = comp.handle_caselist(yyvsp[-1], yyvsp[0]);}
#line 1794 "parser.tab.cpp"
    break;

  case 62: /* CaseList: CaseDeal  */
#line 314 "parser.ypp"
                     {

			yyval = comp.handle_caselist_one(yyvsp[0]);}
#line 1802 "parser.tab.cpp"
    break;

  case 63: /* CaseList: DEFAULT COLON Statements  */
#line 317 "parser.ypp"
                                     {yyval = comp.handle_default_case(yyvsp[0]); }
#line 1808 "parser.tab.cpp"
    break;

  case 64: /* CaseDeal: CASE NUM COLON Statements  */
#line 319 "parser.ypp"
                                    {
	
	yyval = comp.handle_casedeal(yyvsp[-2], yyvsp[0]);
	
	}
#line 1818 "parser.tab.cpp"
    break;


#line 1822 "parser.tab.cpp"

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 327 "parser.ypp"

/* c code */


int main()
{
	//yydebug = 1;
	//InitPrintFunctions();
	int fin = yyparse();
	table.endComp();
	CodeBuffer::instance().printGlobalBuffer();
	CodeBuffer::instance().printCodeBuffer();
	return fin;
	
}

int yyerror(const char * message)
{	
	errorSyn(yylineno);
	exit(1);
}

