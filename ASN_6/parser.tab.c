/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "treeNodes.h"
#include "treeUtils.h"
#include "semantics.h"
#include "symbolTable.h"
#include "scanType.h"
#include "dot.h"
#include "codegen.h"
#include "emitcode.h"
#include "yyerror.h"

using namespace std;

// Assignment 5 in progress...
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
   if(s == NULL && numErrors==0)
   {
      printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
      exit(1);
   }

   // make sure t is not the null value. If it is, return s;
   if (t == nullptr)
   {
      return s;
   }
   // look at t's siblings until you finish with sibbling = null (the end of the list) and add string there.

   TreeNode *treePtr = t;
   while(treePtr->sibling != nullptr)
   {
      treePtr = treePtr->sibling;
   }
   treePtr->sibling = s;

   return t;
}

// pass the static type attribute to the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
   while(t != NULL)
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


#line 143 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FIRSTOP = 258,
    ADDASS = 259,
    DIVASS = 260,
    MULASS = 261,
    SUBASS = 262,
    AND = 263,
    OR = 264,
    NOT = 265,
    CHSIGN = 266,
    SIZEOF = 267,
    EQ = 268,
    GEQ = 269,
    LEQ = 270,
    NEQ = 271,
    MIN = 272,
    MAX = 273,
    INC = 274,
    DEC = 275,
    PRECOMPILER = 276,
    LASTOP = 277,
    IF = 278,
    BOOL = 279,
    THEN = 280,
    ELSE = 281,
    FOR = 282,
    INT = 283,
    BY = 284,
    TO = 285,
    RETURN = 286,
    STATIC = 287,
    DO = 288,
    WHILE = 289,
    BREAK = 290,
    CHAR = 291,
    ID = 292,
    BOOLCONST = 293,
    NUMCONST = 294,
    CHARCONST = 295,
    STRINGCONST = 296,
    LASTTERM = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 79 "parser.y" /* yacc.c:355  */

   struct Token_Data *Token_Data;
   struct TreeNode *tree;
   ExpType type; // for passing type spec up the tree

#line 232 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 249 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   225

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    28,     2,     2,
      54,    55,    21,    24,    59,    22,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    58,
      25,    27,    26,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   123,   124,   125,   129,   130,   134,   135,
     139,   146,   147,   151,   152,   156,   157,   161,   162,   166,
     167,   168,   173,   174,   179,   180,   184,   185,   192,   202,
     203,   208,   210,   215,   216,   221,   222,   223,   228,   229,
     230,   231,   235,   236,   242,   243,   244,   245,   254,   255,
     259,   260,   266,   267,   273,   274,   278,   279,   283,   287,
     288,   289,   290,   291,   295,   296,   297,   298,   299,   303,
     304,   308,   309,   313,   314,   318,   319,   323,   324,   325,
     326,   327,   328,   332,   333,   337,   338,   342,   343,   347,
     348,   352,   353,   357,   358,   359,   363,   364,   368,   369,
     370,   374,   375,   380,   381,   387,   388,   389,   397,   401,
     402,   410,   411,   415,   421,   427,   433
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FIRSTOP", "ADDASS", "DIVASS", "MULASS",
  "SUBASS", "AND", "OR", "NOT", "CHSIGN", "SIZEOF", "EQ", "GEQ", "LEQ",
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
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    42,    45,    47,    43,    60,    62,    61,    37,    63,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,    58,    91,    93,    40,    41,   123,   125,    59,    44,
     297
};
# endif

