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




/* First part of user prologue.  */
#line 1 "parser.y"

#include <cstdio>
#include <iostream>
#include "treeNodes.h"
#include <stdlib.h>
#include <unistd.h>
#include "treeUtils.h"
#include "scanType.h"
using namespace std;

//for pushing

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

int numErrors = 0;
int numWarnings = 0;
extern int line;
extern int yylex();

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
   // make sure s is not the null value. If it is empty, major error, exit program!
   if(s == NULL)
   {
      printf("ERROR: Sibling is equal to 0.");
      exit(1);
   }

   // make sure t is not the null value. If it is, return s;
   if (t == NULL)
   {
      return s;
   }
   // look at t's sibling list until you finish with sibbling = null (the end of the list) and add s there.
   return s;
}

// pass the static type attribute to the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
   while(t)
   {
      // set t->type and t->isStatic
      t->type = type;
      t->isStatic = isStatic;
      t = t->sibling;
   }
}

// the syntax tree goes here
TreeNode *syntaxTree;

void yyerror(const char *msg);

void printToken(Token_Data myData, string tokenName, int type = 0) {
   cout << "Line: " << myData.linenum << " Type: " << tokenName;
   if(type==0)
     cout << " Token: " << myData.tokenstr;
   if(type==1)
     cout << " Token: " << myData.nvalue;
   if(type==2)
     cout << " Token: " << myData.cvalue;
   cout << endl;
}


