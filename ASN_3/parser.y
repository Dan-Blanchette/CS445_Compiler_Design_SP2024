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
   struct TokenData *tokenData;
   struct TreeNode *tree;
   ExpType type; // for passing type spec up the tree
}

%type <tokenData> sumop mulop unaryop
%type <tokenData> assignop relop minmaxop

%type <tree> program precompList compoundstmt
%type <tree> parmList parmId parms parmTypeList parmIdList args argList
%type <tree> exp minmaxExp mulExp relExp simpleExp sumExp unaryExp expstmt unaryRelExp andExp
%type <tree> declList decl factor funDecl iterRange immutable mutable call constant localDecls
%type <tree> scopedVarDecl
%type <tree> stmt stmtList returnstmt breakstmt 
%type <tree> varDecl varDeclList varDeclId varDeclInit
%type <tree> unmatched matched

%type <type> typeSpec

%token <tokenData> FIRSTOP
%token <tokenData> ADDASS DIVASS MULASS SUBASS
%token <tokenData> AND OR NOT
%token <tokenData> EQ GEQ LEQ NEQ
%token <tokenData> MIN MAX INC DEC
%token <tokenData> '*' '-' '/' '+' '<' '>' '=' '%' '?'
%token <tokenData> PRECOMPILER
%token <tokenData> LASTOP

%token <tokenData> IF BOOL THEN ELSE FOR INT BY TO RETURN STATIC DO WHILE BREAK CHAR 
%token <tokenData> ID 
%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST
%token <tokenData> ':' '[' ']' '(' ')' '{' '}' ';' ','
%token <tokenData> LASTTERM


%%
// rule 1
program : precompList declList {syntaxTree = $2; cout << "program : precompList decList" << endl;}
   ;

// rule 2
precompList : precompList PRECOMPILER {$$ = NULL;}
   | PRECOMPILER {$$ = NULL; printf("%s\n", yyval.tinfo->tokenstr);}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 3
declList : declList decl {}
   | decl {}
   ;

// rule 4
decl : varDecl {}
   | funDecl {}
   ;

//rule 5
varDecl : typeSpec varDeclList  ';' {}
   ;

// rule 6
scopedVarDecl : STATIC typeSpec varDeclList ';' {}
   | typeSpec varDeclList ';' {}
   ;

// rule 7
varDeclList : varDeclList ',' varDeclInit {}
   | varDeclInit {}
   ;

// rule 8
varDeclInit : varDeclId {}
   | varDeclId ':' simpleExp {}
   ;

// rule 9
varDeclId : ID {}
   | ID '[' NUMCONST ']' {}
   ;

// rule 10
typeSpec : INT {}
   | BOOL {}
   | CHAR {}
   ;

// rule 11
funDecl : typeSpec ID '(' parms ')' stmt {}
   | ID '(' parms ')' stmt {}
   ;

// rule 12
parms : parmList {}
   | /*empty*/
   ;

// rule 13
parmList : parmList ',' parmId {}
   | parmId {}
   ;

// rule 14
parmTypeList : typeSpec parmIdList {}
   | parmId {}
   ;

// rule 15
parmIdList : parmIdList ',' parmId  {}
   | parmId  {}
   ;

// rule 16
parmId : ID {}
   | ID '['']' {}
   ;

// rule 17
stmt : matched {}
   | unmatched {}
   ;

// rule 18
matched : IF simpleExp THEN matched ELSE matched {}
   | WHILE simpleExp DO matched {}
   | FOR ID '=' iterRange DO matched {}
   | expstmt {}
   | compoundstmt {}
   | returnstmt {}
   | breakstmt {}
   ;

// rule 19
iterRange : simpleExp TO simpleExp {}
   | simpleExp TO simpleExp BY simpleExp {}
   ;

// rule 20
unmatched : IF simpleExp THEN stmt {}
   | IF simpleExp THEN matched ELSE unmatched {}
   | WHILE simpleExp DO unmatched {}
   | FOR ID '=' iterRange DO unmatched {}
   ;

// rule 21
expstmt : exp ';' {}
   | ';'
   ;

// rule 22
compoundstmt : '{' localDecls stmtList '}' {}
   ;

// rule 23
localDecls : localDecls scopedVarDecl {}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 24
stmtList : stmtList stmt {}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 25
returnstmt : RETURN ';' {}
   | RETURN exp ';' {}
   ;

//rule 26
breakstmt : BREAK ';' {}
   ;

// rule 27
exp : mutable assignop exp {}
   | mutable INC {}
   | mutable DEC {}
   | simpleExp {}
   | mutable assignop error {} 
   ;

// rule 28
assignop : '=' {}
   | ADDASS {}
   | SUBASS {}
   | MULASS {}
   | DIVASS {}
   ;

// rule 29
simpleExp : simpleExp OR andExp {}
   | andExp {}
   ;

// rule 30
andExp : andExp AND unaryRelExp {}
   | unaryRelExp {}
   ;

// rule 31
unaryRelExp : NOT unaryRelExp {}
   | relExp {}
   ;

// rule 32
relExp : minmaxExp relop minmaxExp {}
   | minmaxExp {}
   ;

// rule 33
relop : LEQ {}
   | '<' {}
   | '>' {}
   | GEQ {}
   | EQ  {}
   | NEQ {}
   ;

// rule 34
minmaxExp : minmaxExp minmaxop sumExp {}
   | sumExp {}
   ;

// rule 35
minmaxop : MAX {}
   | MIN {}
   ;

// rule 36
sumExp : sumExp sumop mulExp {}
   | mulExp {}
   ;

// rule 37
sumop : '+' {}
   | '-'
   ;

// rule 38
mulExp : mulExp mulop unaryExp {}
   | unaryExp {}
   ;

// rule 39
mulop : '*' {}
   | '/'
   | '%'
   ;

// rule 40
unaryExp : unaryop unaryExp {}
   | factor {}
   ;

// rule 41
unaryop : unaryop '-' {}
   | '*' {}
   | '?' {}
   ;

// rule 42
factor : immutable {}
   | mutable {}
   ;

// rule 43
mutable : ID {}
   | ID '[' exp ']' {}
   ;

// rule 44
immutable : '(' exp ')' {}
   | call {}
   | constant {}
   ;

// rule 45
call : ID '(' args ')' {}
   ;

// rule 46
args : argList {}
   | /* empty */ {$$ = NULL;}
   ;

// rule 47
argList : argList ',' exp {}
   | exp {}
   ;

// rule 48
constant : NUMCONST {}
   | CHARCONST {}
   | STRINGCONST {} 
   | BOOLCONST {}
   ;

%%
void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}
int main(int argc, char **argv) {
   // these lines allow us to read information from the parser.l file
   yyval.tinfo = (TokenData*)malloc(sizeof(TokenData));
   yyval.tree = (TreeNode*)malloc(sizeof(TreeNode));
   yylval.tinfo->linenum = 1;
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
