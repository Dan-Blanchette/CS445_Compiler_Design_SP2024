#include "codegen.h"

/*IMPORTANT NOTES:
// For function nodes the offset is defined to be the position of the
// function in the code space! This is accessible via the symbol table.
// remember where this function is:
  currentNode->offset = emitSkip(0); // offset holds the instruction address!!

  // Store return address
   emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");
*/


// Globals
extern int numErrors;
extern int numWarnings;
extern void yyparse();
extern int yydebug;
extern TreeNode *syntaxTree;
extern char **largerTokens;
extern void initTokenStrings();

// Thes offsets never change
#define OFPOFF 0
#define RETURNOFFSET -1

int toffset; // next available temporary space

FILE *code;

static bool linumFlag;
static int breakloc;
static SymbolTable *globals;

// This is the top level code generator call
void codegen(FILE *codeIn,          // where the code should be written
             char *srcFile,         // name of file compiled
             TreeNode *syntaxTree,  // tree to process
	          SymbolTable *globalsIn,     // globals so function info can be found
	          int globalOffset,      // size of the global frame
             bool linenumFlagIn)   // comment with line numbers
{
   int initJump;

   code = codeIn;
   globals = globalsIn;
   linenumFlag = linenumFlagIn;
   breakloc = 0;

   initJump = emitSkip(1);
   codegenHeader(srcFile);
   codegenGeneral(syntaxTree);
   codegenInit(initJump, globalOffset);
}

void commentLineNum(TreeNode *currentNode)
{
   char buf[16];

   if (linumFlag)
   {
      sprintf(buf, "%d", currentNode->lineno);
      emitComment((char *)"Line:", buf);
   }
}

void codegenStatment(TreeNode *currentNode)
{
   switch(currentNode->kind.stmt)
   {
      case StmtKind::IfK:
      case StmtKind::WhileK:
      case StmtKind::ForK:
      case StmtKind::CompoundK:
      case StmtKind::ReturnK:
      case StmtKind::BreakK:
      case StmtKind::RangeK:
      default:
   }
}
void codegenExpression(TreeNode *currentNode)
{
   switch(currentNode->kind.exp)
   {
      case ExpKind::AssignK:
      case ExpKind::CallK:
      case ExpKind::ConstantK:
      case ExpKind::IdK:
      case ExpKind::OpK:
      default:
   }
}
void codegenDecl(TreeNode *currentNode)
{
   switch(currentNode->kind.decl)
   {
      case DeclKind::VarK:
         // You have a lot to do here!!!!
         break;
      case DeclKind::FuncK:
         if (currentNode->lineno == -1)
         {
            codegenLibraryFun(currentNode); // need to define codegenLibraryFun
         }
         else
         {
            codegenFun(currentNode);
         }
      case DeclKind::ParamK:
      // IMPORTANT: no instructions need to be allocated for parameters here
      break;
   }
}

// nice comments describing what is compiled
void codegenHeader(char *srcFile)
{
   emitComment((char *)"bC compiler version bC-Su23");
   emitComment((char *)"File compiled:", srcFile);
}
// general code including the I/O library
void codegenGeneral(TreeNode *currentNode)
{
   while(currentNode)
   {
      switch (currentNode->nodekind)
      {
         case StmtK:
            codegenStatment(currentNode);
            break;
         case ExpK:
            emitComment((char *)"EXPRESSION");
            codegenExpression(currentNode);
            break;
         case DeclK:
            codegenDecl(currentNode);
            break;
      }
      currentNode = currentNode->sibling;
   }
}
// generation of initialization for run
int codegenInit(int initJump, int globalOffset)
{

}

void codegenLibraryFun(TreeNode *currentNode)
{
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
   emitComment((char *)"FUNCTION", currentNode->attr.name);

   // remember where this function is 
   currentNode->offset = emitSkip(0);

   // store the return address
   emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");

   // NEXT SLIDES HERE
   if (strcmp(currentNode->attr.name, (char *)"input") == 0)
   {
      emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
   }
   else if (strcmp(currentNode->attr.name, (char *)"inputb") == 0)
   {
      emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
   }
   else if (strcmp(currentNode->attr.name, (char *)"inputc") == 0)
   {
      emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
   }
   else if (strcmp(currentNode->attr.name, (char *)"output") == 0)
   {
      emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
      emitRO((char *)"OUT", AC, AC, AC, (char *)"Output integer");
   }
   else if (strcmp(currentNode->attr.name, (char *)"outputb") == 0)
   {
      emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
      emitRO((char *)"OUTB", AC, AC, AC, (char *)"Output bool");
   }
   else if (strcmp(currentNode->attr.name, (char *)"outputc") == 0)
   {
      emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
      emitRO((char *)"OUTC", AC, AC, AC, (char *)"Output char");
   }
   else if (strcmp(currentNode->attr.name, (char *)"outnl") == 0)
   {
      emitRO((char *)"OUTNL", AC, AC, AC, (char *)"Output a newline");
   }
   else
   {
      emitComment((char *)"ERROR(LINKER): No support for special function");
      emitComment(currentNode->attr.name);
   }
   // endIf

   emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
   emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
   emitGoto(0, AC, (char *)"Return");

   emitComment((char *)"END FUNCTION", currentNode->attr.name);
}

void codegenFun(TreeNode *currentNode)
{
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
   emitComment((char *)"FUNCTION", currentNode->attr.name);
   toffset = currentNode->size; // recover the end of activation record
   emitComment((char *)"TOFF set:",toffset);
}