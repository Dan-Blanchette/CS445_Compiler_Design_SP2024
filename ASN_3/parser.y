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
scopedVarDecl : STATIC typeSpec varDeclList ';' {$$ = $3;}
   | typeSpec varDeclList ';' {$$ = $2;}
   ;

// rule 7
varDeclList : varDeclList ',' varDeclInit {$$ = addSibling($1, $3);}
   | varDeclInit {$$ = $1;}
   ;

// rule 8
varDeclInit : varDeclId {$$ = $1;}
   | varDeclId ':' simpleExp {$$ = $1, $3;}
   ;

// rule 9
varDeclId : ID {$$ = newDeclNode(DeclKind::VarK, ExpType::UndefinedType, $1);}
   | ID '[' NUMCONST ']' {$$ = newDeclNode(DeclKind::VarK, ExpType::UndefinedType, $1);
     $$->isArray = true; $$->size = $3->nvalue + 1; }
   ;

// rule 10
typeSpec : INT {$$ = ExpType::Integer;}
   | BOOL {$$ = ExpType::Boolean;}
   | CHAR {$$ = ExpType::Char;}
   ;

// rule 11
// second production is not making sense to me
funDecl : typeSpec ID '(' parms ')' stmt {$$ = newDeclNode(DeclKind::FuncK, $1, $2, $4, $6);}
   | ID '(' parms ')' stmt {$$ = newDeclNode(DeclKind::FuncK, ExpType::Void, $1, $3, $5);}
   ;

// rule 12
parms : parmList {$$ = $1;}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 13
parmList : parmList ',' parmTypeList {$$ = addSibling($1, $3);}
   | parmTypeList {$$ = $1;}
   ;

// rule 14
parmTypeList : typeSpec parmIdList {$$ = $2;}
   | parmId {$$ = $1;}
   ;

// rule 15
// if the start token matches the first production, add a sibling.
// in this case, parmList : parmIdList indicates this relationship.
// So $$ = $1(parmIdList) is a child node
// we don't want the ',' to become a node so $2 aka ',' is of no use to us.
// and $3 parmId is a sibling to $1 parmIdList.

parmIdList : parmIdList ',' parmId  {$$ = addSibling($1, $3);}
   | parmId  {$$ = $1;}
   ;

// rule 16
parmId : ID {$$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); $$->isArray = false; $$->size = 1;}
   | ID '['']' {$$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); $$->isArray = true; $$->size = 1;}
   ;

// rule 17
stmt : matched {$$ = $1; cout << "stmt : matched" << endl;}
   | unmatched {$$ = $1; cout << "| unmatched" << endl;}
   ;

// rule 18
// newStmtNode(IfK,)
// newStmtNode(WhileK,)
// newStmtNode(ForK,)
matched : IF simpleExp THEN matched ELSE matched {$$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6);}
   | WHILE simpleExp DO matched {$$ = newStmtNode(StmtKind::WhileK, $1, $2, $4);}
   | FOR ID '=' iterRange DO matched {$$ = newStmtNode(StmtKind::ForK, $1, NULL, $4, $6); $$->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, $2);
        $$->child[0]->attr.name = $2->svalue; $$->child[0]->isArray = false; 
        $$->child[0]->size = 1;}
   | expstmt {$$ = $1;}
   | compoundstmt {$$ = $1;}
   | returnstmt {$$ = $1;}
   | breakstmt {$$ = $1;}
   ;

// rule 19
// newStmtNode(RangeK,)
// newStmtNode(RangeK,) 
iterRange : simpleExp TO simpleExp {$$ = newStmtNode(StmtKind::RangeK, $2, $1, $3);}
   | simpleExp TO simpleExp BY simpleExp {$$ = newStmtNode(StmtKind::RangeK, $2, $1, $3, $5);}
   ;

// rule 20
unmatched : IF simpleExp THEN stmt {$$ = newStmtNode(StmtKind::IfK, $1, $2, $4);}
   | IF simpleExp THEN matched ELSE unmatched {$$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6);}
   | WHILE simpleExp DO unmatched {$$ = newStmtNode(StmtKind::WhileK, $1, $2, $4);}
   | FOR ID '=' iterRange DO unmatched {$$ = newStmtNode(StmtKind::ForK, $1, NULL, $4, $6);
      $$->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, $2); 
      $$->child[0]->attr.name = $2->svalue;
      $$->child[0]->isArray = false; 
      $$->child[0]->size = 1;}
   ;

// rule 21
expstmt : exp ';' {$$ = $1;}
   | ';' {$$ = NULL;}
   ;

// rule 22
compoundstmt : '{' localDecls stmtList '}' {$$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3); cout << 
"compoundstmt : '{' localDecls stmtList '}'" << endl;}
   ;

// rule 23
localDecls : localDecls scopedVarDecl {$$ = addSibling($1, $2);}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 24
stmtList : stmtList stmt {$$ = addSibling($1, $2);}
   | /*empty*/ {$$ = NULL;}
   ;

// rule 25
returnstmt : RETURN ';' {$$ = newStmtNode(StmtKind::ReturnK, $1);}
   | RETURN exp ';' {$$ = newStmtNode(StmtKind::ReturnK, $1, $2);}
   ;

