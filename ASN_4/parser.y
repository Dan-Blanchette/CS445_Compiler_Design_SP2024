%{
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

using namespace std;

// Assignment 4 in progress...
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
   if(s == nullptr)
   {
      printf("ERROR: Sibling is equal to 0.");
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
%token <Token_Data> CHSIGN SIZEOF
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
program : precompList declList {syntaxTree = $2;}
   ;

// rule 2
// changing NULL to nullptr here. Not sure if that is the issue.
precompList : precompList PRECOMPILER {cout << yylval.Token_Data->tokenstr << "\n"; $$ = nullptr;}
   | PRECOMPILER                      {cout << yylval.Token_Data->tokenstr << "\n"; $$ = nullptr;}
   | /*empty*/                        {$$ = nullptr;}
   ;

// rule 3
declList : declList decl {$$ = addSibling($1, $2);}
   | decl                {$$ = $1;}
   ;

// rule 4
decl : varDecl {$$ = $1;}
   | funDecl   {$$ = $1;}
   ;

//rule 5
varDecl : typeSpec varDeclList  ';' {$$ = $2; setType($2, $1, false);}
   ;

// rule 6
// UPDATE; set isStatic value to false.
// has typeSpec in production which needs the setType function as part of node creation

scopedVarDecl : STATIC typeSpec varDeclList ';' {$$ = $3; setType($3, $2, true); $$->isStatic = true;}
   | typeSpec varDeclList ';'                   {$$ = $2; setType($2, $1, false); $$->isStatic=false;}
   ;

// rule 7
varDeclList : varDeclList ',' varDeclInit {$$ = addSibling($1, $3);}
   | varDeclInit                          {$$ = $1;}
   ;

// rule 8
varDeclInit : varDeclId      {$$ = $1;}
   | varDeclId ':' simpleExp {$$ = $1; $1->child[0] = $3;}
   ;

// rule 9
varDeclId : ID           {$$ = newDeclNode(DeclKind::VarK, UndefinedType, $1); $$->isArray = false; $$->size = 1;}
   | ID '[' NUMCONST ']' {$$ = newDeclNode(DeclKind::VarK, UndefinedType, $1); $$->isArray = true; $$->size = $3->nvalue + 1;}
   ;

// rule 10
typeSpec : INT {$$ = ExpType::Integer;}
   | BOOL      {$$ = ExpType::Boolean;}
   | CHAR      {$$ = ExpType::Char;}
   ;

// rule 11

funDecl : typeSpec ID '(' parms ')' stmt {$$ = newDeclNode(DeclKind::FuncK, $1, $2, $4, $6);}
   | ID '(' parms ')' stmt               {$$ = newDeclNode(DeclKind::FuncK, ExpType::Void, $1, $3, $5);}
   ;

// rule 12
// changed null to nullptr
parms : parmList {$$ = $1;}
   | /*empty*/   {$$ = nullptr;}
   ;

// rule 13
parmList : parmList ';' parmTypeList {$$ = addSibling($1, $3);}
   | parmTypeList                    {$$ = $1;}
   ;

// rule 14
// UPDATE: removed parmID was accidentally added as an OR condition for this production.
// has typeSpec in production which needs the setType function

parmTypeList : typeSpec parmIdList {$$ = $2; setType($2, $1, false);}
   ;

// rule 15
// if the start token matches the first production, add a sibling.
// in this case, parmList : parmIdList indicates this relationship.
// So $$ = $1(parmIdList) is a child node
// we don't want the ',' to become a node so $2 aka ',' is of no use to us.
// and $3 parmId is a sibling to $1 parmIdList.

parmIdList : parmIdList ',' parmId  {$$ = addSibling($1, $3);}
   | parmId                         {$$ = $1;}
   ;

// rule 16

parmId : ID    {$$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); 
                 $$->isArray = false; $$->isStatic = false; $$->size = 1;}
   | ID '['']' {$$ = newDeclNode(DeclKind::ParamK, ExpType::UndefinedType, $1); 
                 $$->isArray = true; $$->isStatic = false; $$->size = 1;}
   ;

// rule 17
stmt : matched {$$ = $1;}
   | unmatched {$$ = $1;}
   ;

// rule 18
// changed NULL to nullptr
matched : IF simpleExp THEN matched ELSE matched {$$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6);}
   | WHILE simpleExp DO matched                  {$$ = newStmtNode(StmtKind::WhileK, $1, $2, $4);}
   | FOR ID '=' iterRange DO matched             {$$ = newStmtNode(StmtKind::ForK, $1, nullptr, $4, $6);
                                                   $$->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, $2);
                                                   $$->child[0]->attr.name = $2->svalue;
                                                   $$->child[0]->isArray = false;
                                                   $$->child[0]->size = 1;}
   | expstmt      {$$ = $1;}
   | compoundstmt {$$ = $1;}
   | returnstmt   {$$ = $1;}
   | breakstmt    {$$ = $1;}
   ;

// rule 19
iterRange : simpleExp TO simpleExp       {$$ = newStmtNode(StmtKind::RangeK, $2, $1, $3);}
   | simpleExp TO simpleExp BY simpleExp {$$ = newStmtNode(StmtKind::RangeK, $2, $1, $3, $5);}
   ;

// rule 20
// UPDATE: removed extra struct variable assignments(not sure they were needed).

