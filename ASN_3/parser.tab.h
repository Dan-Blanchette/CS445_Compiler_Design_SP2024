/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FIRSTOP = 258,                 /* FIRSTOP  */
    ADDASS = 259,                  /* ADDASS  */
    DIVASS = 260,                  /* DIVASS  */
    MULASS = 261,                  /* MULASS  */
    SUBASS = 262,                  /* SUBASS  */
    AND = 263,                     /* AND  */
    OR = 264,                      /* OR  */
    NOT = 265,                     /* NOT  */
    EQ = 266,                      /* EQ  */
    GEQ = 267,                     /* GEQ  */
    LEQ = 268,                     /* LEQ  */
    NEQ = 269,                     /* NEQ  */
    MIN = 270,                     /* MIN  */
    MAX = 271,                     /* MAX  */
    INC = 272,                     /* INC  */
    DEC = 273,                     /* DEC  */
    PRECOMPILER = 274,             /* PRECOMPILER  */
    LASTOP = 275,                  /* LASTOP  */
    IF = 276,                      /* IF  */
    BOOL = 277,                    /* BOOL  */
    THEN = 278,                    /* THEN  */
    ELSE = 279,                    /* ELSE  */
    FOR = 280,                     /* FOR  */
    INT = 281,                     /* INT  */
    BY = 282,                      /* BY  */
    TO = 283,                      /* TO  */
    RETURN = 284,                  /* RETURN  */
    STATIC = 285,                  /* STATIC  */
    DO = 286,                      /* DO  */
    WHILE = 287,                   /* WHILE  */
    BREAK = 288,                   /* BREAK  */
    CHAR = 289,                    /* CHAR  */
    ID = 290,                      /* ID  */
    BOOLCONST = 291,               /* BOOLCONST  */
    NUMCONST = 292,                /* NUMCONST  */
    CHARCONST = 293,               /* CHARCONST  */
    STRINGCONST = 294,             /* STRINGCONST  */
    LASTTERM = 295                 /* LASTTERM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 71 "parser.y"

   struct TokenData *tokenData;
   struct TreeNode *tree;
   ExpType type; // for passing type spec up the tree

#line 110 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
