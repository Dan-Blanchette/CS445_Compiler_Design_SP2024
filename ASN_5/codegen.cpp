#include "codegen.h"
#include "parser.tab.h"

/*IMPORTANT NOTES:
// For function nodes the offset is defined to be the position of the
// function in the code space! This is accessible via the symbol table.
// remember where this function is:
  currentNode->offset = emitSkip(0); // offset holds the instruction address!!

  // Store return address
   emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");

   4-21: All Slides code has been added. I've been working on the OpK in codegenExpression()
*/


// Globals
extern int numErrors;
extern int numWarnings;
// extern void yyparse();
extern int yydebug;
extern TreeNode *syntaxTree;
extern char **largerTokens;
extern void initTokenStrings();

// Thes offsets never change
#define OFPOFF 0
#define RETURNOFFSET -1

int toffset; // next available temporary space

FILE *code;

static bool linenumFlag;
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

void codegenStatment(TreeNode *currentNode)
{
   // local state to remember stuff
   int skiploc =0, skiploc2 = 0, currloc =0;
   TreeNode *loopindex = NULL;
   commentLineNum(currentNode);

   switch(currentNode->kind.stmt)
   {
      case StmtKind::IfK:
         emitComment((char *)"IF");
         break;
      case StmtKind::WhileK:
         emitComment((char *)"WHILE");
         currloc = emitSkip(0); // return here to do the test
         codegenExpression(currentNode->child[0]); // test expression

         emitRM((char *)"JNZ", AC, 1, PC, (char *)"Jump to while part");
         emitComment((char *)"DO");

         skiploc = breakloc;   // save the old break statement return point
         breakloc = emitSkip(1); // addr of instr that jumps to the end of the loop
                                // this is also the backpatch point
         codegenGeneral(currentNode->child[1]); // do body of loop
         emitGotoAbs(currloc, (char *)"go to beginning of loop");
         // backpatch jump to the end of the loop
         backPatchAJumpToHere(breakloc, (char *)"Jump past loop[backpatch]");
         breakloc = skiploc;
         emitComment((char *)"END WHILE");
         break;

      case StmtKind::ForK:
         emitComment((char *)"FOR");
         currloc = emitSkip(0); // return here to do the test
         codegenExpression(currentNode->child[0]); // test expression

         emitRM((char *)"JNZ", AC, 1, PC, (char *)"Jump to for part");
         emitComment((char *)"DO");

         skiploc = breakloc;   // save the old break statement return point
         breakloc = emitSkip(1); // addr of instr that jumps to the end of the loop
                                // this is also the backpatch point
         codegenGeneral(currentNode->child[1]); // do body of loop
         emitGotoAbs(currloc, (char *)"go to beginning of loop");
         // backpatch jump to the end of the loop
         backPatchAJumpToHere(breakloc, (char *)"Jump past loop[backpatch]");
         breakloc = skiploc;
         emitComment((char *)"END FOR");
         break;

      case StmtKind::CompoundK:
         int savedToffset;
         savedToffset = toffset;
         toffset = currentNode->size; // recover the end of activation record
         emitComment((char *)"COMPOUND");
         emitComment((char *)"TOFF set:", toffset);
         codegenGeneral(currentNode->child[0]); // process inits
         emitComment((char *)"Compound Body");
         codegenGeneral(currentNode->child[1]); // process the body
         toffset = savedToffset;
         emitComment((char *)"TOFF set:", toffset);
         emitComment((char *)"END COMPOUND");  
         break;

      case StmtKind::ReturnK: 
         emitComment((char *)"RETURN");
         break;

      case StmtKind::BreakK:
         emitComment((char *)"BREAK");
         break;

      case StmtKind::RangeK:
         emitComment((char *)"RANGE");
         break;
      default:
         break;
   }
}