#define YYPACT_NINF -136

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-136)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -20,  -136,    14,    50,  -136,  -136,  -136,  -136,  -136,     5,
     -17,  -136,  -136,    32,  -136,    16,  -136,   -35,   -28,  -136,
       1,    58,    54,    47,  -136,    60,    16,  -136,    72,   166,
      67,    62,  -136,   135,    16,    70,    74,    75,  -136,   166,
    -136,  -136,  -136,    -4,  -136,  -136,  -136,  -136,   166,   121,
     123,  -136,  -136,   183,    40,    56,  -136,    44,  -136,  -136,
    -136,  -136,  -136,    79,    58,   166,    92,    53,   166,    81,
    -136,  -136,  -136,  -136,  -136,  -136,    85,  -136,  -136,    91,
     121,   198,  -136,  -136,   135,  -136,   166,   166,    86,   166,
     166,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,    44,
      44,  -136,  -136,    44,  -136,  -136,  -136,    44,  -136,  -136,
    -136,     4,   128,  -136,   101,     0,  -136,    83,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,    22,  -136,   110,
    -136,   111,   106,  -136,   123,  -136,     9,    40,    56,  -136,
     135,   166,  -136,   135,    16,  -136,    72,   104,  -136,  -136,
    -136,  -136,   166,  -136,   133,   127,     6,  -136,  -136,    72,
      27,  -136,  -136,  -136,   135,   135,   166,    30,  -136,  -136,
    -136,  -136,  -136,    -3,  -136,   166,   121
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     4,     0,     0,     1,     3,    20,    19,    21,     0,
       2,     7,     8,     0,     9,    25,     6,    17,     0,    14,
      15,     0,     0,    24,    27,     0,    25,    10,     0,     0,
      31,    28,    30,     0,     0,     0,     0,    17,    13,     0,
      99,    98,   100,   103,   116,   113,   114,   115,     0,    16,
      70,    72,    74,    76,    84,    88,    92,     0,    97,   102,
     101,   106,   107,     0,     0,     0,     0,     0,     0,     0,
      53,    49,    23,    33,    34,    38,    39,    40,    41,     0,
      62,   102,    26,    18,     0,    73,     0,   110,     0,     0,
       0,    81,    80,    77,    82,    86,    85,    78,    79,     0,
       0,    90,    89,     0,    93,    94,    95,     0,    96,    32,
      29,     0,     0,    56,     0,     0,    58,    55,    51,    48,
      65,    68,    67,    66,    60,    61,    64,     0,    22,     0,
     112,     0,   109,   105,    69,    71,    75,    83,    87,    91,
       0,     0,    57,     0,     0,    52,     0,     0,    63,    59,
     104,   108,     0,    44,    33,     0,     0,    36,    46,     0,
       0,    50,    54,   111,     0,     0,     0,     0,    12,    35,
      45,    37,    47,    42,    11,     0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -136,  -136,  -136,  -136,   160,  -136,  -136,  -135,   144,  -136,
      -2,  -136,   147,  -136,   140,  -136,   113,   -80,  -118,  -136,
    -131,  -136,  -136,  -136,  -136,  -136,  -136,   -46,  -136,   -29,
      97,   -32,  -136,  -136,    93,  -136,    80,  -136,    87,  -136,
     -52,  -136,  -136,   -30,  -136,  -136,  -136,  -136,  -136
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,    11,    12,   145,    18,    19,    20,
      21,    14,    22,    23,    24,    31,    32,    72,    73,   155,
      74,    75,    76,   117,   147,    77,    78,    79,   127,    80,
      50,    51,    52,    99,    53,   100,    54,   103,    55,   107,
      56,    57,    58,    59,    60,    61,   131,   132,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    13,    88,    81,   128,   108,    89,    85,    13,    89,
       1,   160,   158,    89,     4,    89,     6,    25,    81,    26,
       7,   114,   154,   148,   167,   157,    95,    96,     8,     9,
      27,    28,    39,   170,   172,   175,   111,    81,   140,   115,
     129,   130,   143,    40,    41,   166,   169,   171,    86,     6,
      87,    42,    29,     7,    81,   139,    81,    81,   135,    15,
     153,     8,   101,    39,   102,    40,    41,   162,    43,    44,
      45,    46,    47,    42,    40,    41,    48,   104,    17,   105,
       5,   149,    42,     6,   106,   168,    28,     7,   174,    28,
      43,    44,    45,    46,    47,     8,     9,    81,    48,    43,
      44,    45,    46,    47,    30,    34,   163,    48,    35,    33,
      81,   113,   156,    81,    39,   146,     6,    81,    37,    63,
       7,    64,    81,    83,   144,    40,    41,    25,     8,    84,
      89,    90,   109,    42,    81,    81,    65,   173,   112,   116,
      66,   133,   159,   118,    67,    39,   176,    68,    69,   119,
      43,    44,    45,    46,    47,   141,    40,    41,    48,   142,
      70,   161,    71,   150,    42,   152,   151,    65,   164,   165,
      16,    66,    38,    36,    82,    67,    39,   110,    68,    69,
     137,    43,    44,    45,    46,    47,   134,    40,    41,    48,
     138,    70,   136,    71,     0,    42,    91,    92,    93,    94,
      95,    96,   120,   121,   122,   123,     0,     0,    97,    98,
       0,     0,    43,    44,    45,    46,    47,   124,   125,     0,
      48,     0,     0,     0,     0,   126
};

