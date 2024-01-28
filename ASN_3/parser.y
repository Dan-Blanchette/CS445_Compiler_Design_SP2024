%{
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "treeUtils.h"
#include "scanType.h"
#include "dot.h"
using namespace std;



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
   // make sure t is not the null value. If it is, return s;
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
   return t;
}

// the syntax tree goes here
TreeNode *syntaxTree;

void yyerror(const char *msg);

void printToken(TokenData myData, string tokenName, int type = 0) {
   cout << "Line: " << myData.linenum << " Type: " << tokenName;
   if(type==0)
     cout << " Token: " << myData.tokenstr;
   if(type==1)
     cout << " Token: " << myData.nvalue;
   if(type==2)
     cout << " Token: " << myData.cvalue;
   cout << endl;
}

%}
%union
{
   TokenData *tokenData;
   TreeNode *tree;
   ExpType type; // for passing type spec up the tree
}

%type <tokenData> sumop mulop unaryop
%type <tokenData> assignop relop minmaxop

%type <tree> program
%type <tree> precompList
%type <tree> decList decl 
%type <tree> varDecl varDecList funDecl
%type <tree> typeSpec 

%type <type> typeSpec

%token <tokenData> FIRSTOP
%token <tokenData> ADDASS DIVASS MULASS SUBASS
%token <tokenData> AND OR NOT
%token <tokenData> EQ GEQ LEQ NEQ
%token <tokenData> MIN MAX INC DEC
%token <tokenData> '*' '-' '/' '+' '<' '>' '=' '%' '?'
%token <tokenData> PRECOMPILER
%token <tokenData> LASTOP

%token <tokenData> IF ELSE FOR DO INT RETURN STATIC THEN TO WHILE BOOL BREAK CHAR BY
%token <tokenData> ID 
%token <tokenData> BOOLCONST CHARCONST STRINGCONST NUMCONST
%token <tokenData> ':' '[' ']' '(' ')' '{' '}' ';' ','
%token <tokenData> LASTTERM



%%
program  :  program term
   |  term  {$$=$1;}
   ;
term  : 
      OP {printToken(yylval.tinfo, "OP");}
   |  NEQ {printToken(yylval.tinfo, "NEQ");}
   |  LEQ {printToken(yylval.tinfo, "LEQ");}
   |  GEQ {printToken(yylval.tinfo, "GEQ");}
   |  INC {printToken(yylval.tinfo, "INC");}
   |  DEC {printToken(yylval.tinfo, "DEC");}
   |  EQ  {printToken(yylval.tinfo, "EQ");}
   |  ADDASS {printToken(yylval.tinfo, "ADDASS");}
   |  SUBASS {printToken(yylval.tinfo, "SUBASS");}
   |  MULASS {printToken(yylval.tinfo, "MULASS");}
   |  DIVASS {printToken(yylval.tinfo, "DIVASS");}
   |  MIN {printToken(yylval.tinfo, "MIN");}
   |  MAX {printToken(yylval.tinfo, "MAX");}
   |  INT {printToken(yylval.tinfo, "INT");}
   |  CHAR{printToken(yylval.tinfo, "CHAR");}
   |  BOOL{printToken(yylval.tinfo, "BOOL");}
   |  AND {printToken(yylval.tinfo, "AND");}
   |  OR  {printToken(yylval.tinfo, "OR");}
   |  FOR  {printToken(yylval.tinfo, "FOR");}
   |  TO {printToken(yylval.tinfo, "TO");}
   |  DO {printToken(yylval.tinfo, "DO");}
   |  NOT {printToken(yylval.tinfo, "NOT");}
   |  BY {printToken(yylval.tinfo, "BY");}
   |  WHILE  {printToken(yylval.tinfo, "WHILE");}
   |  IF {printToken(yylval.tinfo, "IF");}
   |  ID {printToken(yylval.tinfo, "ID");}
   |  THEN {printToken(yylval.tinfo, "THEN");}
   |  ELSE {printToken(yylval.tinfo, "ELSE");}
   |  STATIC {printToken(yylval.tinfo, "STATIC");}
   |  RETURN {printToken(yylval.tinfo, "RETURN");}
   |  BREAK  {printToken(yylval.tinfo, "BREAK");}
   |  PRECOMPILER {printToken(yylval.tinfo, "PRECOMPILER");}
   |  NUMCONST {printToken(yylval.tinfo, "NUMCONST");}
   |  BOOLCONST {printToken(yyval.tinfo, "BOOLCONST");}
   |  CHARCONST {printToken(yylval.tinfo, "CHARCONST");}
   |  STRINGCONST {printToken(yylval.tinfo, "STRINGCONST");}
   |  ERROR    {cout << "ERROR(SCANNER Line " << yylval.tinfo.linenum << "): Invalid input character " << yylval.tinfo.tokenstr << endl; }
   ;
%%
void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}
int main(int argc, char **argv) {
   yylval.tinfo.linenum = 1;
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
   return 0;
}
