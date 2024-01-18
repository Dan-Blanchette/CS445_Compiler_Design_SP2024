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
%token   <tinfo>  AND
%token   <tinfo>  MIN
%token   <tinfo>  PRECOMPILER
%token   <tinfo>  NUMCONST
%token   <tinfo>  ERROR 
%type <tinfo>  term program
%%
program  :  program term
   |  term  {$$=$1;}
   ;
term  : 
      OP {printToken(yylval.tinfo, "OP");}
   |  NEQ {printToken(yylval.tinfo, "NEQ");}
   |  MIN {printToken(yyval.tinfo, "MIN");}
   |  AND {printToken(yylval.tinfo, "AND");}
   |  PRECOMPILER {printToken(yylval.tinfo, "PRECOMPILER");}
   |  NUMCONST {printToken(yylval.tinfo, "NUMCONST");}
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