static const yytype_int16 yycheck[] =
{
      29,     3,    48,    33,    84,    57,     9,    39,    10,     9,
      30,   146,   143,     9,     0,     9,    33,    52,    48,    54,
      37,    67,   140,     1,   159,   143,    17,    18,    45,    46,
      58,    59,    10,   164,   165,    38,    65,    67,    34,    68,
      86,    87,    42,    21,    22,    39,   164,   165,    52,    33,
      54,    29,    51,    37,    84,   107,    86,    87,    90,    54,
     140,    45,    22,    10,    24,    21,    22,   147,    46,    47,
      48,    49,    50,    29,    21,    22,    54,    21,    46,    23,
      30,   127,    29,    33,    28,    58,    59,    37,    58,    59,
      46,    47,    48,    49,    50,    45,    46,   127,    54,    46,
      47,    48,    49,    50,    46,    58,   152,    54,    48,    55,
     140,    58,   141,   143,    10,   117,    33,   147,    46,    52,
      37,    59,   152,    53,    41,    21,    22,    52,    45,    55,
       9,     8,    53,    29,   164,   165,    32,   166,    46,    58,
      36,    55,   144,    58,    40,    10,   175,    43,    44,    58,
      46,    47,    48,    49,    50,    27,    21,    22,    54,    58,
      56,    57,    58,    53,    29,    59,    55,    32,    35,    42,
      10,    36,    28,    26,    34,    40,    10,    64,    43,    44,
     100,    46,    47,    48,    49,    50,    89,    21,    22,    54,
     103,    56,    99,    58,    -1,    29,    13,    14,    15,    16,
      17,    18,     4,     5,     6,     7,    -1,    -1,    25,    26,
      -1,    -1,    46,    47,    48,    49,    50,    19,    20,    -1,
      54,    -1,    -1,    -1,    -1,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    62,    63,     0,    30,    33,    37,    45,    46,
      64,    65,    66,    71,    72,    54,    65,    46,    68,    69,
      70,    71,    73,    74,    75,    52,    54,    58,    59,    51,
      46,    76,    77,    55,    58,    48,    73,    46,    69,    10,
      21,    22,    29,    46,    47,    48,    49,    50,    54,    90,
      91,    92,    93,    95,    97,    99,   101,   102,   103,   104,
     105,   106,   109,    52,    59,    32,    36,    40,    43,    44,
      56,    58,    78,    79,    81,    82,    83,    86,    87,    88,
      90,   104,    75,    53,    55,    92,    52,    54,    88,     9,
       8,    13,    14,    15,    16,    17,    18,    25,    26,    94,
      96,    22,    24,    98,    21,    23,    28,   100,   101,    53,
      77,    90,    46,    58,    88,    90,    58,    84,    58,    58,
       4,     5,     6,     7,    19,    20,    27,    89,    78,    88,
      88,   107,   108,    55,    91,    92,    95,    97,    99,   101,
      34,    27,    58,    42,    41,    67,    71,    85,     1,    88,
      53,    55,    59,    78,    79,    80,    90,    79,    81,    71,
      68,    57,    78,    88,    35,    42,    39,    68,    58,    79,
      81,    79,    81,    90,    58,    38,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    88,    88,    88,    89,    89,    89,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   101,   101,   102,   102,
     102,   103,   103,   104,   104,   105,   105,   105,   106,   107,
     107,   108,   108,   109,   109,   109,   109
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     0,     2,     1,     1,     1,
       3,     4,     3,     3,     1,     1,     3,     1,     4,     1,
       1,     1,     6,     5,     1,     0,     3,     1,     2,     3,
       1,     1,     3,     1,     1,     6,     4,     6,     1,     1,
       1,     1,     3,     5,     4,     6,     4,     6,     2,     1,
       4,     2,     2,     0,     2,     0,     2,     3,     2,     3,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     1,     1,     4,     1,
       0,     3,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 118 "parser.y" /* yacc.c:1646  */
    {syntaxTree = (yyvsp[0].tree);}
#line 1474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 123 "parser.y" /* yacc.c:1646  */
    {cout << yylval.Token_Data->tokenstr << "\n"; (yyval.tree) = nullptr;}
#line 1480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 124 "parser.y" /* yacc.c:1646  */
    {cout << yylval.Token_Data->tokenstr << "\n"; (yyval.tree) = nullptr;}
#line 1486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 125 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 1492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 130 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 134 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 139 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), false); yyerrok;}
#line 1522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), true); (yyval.tree)->isStatic = true; yyerrok;}
#line 1528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 147 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), false); (yyval.tree)->isStatic=false; yyerrok;}
#line 1534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 152 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 157 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-2].tree); (yyvsp[-2].tree)->child[0] = (yyvsp[0].tree);}
#line 1558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 161 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(DeclKind::VarK, UndefinedType, (yyvsp[0].Token_Data)); (yyval.tree)->isArray = false; (yyval.tree)->size = 1;}
#line 1564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 162 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(DeclKind::VarK, UndefinedType, (yyvsp[-3].Token_Data)); (yyval.tree)->isArray = true; (yyval.tree)->size = (yyvsp[-1].Token_Data)->nvalue + 1;}
#line 1570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 166 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = ExpType::Integer;}
#line 1576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = ExpType::Boolean;}
#line 1582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 168 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = ExpType::Char;}
#line 1588 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 173 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(DeclKind::FuncK, (yyvsp[-5].type), (yyvsp[-4].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 174 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(DeclKind::FuncK, ExpType::Void, (yyvsp[-4].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1600 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 179 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1606 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 180 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = nullptr;}
#line 1612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 184 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1618 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 185 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1624 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 192 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree); setType((yyvsp[0].tree), (yyvsp[-1].type), false);}
#line 1630 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 202 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1636 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 203 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, (yyvsp[0].Token_Data)); 
                 (yyval.tree)->isArray = false; (yyval.tree)->isStatic = false; (yyval.tree)->size = 1;}