void codegenExpression(TreeNode *currentNode)
{
   switch (currentNode->kind.exp)
   {
      case ExpKind::AssignK:
         emitComment((char *)"ASSIGN");
         if (currentNode->child[0]->attr.op == '[')
         {
            if (!currentNode->child[1] && currentNode->child[0]->varKind == Global)
            {
               if (currentNode->attr.op)
               {
                  case INC:
                     emitRM((char *)"LDC", AC, int(currentNode->child[0]->offset), 6, (char *)"Load integer constant");
                     emitRM((char *)"LDA", 5, currentNode->child[0]->offset, 0, (char *)"Load address of base of array", currentNode->child[0]->attr.name);
               }
            }
         }
         if (currentNode->attr.op == '=')
         {
            if (currentNode->isArray)
            {
               if (currentNode->child[1])
               {
                  emitStrLit(currentNode->child[1]->offset, (char *)currentNode->child[1]->attr.string);
                  emitRM((char *)"LDA", AC, int(currentNode->child[1]->offset), 0, (char *)"Load address of array");
               }

               if (currentNode->varKind == Parameter)
               {
                  emitRM((char *)"LD", AC1, int(currentNode->child[0]->offset), 1, (char *)"address of lhs");
                  emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                  emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");
                  emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");
                  emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
               }

               else if (currentNode->varKind != Parameter)
               {
                  emitRM((char *)"LDA", AC1, int(currentNode->child[0]->offset), 1, (char *)"address of lhs");
                  emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                  emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");
                  emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");
                  emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
               }

               else
               {
                  emitRM((char *)"LDC", AC, currentNode->child[1]->attr.value, 6, (char *)"Load integer constant");
                  emitRM((char *)"ST", AC, currentNode->child[0]->offset, FP, (char *)"Store variable", currentNode->child[0]->attr.name);                  
               }
            }

            else
            {
               if (currentNode->child[1])
               {
                  emitRM((char *)"LDC", AC, currentNode->child[1]->attr.value, 6, (char *)"Load integer constant");
               }

               switch (currentNode->attr.op)
               {
                  case ADDASS:
                       emitRM((char*)"LD", AC1, int(currentNode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"ADD", 3, 4, 3, (char *)"op +=");
                       break;

                  case DEC:
                       emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"LDA", AC, -1, 3, (char *)"decrement value of", currentNode->child[0]->attr.name);
                       break;

                  case DIVASS:
                       emitRM((char*)"LD", AC1, int(currentNode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"DIV", 3, 4, 3, (char *)"op /=");
                       break;   

                  case MULASS:
                       emitRM((char*)"LD", AC1, int(currentNode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"MUL", 3, 4, 3, (char *)"op *=");
                       break;

                  case SUBASS:
                       emitRM((char*)"LD", AC1, int(currentNode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"SUB", 3, 4, 3, (char *)"op -=");
                       break;

                  case INC:
                       emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"LDA", AC, 1, 3, (char *)"increment value of", currentNode->child[0]->attr.name);
                       break;
               }
               emitRM((char *)"ST", AC, currentNode->child[0]->offset, FP, (char *)"Store variable", currentNode->child[0]->attr.name);
            }
         }
         break;
      case ExpKind::CallK:
         emitComment((char *)"CALL");
         break;
      case ExpKind::ConstantK:
         emitComment((char *)"CONSTANT");
         switch(currentNode->type)
         {
            case ExpType::Integer:
               emitRM((char *)"LDC", AC, currentNode->attr.value, 6, (char *)"Loading integer const");
               break;
            case ExpType::Boolean:
               emitRM((char *)"LDC", AC, currentNode->attr.value, 6, (char *)"Loading boolean const");
               break;
            case ExpType::Char:
                // if it's a string
                if (currentNode->isArray)
                {
                  emitStrLit(currentNode->offset, currentNode->attr.string);
                  emitRM((char *)"LDA", AC, int(currentNode->offset), 0, (char *)"Load address of string");
                }
                else
                {
                  emitRM((char *)"LDC", AC, currentNode->attr.cvalue, 6, (char *)"Load char constant");
                }
                break;

            case ExpType::Void:
               // Do Nothing
               break;
         }

         break;
      case ExpKind::IdK:
         emitComment((char *)"ID");
         emitRM((char *)"LD", AC, int(currentNode->offset), 1, (char *)"Load variable", currentNode->attr.name);
         break;
      case ExpKind::OpK:
         // process the lhs of the operation
         codegenExpression(currentNode->child[0]);
         if (currentNode->child[1])
         {
            emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
            toffset--;
            emitComment((char *)"TOFF dec:", toffset);
            codegenExpression(currentNode->child[1]);
            toffset++;
            emitComment((char *)"TOFF inc:", toffset);
            emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
         }
         // more code goes here
         switch (currentNode->attr.op)
         {
            case '+':
               emitRO((char *)"ADD", AC, AC1, AC, (char *)"Op +");
               // break out the case '+' statment
               break;
         }
         // OpK switch statement break
         break;
      // currentNode->kind.exp switch statement break
      break;
   }
}

void codegenDecl(TreeNode *currentNode)
{
   commentLineNum(currentNode);
   switch(currentNode->kind.decl)
   {
      case DeclKind::VarK:
         // You have a lot to do here!!!!
         if(currentNode->isArray)
         {
            switch (currentNode->varKind)
            {
               case VarKind::Local:
                  emitRM((char *)"LDC", 3, (currentNode->size-1), 6, 
                         (char *)"load size of array", currentNode->attr.name);
                  emitRM((char *)"ST", AC, currentNode->offset+1, offsetRegister(currentNode->varKind),
                         (char *)"save size of array", currentNode->attr.name);
                  break;
               case VarKind::LocalStatic:
               case VarKind::Parameter:
               case VarKind::Global:
                  // Do Nothing Here
               case VarKind::None:
                  // Error condition
               default:
                  break;
            }

            if (currentNode->child[0])
            {
               codegenExpression(currentNode->child[0]);
               emitRM((char *)"LDA", AC1, currentNode->offset, offsetRegister(currentNode->varKind),(char *)"address of lhs");
               emitRM((char *)"LD", AC2, 1, AC, (char *)"size of rhs");
               emitRM((char *)"LD", AC3, 1, AC1, (char *)"size of lhs");
               emitRO((char *)"SWP", AC2, AC3, 6, (char *)"pick smallest size");
               emitRO((char *)"MOV", AC1, AC, AC2, (char *)"array op =");
            }

            else
            {
               // !currentNode->isArray
               // SCALAR VALUE initialization
               if (currentNode->child[0])
               {
                  switch(currentNode->varKind)
                  {
                     case VarKind::Local:
                     // compute rhs -> AC
                     codegenExpression(currentNode->child[0]);
                     // save it
                     emitRM((char *)"ST", AC, currentNode->offset, FP, (char *)"Store variable", currentNode->attr.name);
                        break;
                     case VarKind::LocalStatic:
                        break;
                     case VarKind::Parameter:
                        break;
                     case VarKind::Global:
                        // Do Nothing Here
                        break;
                     case VarKind::None:
                        // Error condition
                        break;
                  }
               }
            }
         }
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

void commentLineNum(TreeNode *currentNode)
{
   char buf[16];

   if (linenumFlag)
   {
      sprintf(buf, "%d", currentNode->lineno);
      emitComment((char *)"Line:", buf);
   }
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

   currentNode->offset = emitSkip(0); // offset holds the instruction address

   // Store return address
   emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");

   // Generate code for the statements..
   codegenFun(currentNode->child[1]);
   
   //In case there was no return statement
   // set return register to 0 and return
   emitComment((char *)"Add standard closing in case there is no return statement");
   emitRM((char *)"LDC", RT, 0, 6, (char *)"Set return value to 0");
   emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
   emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
   emitGoto(0, AC, (char *)"Return");

   emitComment((char *)"END FUNCTION", currentNode->attr.name);
}

// nice comments describing what is compiled
void codegenHeader(char *srcFile)
{
   emitComment((char *)"bC compiler version bC-Su23");
   emitComment((char *)"File compiled: ", srcFile);
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

// generate init code
void codegenInit(int initJump, int globalOffset)
{
   backPatchAJumpToHere(initJump, (char *)"Jump to init [backpatch]");
   emitComment((char *)"INIT");
   emitRM((char *)"LDA", FP, globalOffset, GP, (char *)"set first fram at the end of globals");
   emitRM((char *)"ST", FP, 0, FP, (char *)"store old fp (point to self)");

   initGlobalArraySizes(); // needs defined

   emitRM((char *)"LDA", AC, 1, PC, (char *)"Return address in ac");

   TreeNode *funcNode;

   funcNode = (TreeNode *)(globals->lookup((char *)"main"));
   if(funcNode)
   {
      emitGotoAbs(funcNode->offset, (char *)"Jump to main");
   }
   else
   {
      printf((char *)"ERROR(LINKER): Procedure main is not defined.\n");
      numErrors++;
   }
   emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
   emitComment((char *)"END INIT");
}

void initGlobalArraySizes()
{
   emitComment((char *)"INIT GLOBAL AND STATICS");
   globals->applyToAllGlobal(initAGlobalSymbol);
   emitComment((char *)"END INIT GLOBAL AND STATICS");
}

void initAGlobalSymbol(std::string sym, void *ptr)
{
   TreeNode *currentNode;
   // printf("Symbol: %s\n", sym.c_str()); // dump the symbol table
   currentNode = (TreeNode *)ptr;
   // printf("lineno: %d\n", currentNode->lineno); // dump the symbol table
   if (currentNode->lineno != -1)
   {
      if (currentNode->isArray)
      {
         emitRM((char *)"LDC", AC, currentNode->size - 1, 6, (char *)"load size of array", currentNode->attr.name);
         emitRM((char *)"ST", AC, currentNode->offset + 1, GP, (char *)"save size of array", currentNode->attr.name);
      }
      if (currentNode->kind.decl == VarK &&
          (currentNode->varKind == Global || currentNode->varKind == LocalStatic))
      {
         if (currentNode->child[0])
         {
            // compute rhs -> AC;
            codegenExpression(currentNode->child[0]);
            // save it
            emitRM((char *)"ST", AC, currentNode->offset, GP,
                   (char *)"Store variable", currentNode->attr.name);
         }
      }
   }
}


// helper function for IdK, AssignK, & VarK
int offsetRegister(VarKind v)
{
   switch (v)
   {
      case Local:
         return FP;
      case Parameter:
         return FP;
      case Global:
         return GP;
      case LocalStatic:
         return GP;
      default:
         printf((char *)"ERROR(codegen):looking up offset register for a variable of type %d\n", v);
         return 666;
   }
}

