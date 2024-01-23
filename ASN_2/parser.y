%{
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "scanType.h"
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

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
   struct   TokenData tinfo ;
}
%token   <tinfo>  OP
%token   <tinfo>  NEQ
%token   <tinfo>  LEQ
%token   <tinfo>  GEQ
%token   <tinfo>  INC
%token   <tinfo>  DEC
%token   <tinfo>  EQ
%token   <tinfo>  ADDASS
%token   <tinfo>  SUBASS
%token   <tinfo>  MULASS
%token   <tinfo>  DIVASS
%token   <tinfo>  MIN
%token   <tinfo>  MAX 
%token   <tinfo>  INT
%token   <tinfo>  CHAR
%token   <tinfo>  BOOL
%token   <tinfo>  AND
%token   <tinfo>  OR
%token   <tinfo>  FOR
%token   <tinfo>  TO
%token   <tinfo>  DO
%token   <tinfo>  NOT
%token   <tinfo>  BY
%token   <tinfo>  WHILE
%token   <tinfo>  IF
%token   <tinfo>  THEN
%token   <tinfo>  ELSE
%token   <tinfo>  STATIC
%token   <tinfo>  RETURN
%token   <tinfo>  BREAK
%token   <tinfo>  PRECOMPILER
%token   <tinfo>  ID
%token   <tinfo>  NUMCONST
%token   <tinfo>  BOOLCONST
%token   <tinfo>  CHARCONST
%token   <tinfo>  STRINGCONST
%token   <tinfo>  ERROR 
%type <tinfo>  term program
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
   |  STRINGCONST {printToken(yylval.tinfo, "STRINGCONST);}
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
   extern FILE *yyin;
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