#line 1649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, (yyvsp[-2].Token_Data)); 
                 (yyval.tree)->isArray = true; (yyval.tree)->isStatic = false; (yyval.tree)->size = 1;}
#line 1656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1662 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 216 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-5].Token_Data), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::WhileK, (yyvsp[-3].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 223 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::ForK, (yyvsp[-5].Token_Data), nullptr, (yyvsp[-2].tree), (yyvsp[0].tree));
                                                   (yyval.tree)->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, (yyvsp[-4].Token_Data));
                                                   (yyval.tree)->child[0]->attr.name = (yyvsp[-4].Token_Data)->svalue;
                                                   (yyval.tree)->child[0]->isArray = false;
                                                   (yyval.tree)->child[0]->size = 1;}
#line 1690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 235 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::RangeK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::RangeK, (yyvsp[-3].Token_Data), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 242 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-3].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1732 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::IfK, (yyvsp[-5].Token_Data), (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::WhileK, (yyvsp[-3].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 245 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::ForK, (yyvsp[-5].Token_Data), nullptr, (yyvsp[-2].tree), (yyvsp[0].tree));
                                                (yyval.tree)->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, (yyvsp[-4].Token_Data));
                                                (yyval.tree)->child[0]->attr.name = (yyvsp[-4].Token_Data)->svalue;
                                                (yyval.tree)->child[0]->isArray = false;
                                                (yyval.tree)->child[0]->size = 1;}
