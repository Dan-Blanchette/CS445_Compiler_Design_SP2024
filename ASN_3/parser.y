%{
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

%}

%union
{
   struct Token_Data *Token_Data;
   struct TreeNode *tree;
   ExpType type; // for passing type spec up the tree
}

%type <Token_Data> sumop mulop unaryop
%type <Token_Data> assignop relop minmaxop

%type <tree> program precompList compoundstmt
%type <tree> parmList parmId parms parmTypeList parmIdList args argList
%type <tree> exp minmaxExp mulExp relExp simpleExp sumExp unaryExp expstmt unaryRelExp andExp
%type <tree> declList decl factor funDecl iterRange immutable mutable call constant localDecls
%type <tree> scopedVarDecl
%type <tree> stmt stmtList returnstmt breakstmt 
%type <tree> varDecl varDeclList varDeclId varDeclInit
%type <tree> unmatched matched

%type <type> typeSpec

%token <Token_Data> FIRSTOP
%token <Token_Data> ADDASS DIVASS MULASS SUBASS
%token <Token_Data> AND OR NOT
%token <Token_Data> EQ GEQ LEQ NEQ
%token <Token_Data> MIN MAX INC DEC
%token <Token_Data> '*' '-' '/' '+' '<' '>' '=' '%' '?'
%token <Token_Data> PRECOMPILER
%token <Token_Data> LASTOP

%token <Token_Data> IF BOOL THEN ELSE FOR INT BY TO RETURN STATIC DO WHILE BREAK CHAR 
%token <Token_Data> ID 
%token <Token_Data> BOOLCONST NUMCONST CHARCONST STRINGCONST
%token <Token_Data> ':' '[' ']' '(' ')' '{' '}' ';' ','
%token <Token_Data> LASTTERM


%%
// rule 1
program : precompList declList {syntaxTree = $2; cout << "program : precompList decList" << endl;}
   ;

// rule 2
precompList : precompList PRECOMPILER {$$ = NULL;}
   | PRECOMPILER {$$ = NULL; printf("%s\n", yylval.Token_Data->tokenstr);}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 3
declList : declList decl {$$ = addSibling($1, $2);}
   | decl {$$ = $1; cout << "| funDecl" << endl;}
   ;

// rule 4
decl : varDecl {$$ = $1; cout << "varDecl" << endl;}
   | funDecl {$$ = $1; cout << "| funDecl" << endl;}
   ;

//rule 5
varDecl : typeSpec varDeclList  ';' {$$ = $2;}
   ;

// rule 6
scopedVarDecl : STATIC typeSpec varDeclList ';' {$$ = NULL;}
   | typeSpec varDeclList ';' {$$ = NULL;}
   ;

// rule 7
varDeclList : varDeclList ',' varDeclInit {$$ = NULL;}
   | varDeclInit {$$ = NULL;}
   ;

// rule 8
varDeclInit : varDeclId {$$ = NULL;}
   | varDeclId ':' simpleExp {$$ = NULL;}
   ;

// rule 9
varDeclId : ID {$$ = NULL;}
   | ID '[' NUMCONST ']' {$$ = NULL;}
   ;

// rule 10
typeSpec : INT {$$ = ExpType::Integer;}
   | BOOL {$$ = ExpType::Boolean;}
   | CHAR {$$ = ExpType::Char;}
   ;

// rule 11
funDecl : typeSpec ID '(' parms ')' stmt {$$ = newDeclNode(DeclKind::FuncK, $1, $2, $4, $6); cout <<"funDecl : typeSpec ID '(' parms ')' stmt"
 <<  endl;}
   | ID '(' parms ')' stmt {$$ = NULL;}
   ;

// rule 12
parms : parmList {$$ = NULL;}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 13
parmList : parmList ',' parmTypeList {$$ = NULL;}
   | parmTypeList {$$ = NULL;}
   ;

// rule 14
parmTypeList : typeSpec parmIdList {$$ = NULL;}
   | parmId {$$ = NULL;}
   ;

// rule 15
parmIdList : parmIdList ',' parmId  {$$ = $1;}
   | parmId  {$$ = $1;}
   ;

// rule 16
parmId : ID {$$ = NULL;}
   | ID '['']' {$$ = NULL;}
   ;

// rule 17
stmt : matched {$$ = $1; cout << "stmt : matched" << endl;}
   | unmatched {$$ = $1; cout << "| unmatched" << endl;}
   ;

// rule 18
matched : IF simpleExp THEN matched ELSE matched {$$ = NULL;}
   | WHILE simpleExp DO matched {$$ = NULL;}
   | FOR ID '=' iterRange DO matched {$$ = NULL;}
   | expstmt {$$ = NULL;}
   | compoundstmt {$$ = NULL;}
   | returnstmt {$$ = NULL;}
   | breakstmt {$$ = NULL;}
   ;