#line 140 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FIRSTOP = 3,                    /* FIRSTOP  */
  YYSYMBOL_ADDASS = 4,                     /* ADDASS  */
  YYSYMBOL_DIVASS = 5,                     /* DIVASS  */
  YYSYMBOL_MULASS = 6,                     /* MULASS  */
  YYSYMBOL_SUBASS = 7,                     /* SUBASS  */
  YYSYMBOL_AND = 8,                        /* AND  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_NOT = 10,                       /* NOT  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_GEQ = 12,                       /* GEQ  */
  YYSYMBOL_LEQ = 13,                       /* LEQ  */
  YYSYMBOL_NEQ = 14,                       /* NEQ  */
  YYSYMBOL_MIN = 15,                       /* MIN  */
  YYSYMBOL_MAX = 16,                       /* MAX  */
  YYSYMBOL_INC = 17,                       /* INC  */
  YYSYMBOL_DEC = 18,                       /* DEC  */
  YYSYMBOL_19_ = 19,                       /* '*'  */
  YYSYMBOL_20_ = 20,                       /* '-'  */
  YYSYMBOL_21_ = 21,                       /* '/'  */
  YYSYMBOL_22_ = 22,                       /* '+'  */
  YYSYMBOL_23_ = 23,                       /* '<'  */
  YYSYMBOL_24_ = 24,                       /* '>'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '%'  */
  YYSYMBOL_27_ = 27,                       /* '?'  */
  YYSYMBOL_PRECOMPILER = 28,               /* PRECOMPILER  */
  YYSYMBOL_LASTOP = 29,                    /* LASTOP  */
  YYSYMBOL_IF = 30,                        /* IF  */
  YYSYMBOL_BOOL = 31,                      /* BOOL  */
  YYSYMBOL_THEN = 32,                      /* THEN  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_FOR = 34,                       /* FOR  */
  YYSYMBOL_INT = 35,                       /* INT  */
  YYSYMBOL_BY = 36,                        /* BY  */
  YYSYMBOL_TO = 37,                        /* TO  */
  YYSYMBOL_RETURN = 38,                    /* RETURN  */
  YYSYMBOL_STATIC = 39,                    /* STATIC  */
  YYSYMBOL_DO = 40,                        /* DO  */
  YYSYMBOL_WHILE = 41,                     /* WHILE  */
  YYSYMBOL_BREAK = 42,                     /* BREAK  */
  YYSYMBOL_CHAR = 43,                      /* CHAR  */
  YYSYMBOL_ID = 44,                        /* ID  */
  YYSYMBOL_BOOLCONST = 45,                 /* BOOLCONST  */
  YYSYMBOL_NUMCONST = 46,                  /* NUMCONST  */
  YYSYMBOL_CHARCONST = 47,                 /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 48,               /* STRINGCONST  */
  YYSYMBOL_49_ = 49,                       /* ':'  */
  YYSYMBOL_50_ = 50,                       /* '['  */
  YYSYMBOL_51_ = 51,                       /* ']'  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* '{'  */
  YYSYMBOL_55_ = 55,                       /* '}'  */
  YYSYMBOL_56_ = 56,                       /* ';'  */
  YYSYMBOL_57_ = 57,                       /* ','  */
  YYSYMBOL_LASTTERM = 58,                  /* LASTTERM  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_program = 60,                   /* program  */
  YYSYMBOL_precompList = 61,               /* precompList  */
  YYSYMBOL_declList = 62,                  /* declList  */
  YYSYMBOL_decl = 63,                      /* decl  */
  YYSYMBOL_varDecl = 64,                   /* varDecl  */
  YYSYMBOL_scopedVarDecl = 65,             /* scopedVarDecl  */
  YYSYMBOL_varDeclList = 66,               /* varDeclList  */
  YYSYMBOL_varDeclInit = 67,               /* varDeclInit  */
  YYSYMBOL_varDeclId = 68,                 /* varDeclId  */
  YYSYMBOL_typeSpec = 69,                  /* typeSpec  */
  YYSYMBOL_funDecl = 70,                   /* funDecl  */
  YYSYMBOL_parms = 71,                     /* parms  */
  YYSYMBOL_parmList = 72,                  /* parmList  */
  YYSYMBOL_parmTypeList = 73,              /* parmTypeList  */
  YYSYMBOL_parmIdList = 74,                /* parmIdList  */
  YYSYMBOL_parmId = 75,                    /* parmId  */
  YYSYMBOL_stmt = 76,                      /* stmt  */
  YYSYMBOL_matched = 77,                   /* matched  */
  YYSYMBOL_iterRange = 78,                 /* iterRange  */
  YYSYMBOL_unmatched = 79,                 /* unmatched  */
  YYSYMBOL_expstmt = 80,                   /* expstmt  */
  YYSYMBOL_compoundstmt = 81,              /* compoundstmt  */
  YYSYMBOL_localDecls = 82,                /* localDecls  */
  YYSYMBOL_stmtList = 83,                  /* stmtList  */
  YYSYMBOL_returnstmt = 84,                /* returnstmt  */
  YYSYMBOL_breakstmt = 85,                 /* breakstmt  */
  YYSYMBOL_exp = 86,                       /* exp  */
  YYSYMBOL_assignop = 87,                  /* assignop  */
  YYSYMBOL_simpleExp = 88,                 /* simpleExp  */
  YYSYMBOL_andExp = 89,                    /* andExp  */
  YYSYMBOL_unaryRelExp = 90,               /* unaryRelExp  */
  YYSYMBOL_relExp = 91,                    /* relExp  */
  YYSYMBOL_relop = 92,                     /* relop  */
  YYSYMBOL_minmaxExp = 93,                 /* minmaxExp  */
  YYSYMBOL_minmaxop = 94,                  /* minmaxop  */
  YYSYMBOL_sumExp = 95,                    /* sumExp  */
  YYSYMBOL_sumop = 96,                     /* sumop  */
  YYSYMBOL_mulExp = 97,                    /* mulExp  */
  YYSYMBOL_mulop = 98,                     /* mulop  */
  YYSYMBOL_unaryExp = 99,                  /* unaryExp  */
  YYSYMBOL_unaryop = 100,                  /* unaryop  */
  YYSYMBOL_factor = 101,                   /* factor  */
  YYSYMBOL_mutable = 102,                  /* mutable  */
  YYSYMBOL_immutable = 103,                /* immutable  */
  YYSYMBOL_call = 104,                     /* call  */
  YYSYMBOL_args = 105,                     /* args  */
  YYSYMBOL_argList = 106,                  /* argList  */
  YYSYMBOL_constant = 107                  /* constant  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
       2,     2,     2,     2,     2,     2,     2,    26,     2,     2,
      52,    53,    19,    22,    57,    20,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    56,
      23,    25,    24,    27,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
      15,    16,    17,    18,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   113,   114,   115,   119,   120,   124,   125,
     129,   133,   134,   138,   139,   143,   144,   148,   149,   153,
     154,   155,   160,   161,   165,   166,   170,   171,   175,   176,
     186,   187,   191,   192,   196,   197,   204,   205,   206,   207,
     208,   209,   210,   216,   217,   223,   224,   225,   226,   230,
     231,   235,   240,   241,   245,   246,   250,   251,   255,   259,
     260,   261,   262,   263,   267,   268,   269,   270,   271,   275,
     276,   280,   281,   285,   286,   290,   291,   295,   296,   297,
     298,   299,   300,   304,   305,   309,   310,   314,   315,   319,
     320,   324,   325,   329,   330,   331,   335,   336,   340,   341,
     342,   346,   347,   352,   353,   357,   358,   359,   367,   372,
     373,   380,   381,   385,   386,   388,   389
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
  "\"end of file\"", "error", "\"invalid token\"", "FIRSTOP", "ADDASS",
  "DIVASS", "MULASS", "SUBASS", "AND", "OR", "NOT", "EQ", "GEQ", "LEQ",
  "NEQ", "MIN", "MAX", "INC", "DEC", "'*'", "'-'", "'/'", "'+'", "'<'",
  "'>'", "'='", "'%'", "'?'", "PRECOMPILER", "LASTOP", "IF", "BOOL",
  "THEN", "ELSE", "FOR", "INT", "BY", "TO", "RETURN", "STATIC", "DO",
  "WHILE", "BREAK", "CHAR", "ID", "BOOLCONST", "NUMCONST", "CHARCONST",
  "STRINGCONST", "':'", "'['", "']'", "'('", "')'", "'{'", "'}'", "';'",
  "','", "LASTTERM", "$accept", "program", "precompList", "declList",
  "decl", "varDecl", "scopedVarDecl", "varDeclList", "varDeclInit",
  "varDeclId", "typeSpec", "funDecl", "parms", "parmList", "parmTypeList",
  "parmIdList", "parmId", "stmt", "matched", "iterRange", "unmatched",
  "expstmt", "compoundstmt", "localDecls", "stmtList", "returnstmt",
  "breakstmt", "exp", "assignop", "simpleExp", "andExp", "unaryRelExp",
  "relExp", "relop", "minmaxExp", "minmaxop", "sumExp", "sumop", "mulExp",
  "mulop", "unaryExp", "unaryop", "factor", "mutable", "immutable", "call",
  "args", "argList", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -14,  -138,    24,    78,  -138,  -138,  -138,  -138,  -138,     1,
     157,  -138,  -138,    30,  -138,   168,  -138,   -35,    46,  -138,
      19,    37,    48,    54,    57,  -138,  -138,    66,   168,  -138,
      74,     0,    79,    82,  -138,   137,   168,    89,    93,   100,
    -138,     0,  -138,  -138,  -138,   -20,  -138,  -138,  -138,  -138,
       0,   149,   158,  -138,  -138,    70,    11,   117,  -138,    53,
    -138,  -138,  -138,  -138,  -138,  -138,    48,     0,   121,   150,
       0,   112,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,   116,   149,    71,  -138,  -138,   137,  -138,     0,     0,
     120,     0,     0,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,    53,    53,  -138,  -138,    53,  -138,  -138,  -138,    53,
    -138,  -138,    17,   151,  -138,   118,     3,  -138,   174,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,    15,  -138,   129,
    -138,   133,   130,  -138,   158,  -138,    55,    11,   117,  -138,
     137,     0,  -138,   137,    88,  -138,    74,   107,  -138,  -138,
    -138,  -138,     0,  -138,   171,   167,    14,  -138,  -138,    74,
      68,  -138,  -138,  -138,   137,   137,     0,    72,  -138,  -138,
    -138,  -138,  -138,     2,  -138,     0,   149
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     4,     0,     0,     1,     3,    20,    19,    21,     0,
       2,     7,     8,     0,     9,    25,     6,    17,     0,    14,
      15,    32,     0,     0,    24,    27,    29,     0,    25,    10,
       0,     0,     0,    28,    31,     0,     0,     0,     0,    17,
      13,     0,    99,    98,   100,   103,   116,   113,   114,   115,
       0,    16,    70,    72,    74,    76,    84,    88,    92,     0,
      97,   102,   101,   106,   107,    33,     0,     0,     0,     0,
       0,     0,    53,    50,    23,    34,    35,    39,    40,    41,
      42,     0,    62,   102,    26,    18,     0,    73,     0,   110,
       0,     0,     0,    81,    80,    77,    82,    86,    85,    78,
      79,     0,     0,    90,    89,     0,    93,    94,    95,     0,
      96,    30,     0,     0,    56,     0,     0,    58,    55,    49,
      65,    68,    67,    66,    60,    61,    64,     0,    22,     0,
     112,     0,   109,   105,    69,    71,    75,    83,    87,    91,
       0,     0,    57,     0,     0,    52,     0,     0,    63,    59,
     104,   108,     0,    45,    34,     0,     0,    37,    47,     0,
       0,    51,    54,   111,     0,     0,     0,     0,    12,    36,
      46,    38,    48,    43,    11,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,  -138,   180,  -138,  -138,  -137,   178,  -138,
      -2,  -138,   182,  -138,   179,  -138,   -16,   -82,   -74,  -138,
    -136,  -138,  -138,  -138,  -138,  -138,  -138,   -48,  -138,   -31,
     123,   -28,  -138,  -138,   115,  -138,   119,  -138,   113,  -138,
     -54,  -138,  -138,   -32,  -138,  -138,  -138,  -138,  -138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,    10,    11,    12,   145,    18,    19,    20,
      22,    14,    23,    24,    25,    33,    26,    74,    75,   155,
      76,    77,    78,   118,   147,    79,    80,    81,   127,    82,
      52,    53,    54,   101,    55,   102,    56,   105,    57,   109,
      58,    59,    60,    61,    62,    63,   131,   132,    64
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,    13,    90,    83,   128,   110,    34,   158,    13,   160,
      41,    91,    91,    87,     1,    27,   148,    28,    83,    42,
      43,   115,   167,    91,     4,    41,    91,    44,   170,   172,
      88,   103,    89,   104,    42,    43,   112,    83,   175,   116,
     129,   130,    44,   143,    45,    46,    47,    48,    49,   140,
     111,   166,    50,    15,    83,   139,    83,    83,   153,    45,
      46,    47,    48,    49,   135,   162,   154,    50,    31,   157,
      97,    98,    42,    43,    17,   120,   121,   122,   123,   149,
      44,    93,    94,    95,    96,    97,    98,    32,   124,   125,
     169,   171,    21,    99,   100,    83,   126,    45,    46,    47,
      48,    49,    29,    30,   163,    50,     5,    35,    83,     6,
     156,    83,    37,     7,    36,    83,   146,    41,    39,     6,
      83,     8,     9,     7,   168,    30,    42,    43,   174,    30,
      65,     8,    83,    83,    44,   173,   106,    67,   107,    66,
      85,    68,   159,   108,   176,    69,    86,    41,    70,    71,
      27,    45,    46,    47,    48,    49,    42,    43,    91,    50,
      41,    72,   161,    73,    44,   113,    92,    67,   117,    42,
      43,    68,   119,   133,   142,    69,   141,    44,    70,    71,
     150,    45,    46,    47,    48,    49,   151,   152,     6,    50,
      16,    72,     7,    73,    45,    46,    47,    48,    49,     6,
       8,     9,    50,     7,   164,     6,   114,   165,    40,     7,
      38,     8,    21,   144,   134,    84,   136,     8,   138,     0,
       0,   137
};

static const yytype_int16 yycheck[] =
{
      31,     3,    50,    35,    86,    59,    22,   143,    10,   146,
      10,     9,     9,    41,    28,    50,     1,    52,    50,    19,
      20,    69,   159,     9,     0,    10,     9,    27,   164,   165,
      50,    20,    52,    22,    19,    20,    67,    69,    36,    70,
      88,    89,    27,    40,    44,    45,    46,    47,    48,    32,
      66,    37,    52,    52,    86,   109,    88,    89,   140,    44,
      45,    46,    47,    48,    92,   147,   140,    52,    49,   143,
      15,    16,    19,    20,    44,     4,     5,     6,     7,   127,
      27,    11,    12,    13,    14,    15,    16,    50,    17,    18,
     164,   165,    44,    23,    24,   127,    25,    44,    45,    46,
      47,    48,    56,    57,   152,    52,    28,    53,   140,    31,
     141,   143,    46,    35,    57,   147,   118,    10,    44,    31,
     152,    43,    44,    35,    56,    57,    19,    20,    56,    57,
      51,    43,   164,   165,    27,   166,    19,    30,    21,    57,
      51,    34,   144,    26,   175,    38,    53,    10,    41,    42,
      50,    44,    45,    46,    47,    48,    19,    20,     9,    52,
      10,    54,    55,    56,    27,    44,     8,    30,    56,    19,
      20,    34,    56,    53,    56,    38,    25,    27,    41,    42,
      51,    44,    45,    46,    47,    48,    53,    57,    31,    52,
      10,    54,    35,    56,    44,    45,    46,    47,    48,    31,
      43,    44,    52,    35,    33,    31,    56,    40,    30,    35,
      28,    43,    44,    39,    91,    36,   101,    43,   105,    -1,
      -1,   102
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    60,    61,     0,    28,    31,    35,    43,    44,
      62,    63,    64,    69,    70,    52,    63,    44,    66,    67,
      68,    44,    69,    71,    72,    73,    75,    50,    52,    56,
      57,    49,    50,    74,    75,    53,    57,    46,    71,    44,
      67,    10,    19,    20,    27,    44,    45,    46,    47,    48,
      52,    88,    89,    90,    91,    93,    95,    97,    99,   100,
     101,   102,   103,   104,   107,    51,    57,    30,    34,    38,
      41,    42,    54,    56,    76,    77,    79,    80,    81,    84,
      85,    86,    88,   102,    73,    51,    53,    90,    50,    52,
      86,     9,     8,    11,    12,    13,    14,    15,    16,    23,
      24,    92,    94,    20,    22,    96,    19,    21,    26,    98,
      99,    75,    88,    44,    56,    86,    88,    56,    82,    56,
       4,     5,     6,     7,    17,    18,    25,    87,    76,    86,
      86,   105,   106,    53,    89,    90,    93,    95,    97,    99,
      32,    25,    56,    40,    39,    65,    69,    83,     1,    86,
      51,    53,    57,    76,    77,    78,    88,    77,    79,    69,
      66,    55,    76,    86,    33,    40,    37,    66,    56,    77,
      79,    77,    79,    88,    56,    36,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    77,    77,    77,    77,
      77,    77,    77,    78,    78,    79,    79,    79,    79,    80,
      80,    81,    82,    82,    83,    83,    84,    84,    85,    86,
      86,    86,    86,    86,    87,    87,    87,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    92,
      92,    92,    92,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    98,    98,    98,    99,    99,   100,   100,
     100,   101,   101,   102,   102,   103,   103,   103,   104,   105,
     105,   106,   106,   107,   107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     0,     2,     1,     1,     1,
       3,     4,     3,     3,     1,     1,     3,     1,     4,     1,
       1,     1,     6,     5,     1,     0,     3,     1,     2,     1,
       3,     1,     1,     3,     1,     1,     6,     4,     6,     1,
       1,     1,     1,     3,     5,     4,     6,     4,     6,     2,
       1,     4,     2,     0,     2,     0,     2,     3,     2,     3,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     1,     1,     4,     1,
       0,     3,     1,     1,     1,     1,     1
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
  case 2: /* program: precompList declList  */