#line 1754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 254 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree);}
#line 1760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 255 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = nullptr;}
#line 1766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::CompoundK, (yyvsp[-3].Token_Data), (yyvsp[-2].tree), (yyvsp[-1].tree)); yyerrok;}
#line 1772 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 260 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree);}
#line 1778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 266 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 267 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = nullptr;}
#line 1790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree));}
#line 1796 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 274 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = nullptr;}
#line 1802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 278 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::ReturnK, (yyvsp[-1].Token_Data));}
#line 1808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 279 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::ReturnK, (yyvsp[-2].Token_Data), (yyvsp[-1].tree));}
#line 1814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 283 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(StmtKind::BreakK, (yyvsp[-1].Token_Data));}
#line 1820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 287 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree)); (yyval.tree)->isAssigned = true;}
#line 1826 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 288 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[0].Token_Data), (yyvsp[-1].tree));}
#line 1832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 289 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[0].Token_Data), (yyvsp[-1].tree));}
#line 1838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 290 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 291 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::AssignK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree));}
#line 1850 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 295 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 296 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1862 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 297 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1868 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 299 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1880 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 303 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 304 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1892 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 308 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 309 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 313 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[0].tree));}
#line 1910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 314 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 318 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 319 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 323 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 324 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 325 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 326 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 327 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 328 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 332 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 333 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 337 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1982 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 338 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 1988 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 342 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1994 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 343 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2000 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 347 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 2006 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 2012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-1].Token_Data), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 2018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 357 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 2030 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 358 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 2036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 359 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 2042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 363 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::OpK,(yyvsp[-1].Token_Data), (yyvsp[0].tree));}
#line 2048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 364 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2054 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 368 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data); (yyval.Token_Data)->svalue = (char *)"chsign";}
#line 2060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 369 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data); (yyval.Token_Data)->svalue = (char *)"sizeof";}
#line 2066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 370 "parser.y" /* yacc.c:1646  */
    {(yyval.Token_Data) = (yyvsp[0].Token_Data);}
#line 2072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 374 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 375 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 380 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::IdK, (yyvsp[0].Token_Data)); (yyval.tree)->isArray = false; (yyval.tree)->attr.name = (yyvsp[0].Token_Data)->svalue;}
#line 2090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 381 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newExpNode(ExpKind::OpK, (yyvsp[-2].Token_Data), nullptr, (yyvsp[-1].tree)); 
                      (yyval.tree)->child[0] = newExpNode(ExpKind::IdK, (yyvsp[-3].Token_Data));
                      (yyval.tree)->child[0]->attr.name = (yyvsp[-3].Token_Data)->svalue;}
#line 2098 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 387 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree);}
#line 2104 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 388 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2110 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 389 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2116 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 397 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::CallK, (yyvsp[-3].Token_Data), (yyvsp[-1].tree)); (yyval.tree)->attr.name = (yyvsp[-3].Token_Data)->svalue;}
#line 2122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 401 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2128 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 402 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = nullptr;}
#line 2134 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 410 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 2140 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 411 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2146 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 415 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data)); 
   (yyval.tree)->type = ExpType::Integer;
   (yyval.tree)->isArray = false;
   (yyval.tree)->attr.value = (yyvsp[0].Token_Data)->nvalue; 
   (yyval.tree)->size = 1;}
#line 2156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 421 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data)); 
   (yyval.tree)->type = ExpType::Char; 
   (yyval.tree)->attr.cvalue = (yyvsp[0].Token_Data)->cvalue;
   (yyval.tree)->isArray = false;
   (yyval.tree)->size = 1;}
#line 2166 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 427 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data)); 
   (yyval.tree)->type = ExpType::Char;
   (yyval.tree)->attr.string = (yyvsp[0].Token_Data)->svalue;
   (yyval.tree)->isArray = true;
   (yyval.tree)->size = (yyvsp[0].Token_Data)->nvalue + 1;}
#line 2176 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 433 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ExpKind::ConstantK, (yyvsp[0].Token_Data)); 
   (yyval.tree)->type = ExpType::Boolean; 
   (yyval.tree)->isArray = false;
   (yyval.tree)->attr.value = (yyvsp[0].Token_Data)->nvalue;
   (yyval.tree)->size = 1; }
#line 2186 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2190 "parser.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 440 "parser.y" /* yacc.c:1906  */