// rule 19
iterRange : simpleExp TO simpleExp {$$ = NULL;}
   | simpleExp TO simpleExp BY simpleExp {$$ = NULL;}
   ;

// rule 20
unmatched : IF simpleExp THEN stmt {$$ = NULL;}
   | IF simpleExp THEN matched ELSE unmatched {$$ = NULL;}
   | WHILE simpleExp DO unmatched {$$ = NULL;}
   | FOR ID '=' iterRange DO unmatched {$$ = NULL;}
   ;

// rule 21
expstmt : exp ';' {$$ = NULL;}
   | ';' {$$ = NULL;}
   ;

// rule 22
compoundstmt : '{' localDecls stmtList '}' {$$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3); cout << 
"compoundstmt : '{' localDecls stmtList '}'" << endl;}
   ;

// rule 23
localDecls : localDecls scopedVarDecl {$$ = NULL;}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 24
stmtList : stmtList stmt {$$ = NULL;}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 25
returnstmt : RETURN ';' {$$ = NULL;}
   | RETURN exp ';' {$$ = NULL;}
   ;

//rule 26
breakstmt : BREAK ';' {$$ = NULL;}
   ;

// rule 27
exp : mutable assignop exp {$$ = NULL;}
   | mutable INC {$$ = NULL;}
   | mutable DEC {$$ = NULL;}
   | simpleExp {$$ = NULL;}
   | mutable assignop error {$$ = NULL;} 
   ;

// rule 28
assignop : '=' {$$ = NULL;}
   | ADDASS {$$ = NULL;}
   | SUBASS {$$ = NULL;}
   | MULASS {$$ = NULL;}
   | DIVASS {$$ = NULL;}
   ;

// rule 29
simpleExp : simpleExp OR andExp {$$ = NULL;}
   | andExp {$$ = NULL;}
   ;

// rule 30
andExp : andExp AND unaryRelExp {$$ = NULL;}
   | unaryRelExp {$$ = NULL;}
   ;

// rule 31
unaryRelExp : NOT unaryRelExp {$$ = NULL;}
   | relExp {$$ = NULL;}
   ;

// rule 32
relExp : minmaxExp relop minmaxExp {$$ = NULL;}
   | minmaxExp {$$ = NULL;}
   ;

// rule 33
relop : LEQ {$$ = NULL;}
   | '<' {$$ = NULL;}
   | '>' {$$ = NULL;}
   | GEQ {$$ = NULL;}
   | EQ  {$$ = NULL;}
   | NEQ {$$ = NULL;}
   ;

// rule 34
minmaxExp : minmaxExp minmaxop sumExp {$$ = NULL;}
   | sumExp {$$ = NULL;}
   ;

// rule 35
minmaxop : MAX {$$ = NULL;}
   | MIN {$$ = NULL;}
   ;

// rule 36
sumExp : sumExp sumop mulExp {$$ = NULL;}
   | mulExp {$$ = NULL;}
   ;

// rule 37
sumop : '+' {$$ = NULL;}
   | '-'
   ;

// rule 38
mulExp : mulExp mulop unaryExp {$$ = NULL;}
   | unaryExp {$$ = NULL;}
   ;

// rule 39
mulop : '*' {$$ = NULL;}
   | '/'
   | '%'
   ;

// rule 40
unaryExp : unaryop unaryExp {$$ = NULL;}
   | factor {$$ = NULL;}
   ;

// rule 41
unaryop : unaryop '-' {$$ = NULL;}
   | '*' {$$ = NULL;}
   | '?' {$$ = NULL;}
   ;

// rule 42
factor : immutable {$$ = NULL;}
   | mutable {$$ = NULL;}
   ;

// rule 43
mutable : ID {$$ = NULL;}
   | ID '[' exp ']' {$$ = NULL;}
   ;

// rule 44
immutable : '(' exp ')' {$$ = NULL;}
   | call {$$ = NULL;}
   | constant {$$ = NULL;}
   ;

// rule 45
call : ID '(' args ')' {$$ = NULL;}
   ;

// rule 46
args : argList {$$ = NULL;}
   | /* empty */ {$$ = NULL;}
   ;

// rule 47
argList : argList ',' exp {$$ = NULL;}
   | exp {$$ = NULL;}
   ;

// rule 48
constant : NUMCONST {$$ = newExpNode(ExpKind::ConstantK, $1); $$->type = ExpType::Integer;}
   | CHARCONST {$$ = newExpNode(ExpKind::ConstantK, $1);
                $$->type = ExpType::Char;}
   | STRINGCONST {$$ = NULL;} 
   | BOOLCONST {$$ = NULL;}
   ;

%%
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