unmatched : IF simpleExp THEN stmt            {$$ = newStmtNode(StmtKind::IfK, $1, $2, $4);}
   | IF simpleExp THEN matched ELSE unmatched {$$ = newStmtNode(StmtKind::IfK, $1, $2, $4, $6);}
   | WHILE simpleExp DO unmatched             {$$ = newStmtNode(StmtKind::WhileK, $1, $2, $4);}
   | FOR ID '=' iterRange DO unmatched        {$$ = newStmtNode(StmtKind::ForK, $1, nullptr, $4, $6);
                                                $$->child[0] = newDeclNode(DeclKind::VarK, ExpType::Integer, $2);
                                                $$->child[0]->attr.name = $2->svalue;
                                                $$->child[0]->isArray = false;
                                                $$->child[0]->size = 1;}
   ;

// rule 21
// changed to NULL to nullptr
expstmt : exp ';' {$$ = $1;}
   | ';'          {$$ = nullptr;}
   ;

// rule 22
compoundstmt : '{' localDecls stmtList '}' {$$ = newStmtNode(StmtKind::CompoundK, $1, $2, $3);}
   | compoundstmt ';' {$$ = $1;}
   ;

// rule 23
// changed to NULL to nullptr

localDecls : localDecls scopedVarDecl {$$ = addSibling($1, $2);}
   | /*empty*/ {$$ = nullptr;}
   ;

// rule 24
// changed to NULL to nullptr
// removed turnary logic(going to see if this works)
stmtList : stmtList stmt { $$ = addSibling($1, $2);}
   | /*empty*/ {$$ = nullptr;}
   ;

// rule 25
returnstmt : RETURN ';' {$$ = newStmtNode(StmtKind::ReturnK, $1);}
   | RETURN exp ';'     {$$ = newStmtNode(StmtKind::ReturnK, $1, $2);}
   ;

//rule 26
breakstmt : BREAK ';'   {$$ = newStmtNode(StmtKind::BreakK, $1);}
   ;

// rule 27
exp : mutable assignop exp  {$$ = newExpNode(ExpKind::AssignK, $2, $1, $3); $$->isAssigned = true;}
   | mutable INC            {$$ = newExpNode(ExpKind::AssignK, $2, $1);}
   | mutable DEC            {$$ = newExpNode(ExpKind::AssignK, $2, $1);}
   | simpleExp              {$$ = $1;}
   | mutable assignop error {$$ = newExpNode(ExpKind::AssignK, $2, $1);} 
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
unaryop : '-' {$$ = $1; $$->svalue = (char *)"chsign";}
   | '*' {$$ = $1; $$->svalue = (char *)"sizeof";}
   | '?' {$$ = $1;}
   ;

// rule 42
factor : immutable {$$ = $1;}
   | mutable {$$ = $1;}
   ;

// rule 43
// not sure about part 2 on this one
mutable : ID {$$ = newExpNode(ExpKind::IdK, $1); 
         $$->isArray = false; $$->attr.name = $1->svalue; }
   | ID '[' exp ']' {$$ = newExpNode(ExpKind::OpK, $2, nullptr, $3); 
         $$->child[0] = newExpNode(ExpKind::IdK, $1);
         $$->child[0]->attr.name = $1->svalue;} 
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

call : ID '(' args ')' {$$ = newExpNode(ExpKind::CallK, $1, $3); $$->attr.name = $1->svalue;}
   ;

// rule 46
args : argList {$$ = $1;}
   | /* empty */ {$$ = nullptr;}
   ;

// rule 47  in this rule, production 1 arglist repeats the definition on the 
// production side so a sibling relationship is required here.
// we use $1 because arglist is a treeType and also the 3rd entry exp is as well
// ',' is not and we will not need to make a new node for it.

argList : argList ',' exp {$$ = addSibling($1, $3);}
   | exp {$$ = $1;}
   ;

// rule 48
constant : NUMCONST {$$ = newExpNode(ExpKind::ConstantK, $1); 
   $$->type = ExpType::Integer;
   $$->isArray = false;
   $$->attr.value = $1->nvalue; 
   $$->size = 1;}

   | CHARCONST {$$ = newExpNode(ExpKind::ConstantK, $1); 
   $$->type = ExpType::Char; 
   $$->attr.cvalue = $1->cvalue;
   $$->isArray = false;
   $$->size = 1;}

   | STRINGCONST {$$ = newExpNode(ExpKind::ConstantK, $1); 
   $$->type = ExpType::Char;
   $$->attr.string = $1->svalue;
   $$->isArray = true;
   $$->size = $1->nvalue + 1;} 

   | BOOLCONST {$$ = newExpNode(ExpKind::ConstantK, $1); 
   $$->type = ExpType::Boolean; 
   $$->isArray = false;
   $$->attr.value = $1->nvalue;
   $$->size = 1; }
   ;

%%

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

void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}

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

   // TreeTraverse Call
   treeTraverse(syntaxTree, symtab);

   if(numErrors == 0)
   {
      printTree(stdout, syntaxTree, true, true);
      if (dotAST)
      {
         printTree(stdout, syntaxTree, true, false);
      }
   }
   else 
   {
      printf("/****************\n");
      printf("Error: %d\n", numErrors);
      printf("*****************/\n");
   }
   printf("Number of warnings: %i\n", numWarnings);
   printf("Number of errors: %i\n", numErrors);
   return 0;
}