char *largerTokens[LASTTERM+1]; // used in the utils.cpp file printing routines
// create a mapping from token class enum to a printable name in a
// way that makes it easy to keep the mapping straight.
 void initTokenStrings()
 {
   largerTokens[ADDASS] = (char *)"+=";
   largerTokens[AND] = (char *)"and";
   largerTokens[BOOL] = (char *)"bool";
   largerTokens[BOOLCONST] = (char *)"boolconst";
   largerTokens[BREAK] = (char *)"break";
   largerTokens[BY] = (char *)"by";
   largerTokens[CHAR] = (char *)"char";
   largerTokens[CHARCONST] = (char *)"charconst";
   largerTokens[CHSIGN] = (char *)"chsign";
   largerTokens[DEC] = (char *)"--";
   largerTokens[DIVASS] = (char *)"/=";
   largerTokens[DO] = (char *)"do";
   largerTokens[ELSE] = (char *)"else";
   largerTokens[EQ] = (char *)"==";
   largerTokens[FOR] = (char *)"for";
   largerTokens[GEQ] = (char *)">=";
   largerTokens[ID] = (char *)"id";
   largerTokens[IF] = (char *)"if";
   largerTokens[INC] = (char *)"++";
   largerTokens[INT] = (char *)"int";
   largerTokens[LEQ] = (char *)"<=";
   largerTokens[MAX] = (char *)":>:";
   largerTokens[MIN] = (char *)":<:";
   largerTokens[MULASS] = (char *)"*=";
   largerTokens[NEQ] = (char *)"!=";
   largerTokens[NOT] = (char *)"not";
   largerTokens[NUMCONST] = (char *)"numconst";
   largerTokens[OR] = (char *)"or";
   largerTokens[RETURN] = (char *)"return";
   largerTokens[SIZEOF] = (char *)"sizeof";
   largerTokens[STATIC] = (char *)"static";
   largerTokens[STRINGCONST] = (char *)"stringconst";
   largerTokens[SUBASS] = (char *)"-=";
   largerTokens[THEN] = (char *)"then";
   largerTokens[TO] = (char *)"to";
   largerTokens[WHILE] = (char *)"while";
   largerTokens[LASTTERM] = (char *)"lastterm";
 }

 static char tokenBuffer[16];
 char *tokenToStr(int type)
  { 
   if (type>LASTTERM) {
   return (char*)"UNKNOWN";
    }
    else if (type > 256) {
   return largerTokens[type];
    }   else if ((type < 32) || (type > 127)) {
  sprintf(tokenBuffer, "Token#%d", type);
    } else {
   tokenBuffer[0] = type;
  tokenBuffer[1] = '\0';
    }
    return tokenBuffer;
}

/* void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}
*/

int main(int argc, char **argv) 
{
   // these lines allow us to read information from the parser.l file
   yylval.Token_Data = (Token_Data*)malloc(sizeof(Token_Data));
   yylval.tree = (TreeNode*)malloc(sizeof(TreeNode));
   yylval.Token_Data->linenum = 1;

   int opt, index;
   char *file = NULL;
   bool dotAST = false;
   extern FILE *yyin;
   
   initErrorProcessing();

   while ((opt = getopt(argc, argv, "w")) != -1)
   {
      switch (opt)
      {
         case 'w':
            dotAST = true;
            break;
         case '?':
         default:
           ;
      }
   }

   initTokenStrings();

   if ( optind == argc ) yyparse();
   for (index = optind; index < argc; index++) 
   {
      yyin = fopen (argv[index], "r");
      yyparse();
      fclose (yyin);
   }

   // create vars for slide code
   bool debugSymTab = false; 
   static int globalOffset = 0;

   // from slides NOTE: this code doesn't seem to allow printTree() 
   // to print anything yet..for some reason...

   SymbolTable *symtab;

   // Initialize symbol table
   symtab = new SymbolTable();
   symtab->debug(debugSymTab);

   // Initialize Syntax Tree and Symbol Table for semantic analysis
   syntaxTree = semanticAnalysis(syntaxTree, true, false, symtab, globalOffset);
   // CODEGEN!!!!!
   // codegen(stdout, argv[1], syntaxTree, symtab, globalOffset, false);

   // TreeTraverse Call
   treeTraverse(syntaxTree, symtab);

   if(numErrors == 0)
   {
      // printTree(stdout, syntaxTree, true, true);
      if (dotAST)
      {
        // printTree(stdout, syntaxTree, true, false);
      }
   }
   else 
   {
//      printf("/****************\n");
//      printf("Error: %d\n", numErrors);
//      printf("*****************/\n");
      // printf("Number of warnings: %d\n", numWarnings);
      // printf("Number of errors: %d\n", numErrors);
   } 
   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}