//rule 26
breakstmt : BREAK ';' {$$ = newStmtNode(StmtKind::BreakK, $1);}
   ;

// rule 27
exp : mutable assignop exp {$$ = newExpNode(ExpKind::AssignK, $2, $1, $3);}
   | mutable INC {$$ = newExpNode(ExpKind::AssignK, $2, $1);}
   | mutable DEC {$$ = newExpNode(ExpKind::AssignK, $2, $1);}
   | simpleExp {$$ = $1;}
   | mutable assignop error {$$ = newExpNode(ExpKind::AssignK, $2, $1, NULL);} 
   ;

// rule 28
assignop : '=' {$$ = $1;}
   | ADDASS {$$ = $1;}
   | SUBASS {$$ = $1;}
   | MULASS {$$ = $1;}
   | DIVASS {$$ = $1;}
   ;

// rule 29
simpleExp : simpleExp OR andExp {$$ = newExpNode(OpK, $2, $1, $3);}
   | andExp {$$ = $1;}
   ;

// rule 30
andExp : andExp AND unaryRelExp {$$ = newExpNode(OpK, $2, $1, $3);}
   | unaryRelExp {$$ = $1;}
   ;

// rule 31
unaryRelExp : NOT unaryRelExp {$$ = newExpNode(OpK, $1, $2);}
   | relExp {$$ = $1;}
   ;

// rule 32
relExp : minmaxExp relop minmaxExp {$$ = newExpNode(OpK, $2, $1, $3);}
   | minmaxExp {$$ = $1;}
   ;

// rule 33
relop : LEQ {$$ = $1;}
   | '<' {$$ = $1;}
   | '>' {$$ = $1;}
   | GEQ {$$ = $1;}
   | EQ  {$$ = $1;}
   | NEQ {$$ = $1;}
   ;

// rule 34
minmaxExp : minmaxExp minmaxop sumExp {$$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | sumExp {$$ = $1;}
   ;

// rule 35
minmaxop : MAX {$$ = $1;}
   | MIN {$$ = $1;}
   ;

// rule 36
sumExp : sumExp sumop mulExp {$$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | mulExp {$$ = $1;}
   ;

// rule 37
sumop : '+' {$$ = $1;}
   | '-' {$$ = $1;}
   ;

// rule 38
mulExp : mulExp mulop unaryExp {$$ = newExpNode(ExpKind::OpK, $2, $1, $3);}
   | unaryExp {$$ = $1;}
   ;

// rule 39
mulop : '*' {$$ = $1;}
   | '/' {$$ = $1;}
   | '%' {$$ = $1;}
   ;

// rule 40
unaryExp : unaryop unaryExp {$$ = newExpNode(ExpKind::OpK,$1, $2);}
   | factor {$$ = $1;}
   ;

// rule 41
unaryop : '-' {$$ = $1;}
   | '*' {$$ = $1;}
   | '?' {$$ = $1;}
   ;

// rule 42
factor : immutable {$$ = $1;}
   | mutable {$$ = $1;}
   ;

// rule 43
// not sure about part 2 on this one
mutable : ID {$$ = newExpNode(ExpKind::IdK, $1); $$->isArray = false; $$->attr.name = $1->svalue;}
   | ID '[' exp ']' {$$ = newExpNode(ExpKind::OpK, $2, NULL, $3); $$->isArray = false; 
      $$->child[0] = newExpNode(ExpKind::IdK, $1); $$->child[0]->attr.name = $1->svalue;} 
   ;

// rule 44
immutable : '(' exp ')' {$$ = $2;}
   | call {$$ = $1;}
   | constant {$$ = $1;}
   ;

// rule 45
// Here we want the ID as the root and args as the children
// We must also store the string name of the ID in the ExpKind struct
// as part of the new node's information block.

call : ID '(' args ')' {$$ = newExpNode(ExpKind::CallK, $1, $3);
   $$->attr.name = $1->svalue;}
   ;

// rule 46
args : argList {$$ = $1;}
   | /* empty */ {$$ = NULL;}
   ;

// rule 47  in this rule, production 1 arglist repeats the definition on the 
// production side so a sibling relationship is required here.
// we use $1 because arglist is a treeType and also the 3rd entry exp is as well
// ',' is not and we will not need to make a new node for it.

argList : argList ',' exp {$$ = addSibling($1, $3);}
   | exp {$$ = $1;}
   ;

// rule 48
constant : NUMCONST {$$ = newExpNode(ExpKind::ConstantK, $1); $$->type = ExpType::Integer;
   $$->isArray = false; $$->size = 1; $$->attr.value = $1->nvalue;}
   | CHARCONST {$$ = newExpNode(ExpKind::ConstantK, $1); $$->type = ExpType::Char; $$->attr.cvalue = $1->cvalue;
      $$->isArray = false; $$->size = 1;}
   | STRINGCONST {$$ = newExpNode(ExpKind::ConstantK, $1); $$->isArray = true; $$->type = ExpType::Char;
      $$->size = $1->nvalue + 1; $$->attr.string = $1->svalue;} 
   | BOOLCONST {$$ = newExpNode(ExpKind::ConstantK, $1); $$->type = ExpType::Boolean; $$->isArray = false;
      $$->size = 1; $$->attr.value = $1->nvalue;}
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