#line 109 "parser.y"
                               {syntaxTree = (yyvsp[0].tree); cout << "program : precompList decList" << endl;}
#line 1374 "parser.tab.c"
    break;

  case 3: /* precompList: precompList PRECOMPILER  */
#line 113 "parser.y"
                                      {(yyval.tree) = NULL;}
#line 1380 "parser.tab.c"
    break;

  case 4: /* precompList: PRECOMPILER  */
#line 114 "parser.y"
                 {(yyval.tree) = NULL; printf("%s\n", yylval.Token_Data->tokenstr);}
#line 1386 "parser.tab.c"
    break;

  case 5: /* precompList: %empty  */
#line 115 "parser.y"
               {(yyval.tree) = NULL;}
#line 1392 "parser.tab.c"
    break;

  case 6: /* declList: declList decl  */
#line 119 "parser.y"
                         {(yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1398 "parser.tab.c"
    break;

  case 7: /* declList: decl  */
#line 120 "parser.y"
          {(yyval.tree) = (yyvsp[0].tree); cout << "| funDecl" << endl;}
#line 1404 "parser.tab.c"
    break;

  case 8: /* decl: varDecl  */
#line 124 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree); cout << "varDecl" << endl;}
#line 1410 "parser.tab.c"
    break;

  case 9: /* decl: funDecl  */
#line 125 "parser.y"
             {(yyval.tree) = (yyvsp[0].tree); cout << "| funDecl" << endl;}
#line 1416 "parser.tab.c"
    break;

  case 10: /* varDecl: typeSpec varDeclList ';'  */
#line 129 "parser.y"
                                    {(yyval.tree) = (yyvsp[-1].tree);}
#line 1422 "parser.tab.c"
    break;

  case 11: /* scopedVarDecl: STATIC typeSpec varDeclList ';'  */
#line 133 "parser.y"
                                                {(yyval.tree) = (yyvsp[-1].tree);}
#line 1428 "parser.tab.c"
    break;

  case 12: /* scopedVarDecl: typeSpec varDeclList ';'  */
#line 134 "parser.y"
                              {(yyval.tree) = (yyvsp[-1].tree);}
#line 1434 "parser.tab.c"
    break;

  case 13: /* varDeclList: varDeclList ',' varDeclInit  */
#line 138 "parser.y"
                                          {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1440 "parser.tab.c"
    break;

  case 14: /* varDeclList: varDeclInit  */
#line 139 "parser.y"
                 {(yyval.tree) = (yyvsp[0].tree);}
#line 1446 "parser.tab.c"
    break;

  case 15: /* varDeclInit: varDeclId  */
#line 143 "parser.y"
                        {(yyval.tree) = (yyvsp[0].tree);}
#line 1452 "parser.tab.c"
    break;

  case 16: /* varDeclInit: varDeclId ':' simpleExp  */
#line 144 "parser.y"
                             {(yyval.tree) = (yyvsp[-2].tree);}
#line 1458 "parser.tab.c"
    break;

  case 17: /* varDeclId: ID  */
#line 148 "parser.y"
               {(yyval.tree) = NULL;}
#line 1464 "parser.tab.c"
    break;

  case 18: /* varDeclId: ID '[' NUMCONST ']'  */
#line 149 "parser.y"
                         {(yyval.tree) = NULL;}
#line 1470 "parser.tab.c"
    break;

  case 19: /* typeSpec: INT  */
#line 153 "parser.y"
               {(yyval.type) = ExpType::Integer;}
#line 1476 "parser.tab.c"
    break;

  case 20: /* typeSpec: BOOL  */
#line 154 "parser.y"
          {(yyval.type) = ExpType::Boolean;}
#line 1482 "parser.tab.c"
    break;

  case 21: /* typeSpec: CHAR  */
#line 155 "parser.y"
          {(yyval.type) = ExpType::Char;}
#line 1488 "parser.tab.c"
    break;

  case 22: /* funDecl: typeSpec ID '(' parms ')' stmt  */
#line 160 "parser.y"
                                         {(yyval.tree) = newDeclNode(DeclKind::FuncK, (yyvsp[-5].type), (yyvsp[-4].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1494 "parser.tab.c"
    break;

  case 23: /* funDecl: ID '(' parms ')' stmt  */
#line 161 "parser.y"
                           {(yyval.tree) = newDeclNode(DeclKind::FuncK, ExpType::Void, (yyvsp[-4].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1500 "parser.tab.c"
    break;

  case 24: /* parms: parmList  */
#line 165 "parser.y"
                 {(yyval.tree) = (yyvsp[0].tree);}
#line 1506 "parser.tab.c"
    break;

  case 25: /* parms: %empty  */
#line 166 "parser.y"
               {(yyval.tree) = NULL;}
#line 1512 "parser.tab.c"
    break;

  case 26: /* parmList: parmList ',' parmTypeList  */
#line 170 "parser.y"
                                     {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1518 "parser.tab.c"
    break;

  case 27: /* parmList: parmTypeList  */
#line 171 "parser.y"
                  {(yyval.tree) = (yyvsp[0].tree);}
#line 1524 "parser.tab.c"
    break;

  case 28: /* parmTypeList: typeSpec parmIdList  */
#line 175 "parser.y"
                                   {(yyval.tree) = (yyvsp[0].tree);}
#line 1530 "parser.tab.c"
    break;

  case 29: /* parmTypeList: parmId  */
#line 176 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1536 "parser.tab.c"
    break;

  case 30: /* parmIdList: parmIdList ',' parmId  */
#line 186 "parser.y"
                                    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1542 "parser.tab.c"
    break;

  case 31: /* parmIdList: parmId  */
#line 187 "parser.y"
             {(yyval.tree) = (yyvsp[0].tree);}
#line 1548 "parser.tab.c"
    break;

  case 32: /* parmId: ID  */
#line 191 "parser.y"
            {(yyval.tree) = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, (yyvsp[0].Token_Data)); (yyval.tree)->isArray = false;}
#line 1554 "parser.tab.c"
    break;

  case 33: /* parmId: ID '[' ']'  */
#line 192 "parser.y"
               {(yyval.tree) = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, (yyvsp[-2].Token_Data)); (yyval.tree)->isArray = true;}
#line 1560 "parser.tab.c"
    break;

  case 34: /* stmt: matched  */
#line 196 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree); cout << "stmt : matched" << endl;}
#line 1566 "parser.tab.c"
    break;

  case 35: /* stmt: unmatched  */
#line 197 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree); cout << "| unmatched" << endl;}
#line 1572 "parser.tab.c"
    break;

  case 36: /* matched: IF simpleExp THEN matched ELSE matched  */
#line 204 "parser.y"
                                                 {(yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-5].Token_Data), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1578 "parser.tab.c"
    break;

  case 37: /* matched: WHILE simpleExp DO matched  */
#line 205 "parser.y"
                                {(yyval.tree) = newStmtNode(StmtKind::WhileK, (yyvsp[-3].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1584 "parser.tab.c"
    break;

  case 38: /* matched: FOR ID '=' iterRange DO matched  */
#line 206 "parser.y"
                                     {(yyval.tree) = newStmtNode(StmtKind::ForK, (yyvsp[-5].Token_Data), NULL, (yyvsp[-2].tree), (yyvsp[0].tree)); (yyval.tree)->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, (yyvsp[-4].Token_Data));}
#line 1590 "parser.tab.c"
    break;

  case 39: /* matched: expstmt  */
#line 207 "parser.y"
             {(yyval.tree) = (yyvsp[0].tree);}
#line 1596 "parser.tab.c"
    break;

  case 40: /* matched: compoundstmt  */
#line 208 "parser.y"
                  {(yyval.tree) = (yyvsp[0].tree);}
#line 1602 "parser.tab.c"
    break;

  case 41: /* matched: returnstmt  */
#line 209 "parser.y"
                {(yyval.tree) = (yyvsp[0].tree);}
#line 1608 "parser.tab.c"
    break;

  case 42: /* matched: breakstmt  */
#line 210 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 1614 "parser.tab.c"
    break;

  case 43: /* iterRange: simpleExp TO simpleExp  */
#line 216 "parser.y"
                                   {(yyval.tree) = newStmtNode(StmtKind::RangeK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1620 "parser.tab.c"
    break;

  case 44: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 217 "parser.y"
                                         {(yyval.tree) = newStmtNode(StmtKind::RangeK, (yyvsp[-3].Token_Data), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1626 "parser.tab.c"
    break;

  case 45: /* unmatched: IF simpleExp THEN stmt  */
#line 223 "parser.y"
                                   {(yyval.tree) = NULL;}
#line 1632 "parser.tab.c"
    break;

  case 46: /* unmatched: IF simpleExp THEN matched ELSE unmatched  */
#line 224 "parser.y"
                                              {(yyval.tree) = NULL;}
#line 1638 "parser.tab.c"
    break;

  case 47: /* unmatched: WHILE simpleExp DO unmatched  */
#line 225 "parser.y"
                                  {(yyval.tree) = NULL;}
#line 1644 "parser.tab.c"
    break;

  case 48: /* unmatched: FOR ID '=' iterRange DO unmatched  */
#line 226 "parser.y"
                                       {(yyval.tree) = NULL;}
#line 1650 "parser.tab.c"
    break;

  case 49: /* expstmt: exp ';'  */
#line 230 "parser.y"
                  {(yyval.tree) = (yyvsp[-1].tree);}
#line 1656 "parser.tab.c"
    break;

  case 50: /* expstmt: ';'  */
#line 231 "parser.y"
         {(yyval.tree) = NULL;}
#line 1662 "parser.tab.c"
    break;

  case 51: /* compoundstmt: '{' localDecls stmtList '}'  */
#line 235 "parser.y"
                                           {(yyval.tree) = newStmtNode(StmtKind::CompoundK, (yyvsp[-3].Token_Data), (yyvsp[-2].tree), (yyvsp[-1].tree)); cout << 
"compoundstmt : '{' localDecls stmtList '}'" << endl;}
#line 1669 "parser.tab.c"
    break;

  case 52: /* localDecls: localDecls scopedVarDecl  */
#line 240 "parser.y"
                                      {(yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1675 "parser.tab.c"
    break;

  case 53: /* localDecls: %empty  */
#line 241 "parser.y"
               {(yyval.tree) = NULL;}
#line 1681 "parser.tab.c"
    break;

  case 54: /* stmtList: stmtList stmt  */
#line 245 "parser.y"
                         {(yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1687 "parser.tab.c"
    break;

  case 55: /* stmtList: %empty  */
#line 246 "parser.y"
               {(yyval.tree) = NULL;}
#line 1693 "parser.tab.c"
    break;

  case 56: /* returnstmt: RETURN ';'  */
#line 250 "parser.y"
                        {(yyval.tree) = newStmtNode(StmtKind::ReturnK, (yyvsp[-1].Token_Data));}
#line 1699 "parser.tab.c"
    break;

  case 57: /* returnstmt: RETURN exp ';'  */
#line 251 "parser.y"
                    {(yyval.tree) = newStmtNode(StmtKind::ReturnK, (yyvsp[-2].Token_Data), (yyvsp[-1].tree));}
#line 1705 "parser.tab.c"
    break;

  case 58: /* breakstmt: BREAK ';'  */
#line 255 "parser.y"
                      {(yyval.tree) = newStmtNode(StmtKind::BreakK, (yyvsp[-1].Token_Data));}
#line 1711 "parser.tab.c"
    break;

  case 59: /* exp: mutable assignop exp  */
#line 259 "parser.y"
                           {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1717 "parser.tab.c"
    break;

  case 60: /* exp: mutable INC  */
#line 260 "parser.y"
                 {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[0].Token_Data), (yyvsp[-1].tree));}
#line 1723 "parser.tab.c"
    break;

  case 61: /* exp: mutable DEC  */
#line 261 "parser.y"
                 {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[0].Token_Data), (yyvsp[-1].tree));}
#line 1729 "parser.tab.c"
    break;

  case 62: /* exp: simpleExp  */
#line 262 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 1735 "parser.tab.c"
    break;

  case 63: /* exp: mutable assignop error  */
#line 263 "parser.y"
                            {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), NULL);}
#line 1741 "parser.tab.c"
    break;

  case 64: /* assignop: '='  */
#line 267 "parser.y"
               {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1747 "parser.tab.c"
    break;

  case 65: /* assignop: ADDASS  */
#line 268 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1753 "parser.tab.c"
    break;

  case 66: /* assignop: SUBASS  */
#line 269 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1759 "parser.tab.c"
    break;

  case 67: /* assignop: MULASS  */
#line 270 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1765 "parser.tab.c"
    break;

  case 68: /* assignop: DIVASS  */
#line 271 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1771 "parser.tab.c"
    break;

  case 69: /* simpleExp: simpleExp OR andExp  */
#line 275 "parser.y"
                                {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1777 "parser.tab.c"
    break;

  case 70: /* simpleExp: andExp  */
#line 276 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1783 "parser.tab.c"
    break;

  case 71: /* andExp: andExp AND unaryRelExp  */
#line 280 "parser.y"
                                {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1789 "parser.tab.c"
    break;

  case 72: /* andExp: unaryRelExp  */
#line 281 "parser.y"
                 {(yyval.tree) = (yyvsp[0].tree);}
#line 1795 "parser.tab.c"
    break;

  case 73: /* unaryRelExp: NOT unaryRelExp  */
#line 285 "parser.y"
                              {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[0].tree));}
#line 1801 "parser.tab.c"
    break;

  case 74: /* unaryRelExp: relExp  */
#line 286 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1807 "parser.tab.c"
    break;

  case 75: /* relExp: minmaxExp relop minmaxExp  */
#line 290 "parser.y"
                                   {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1813 "parser.tab.c"
    break;

  case 76: /* relExp: minmaxExp  */
#line 291 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 1819 "parser.tab.c"
    break;

  case 77: /* relop: LEQ  */
#line 295 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1825 "parser.tab.c"
    break;

  case 78: /* relop: '<'  */
#line 296 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1831 "parser.tab.c"
    break;

  case 79: /* relop: '>'  */
#line 297 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1837 "parser.tab.c"
    break;

  case 80: /* relop: GEQ  */
#line 298 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1843 "parser.tab.c"
    break;

  case 81: /* relop: EQ  */
#line 299 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1849 "parser.tab.c"
    break;

  case 82: /* relop: NEQ  */
#line 300 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1855 "parser.tab.c"
    break;

  case 83: /* minmaxExp: minmaxExp minmaxop sumExp  */
#line 304 "parser.y"
                                      {(yyval.tree) = NULL;}
#line 1861 "parser.tab.c"
    break;

  case 84: /* minmaxExp: sumExp  */
#line 305 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1867 "parser.tab.c"
    break;

  case 85: /* minmaxop: MAX  */
#line 309 "parser.y"
               {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1873 "parser.tab.c"
    break;

  case 86: /* minmaxop: MIN  */
#line 310 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1879 "parser.tab.c"
    break;

  case 87: /* sumExp: sumExp sumop mulExp  */
#line 314 "parser.y"
                             {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1885 "parser.tab.c"
    break;

  case 88: /* sumExp: mulExp  */
#line 315 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1891 "parser.tab.c"
    break;

  case 89: /* sumop: '+'  */
#line 319 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1897 "parser.tab.c"
    break;

  case 90: /* sumop: '-'  */
#line 320 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1903 "parser.tab.c"
    break;

  case 91: /* mulExp: mulExp mulop unaryExp  */
#line 324 "parser.y"
                               {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1909 "parser.tab.c"
    break;

  case 92: /* mulExp: unaryExp  */
#line 325 "parser.y"
              {(yyval.tree) = (yyvsp[0].tree);}
#line 1915 "parser.tab.c"
    break;

  case 93: /* mulop: '*'  */
#line 329 "parser.y"
            {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1921 "parser.tab.c"
    break;

  case 94: /* mulop: '/'  */
#line 330 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1927 "parser.tab.c"
    break;

  case 95: /* mulop: '%'  */
#line 331 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1933 "parser.tab.c"
    break;

  case 96: /* unaryExp: unaryop unaryExp  */
#line 335 "parser.y"
                            {(yyval.tree) = newExpNode(OpK,(yyvsp[-1].Token_Data), (yyvsp[0].tree));}
#line 1939 "parser.tab.c"
    break;

  case 97: /* unaryExp: factor  */
#line 336 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1945 "parser.tab.c"
    break;

  case 98: /* unaryop: '-'  */
#line 340 "parser.y"
              {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1951 "parser.tab.c"
    break;

  case 99: /* unaryop: '*'  */
#line 341 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1957 "parser.tab.c"
    break;

  case 100: /* unaryop: '?'  */
#line 342 "parser.y"
         {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1963 "parser.tab.c"
    break;

  case 101: /* factor: immutable  */
#line 346 "parser.y"
                   {(yyval.tree) = (yyvsp[0].tree);}
#line 1969 "parser.tab.c"
    break;

  case 102: /* factor: mutable  */
#line 347 "parser.y"
             {(yyval.tree) = (yyvsp[0].tree);}
#line 1975 "parser.tab.c"
    break;

  case 103: /* mutable: ID  */
#line 352 "parser.y"
             {(yyval.tree) = newExpNode(ExpKind::IdK, (yyvsp[0].Token_Data));}
#line 1981 "parser.tab.c"
    break;

  case 104: /* mutable: ID '[' exp ']'  */
#line 353 "parser.y"
                    {(yyval.tree) = NULL;}
#line 1987 "parser.tab.c"
    break;

  case 105: /* immutable: '(' exp ')'  */
#line 357 "parser.y"
                        {(yyval.tree) = (yyvsp[-1].tree);}
#line 1993 "parser.tab.c"
    break;

  case 106: /* immutable: call  */
#line 358 "parser.y"
          {(yyval.tree) = (yyvsp[0].tree);}
#line 1999 "parser.tab.c"
    break;

  case 107: /* immutable: constant  */
#line 359 "parser.y"
              {(yyval.tree) = (yyvsp[0].tree);}
#line 2005 "parser.tab.c"
    break;

  case 108: /* call: ID '(' args ')'  */
#line 367 "parser.y"
                       {(yyval.tree) = newExpNode(ExpKind::CallK, (yyvsp[-3].Token_Data), (yyvsp[-1].tree));
   (yyval.tree)->attr.name = (yyvsp[-3].Token_Data)->svalue;}
#line 2012 "parser.tab.c"
    break;

  case 109: /* args: argList  */
#line 372 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 2018 "parser.tab.c"
    break;

  case 110: /* args: %empty  */
#line 373 "parser.y"
                 {(yyval.tree) = NULL;}
#line 2024 "parser.tab.c"
    break;

  case 111: /* argList: argList ',' exp  */
#line 380 "parser.y"
                          {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 2030 "parser.tab.c"
    break;

  case 112: /* argList: exp  */
#line 381 "parser.y"
         {(yyval.tree) = (yyvsp[0].tree);}
#line 2036 "parser.tab.c"
    break;

  case 113: /* constant: NUMCONST  */
#line 385 "parser.y"
                    {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data)); (yyval.tree)->type = ExpType::Integer;}
#line 2042 "parser.tab.c"
    break;

  case 114: /* constant: CHARCONST  */
#line 386 "parser.y"
               {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data));
                (yyval.tree)->type = ExpType::Char;}
#line 2049 "parser.tab.c"
    break;

  case 115: /* constant: STRINGCONST  */
#line 388 "parser.y"
                 {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data));}
#line 2055 "parser.tab.c"
    break;

  case 116: /* constant: BOOLCONST  */
#line 389 "parser.y"
               {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data)); (yyval.tree)->type = ExpType::Boolean;}
#line 2061 "parser.tab.c"
    break;


#line 2065 "parser.tab.c"

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

#line 392 "parser.y"

void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}
int main(int argc, char **argv) {
   // these lines allow us to read information from the parser.l file
   yylval.Token_Data = (Token_Data*)malloc(sizeof(Token_Data));
   yylval.tree = (TreeNode*)malloc(sizeof(TreeNode));
   yylval.Token_Data->linenum = 1;
   int option, index;
   char *file = NULL;
   bool dotAST = false;
   extern FILE *yyin;

   int ch;
   
   while ((option = getopt (argc, argv, "")) != -1)
      switch (option)
      {
      default:
         ;
      }
   if ( optind == argc ) yyparse();
   for (index = optind; index < argc; index++) 
   {
      yyin = fopen (argv[index], "r");
      yyparse();
      fclose (yyin);
   }
   printf("Number of warnings: 0\n");
   printf("Number of errors: 0\n");
   // printTree(stdout,,)
   return 0;
}
