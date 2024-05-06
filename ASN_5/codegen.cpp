#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeNodes.h"
#include "treeUtils.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "parser.tab.h"

// Globals
extern int numErrors;
int toffset;   // next available temporary space

FILE *code;                     // shared global code

static bool linenumFlag;        // mark with line numbers
static int breakloc;            // which while to break to
static SymbolTable *globals;    // the global symbol table

// These offsets that never change
#define OFPOFF  0
#define RETURNOFFSET   -1



//prototypes
void codegenHeader(char *srcFile);
void codegenStatement(TreeNode *currnode);
void codegenFun(TreeNode *currnode);
void codegenGeneral(TreeNode *currnode);
void commentLineNum(TreeNode *currnode);
void codegenDecl(TreeNode *currnode);
void codegenLibraryFun(TreeNode *currnode);
void initAGlobalSymbol(std::string sym, void *ptr);
void initGlobalArraySizes();
void codegenInit(int initJump, int globalOffset);
int offsetRegister(VarKind v);

void codegenExpression(TreeNode *currnode);


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

initJump = emitSkip(1);                  // save a place for the jump to init
codegenHeader(srcFile);                  // nice comments describing what is compiled
codegenGeneral(syntaxTree);              // general code generation including I/O library
codegenInit(initJump, globalOffset);     // generation of initialization for run
}


// Generate a header for our code
void codegenHeader(char *srcFile)
{
    emitComment((char *)"bC compiler version bC-Su23");
    emitComment((char *)"File compiled: ", srcFile);
}

///    AssignK, CallK, ConstantK, IdK, OpK
void codegenExpression(TreeNode *currnode) {
   switch(currnode->kind.exp){
       case ConstantK:
          switch(currnode->type){
             
             case Void:
             
                break;
             case Integer:
                emitRM((char*)"LDC", AC, currnode->attr.value, 6, (char*)"Load integer constant");
                break;
             case Boolean:
                emitRM((char*)"LDC", AC, currnode->attr.value, 6, (char*)"Load Boolean constant");
                break;
             case Char:
                if (currnode->isArray){
                    emitStrLit(currnode->offset, currnode->attr.string);
                    emitRM((char*)"LDA", AC, int(currnode->offset), 0, (char*)"Load address of char array"); 
                }else {
                    emitRM((char*)"LDC", AC, currnode->attr.cvalue, 6, (char*)"Load char constant");
                }
                break;
          }
          break;
       case AssignK:
          if (currnode->child[0]->attr.op == '[') {
               if ( !currnode->child[1] && currnode->child[0]->varKind == Global ){
                      switch (currnode->attr.op){
                          case INC:
                              emitRM((char*)"LDC", AC, int(currnode->child[0]->offset), 6, (char*)"Load integer constant");
                              emitRM((char*)"LDA", 5, currnode->child[0]->offset, 0, (char*)"Load address of base of array", currnode->child[0]->attr.name);
                       }
              }  

          if (currnode->attr.op == '=' ){

         /*    if (currnode->varKind == Global){
                 emitRM((char*)"LDC", AC, currnode->child[1]->attr.value, 6, (char*)"Load Boolean constant");
                 emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name);
             }
             if (currnode->varKind == Local){
                 emitRM((char*)"LDC", AC, currnode->child[1]->attr.value, 6, (char*)"Load integer constant");
                 emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name);
             }    */ 
             if (currnode->isArray) {
                if (currnode->child[1]){
                     emitStrLit(currnode->child[1]->offset, (char *)currnode->child[1]->attr.string );
                     emitRM((char*)"LDA", AC, int(currnode->child[1]->offset), 0, (char*)"Load address of char array");
                }
              
                 if (currnode->varKind == Parameter){
                     emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"address of lhs");
                     emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");
                     emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
                     emitRO((char*)"SWP", 5,6,6,(char*)"pick smallest size");
                     emitRO((char*)"MOV",4,3,5,(char*)"array op =");

                 }
                
                 else if (currnode->varKind != Parameter){
                     emitRM((char*)"LDA", AC1, int(currnode->child[0]->offset), 1, (char*)"address of lhs");
                     emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");              
                     emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
                     emitRO((char*)"SWP", 5,6,6,(char*)"pick smallest size");
                     emitRO((char*)"MOV",4,3,5,(char*)"array op =");
                 }


              }
              else {
         //         if (currnode->varKind == Parameter){
                      emitRM((char*)"LDC", AC, currnode->child[1]->attr.value, 6, (char*)"Load integer constant");
                      emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name);
        //          }
             /*     else if(currnode->varKind != Parameter){
                      emitRM((char*)"LDC", AC, currnode->child[1]->attr.value, 6, (char*)"Load Boolean constant");
                      emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name);
                  }   */
              }
          }

          else {

              if (currnode->child[1]) {
                  emitRM((char*)"LDC", AC, currnode->child[1]->attr.value, 6, (char*)"Load integer constant");
              }

                 switch (currnode->attr.op) {
                    case ADDASS:
                       emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"ADD", 3, 4, 3, (char *)"op +=");
                       break;
                    case DEC:
                       emitRM((char*)"LD", AC, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRM((char*)"LDA", AC, -1, 3, (char*)"decrement value of", currnode->child[0]->attr.name);                     
                       break;
                    case DIVASS:
                       emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"DIV", 3, 4, 3, (char *)"op /=");
                       break;
                    case MULASS:
                       emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"MUL", 3, 4, 3, (char *)"op *=");
                       break;
                    case SUBASS:
                       emitRM((char*)"LD", AC1, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRO((char *)"SUB", 3, 4, 3, (char *)"op -=");
                       break;
                    case INC:
                       emitRM((char*)"LD", AC, int(currnode->child[0]->offset), 1, (char*)"load lhs variable", currnode->child[0]->attr.name);
                       emitRM((char*)"LDA", AC, 1, 3, (char*)"increment value of", currnode->child[0]->attr.name);
                       break;
                 }
                   emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name); 

              }
          }


                                 
       	  break;
       case CallK:

          break;
       case IdK:
          if(currnode->isArray){
          //    emitRM((char*)"LD", AC, int(currnode->offset), 1, (char*)"Load variable x");
          }
          else {
              emitRM((char*)"LD", AC, int(currnode->offset), 1, (char*)"Load variable", currnode->attr.name);
          } 
          break;
       case OpK:
        // process lhs
        codegenExpression(currnode->child[0]);

        // process rhs if binary operator
        if (currnode->child[1]) {
            emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
            toffset--;  emitComment((char *)"TOFF dec:", toffset);
            codegenExpression(currnode->child[1]);
            toffset++;  emitComment((char *)"TOFF inc:", toffset);
            emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
        }

        // do operator
        switch (currnode->attr.op) {
           case '+':
              emitRO((char *)"ADD", AC, AC1, AC, (char *)"Op +");
              break;}
           break;


          break;

   }



}


// given the syntax tree for declarations generate the code
void codegenDecl(TreeNode *currnode)
{
    commentLineNum(currnode);
    switch(currnode->kind.decl) {
        case VarK:
            
             if (currnode->isArray){ 

               //  if (currnode->child[0]){
                     if (currnode->varKind == Local) {
                          emitRM((char *)"LDC", 3, currnode->size-1, 6, (char *)"load size of array", currnode->attr.name);
                          emitRM((char *)"ST", AC, -2, FP, (char *)"save size of array", currnode->attr.name);
                      }
                   if (currnode->child[1]){

                       codegenExpression(currnode->child[0]);
                       emitRM((char*)"LDA", AC1, int(currnode->offset), 1, (char*)"address of lhs");
                       emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");		
                       emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
                       emitRO((char*)"SWP", 5,6,6,(char*)"pick smallest size");
                       emitRO((char*)"MOV",4,3,5,(char*)"array op =");
                      
                 } 
              /*   else if (!currnode->child[0]) {
                      emitRM((char *)"LDC", 3, currnode->size-1, 6, (char *)"load size of array", currnode->attr.name);
                      emitRM((char *)"ST", AC, -2, FP, (char *)"save size of array", currnode->attr.name);
                 }  */
             }
             else {
                 if (currnode->child[1]) {      
                      if (currnode->varKind == Local) {
                          codegenExpression(currnode->child[0]);
                          emitRM((char *)"ST", AC, currnode->offset, FP, (char *)"Store variable", currnode->attr.name);

//                          emitRM((char *)"LDC", 3, currnode->size-1, 6, (char *)"load size of array", currnode->attr.name);
  //  if part of the arr                       emitRM((char *)"ST", AC, -2, FP, (char *)"save size of array", currnode->attr.name);
                      }
                 }
             }  

            break;
        case FuncK:

            if (currnode->lineno == -1) { // These are the library functions we just added
                codegenLibraryFun(currnode);
            }
            else {
                codegenFun(currnode);
            }
            break;
        case ParamK:

        // IMPORTANT: no instructions need to be allocated for parameters here

            break;
    }
}


void codegenStatement(TreeNode *currnode)
{
    // local state to remember stuff
    int skiploc=0, skiploc2=0, currloc=0; // some temporary instuction addresses
    TreeNode *loopindex=NULL; // a pointer to the index variable declaration node
    commentLineNum(currnode);
    switch (currnode->kind.stmt) {
    /////////////////Other cases        BreakK     AssignK,  CallK,  ForK,  CompundK,  FuncK



    case WhileK:
            emitComment((char *)"WHILE");
            currloc = emitSkip(0); // return to here to do the test
            codegenExpression(currnode->child[0]); // test expression
            emitRM((char *)"JNZ", AC, 1, PC, (char *)"Jump to while part");
            emitComment((char *)"DO");
            skiploc = breakloc; // save the old break statement return point
            breakloc = emitSkip(1); // addr of instr that jumps to end of loop
            // this is also the backpatch point
            codegenGeneral(currnode->child[1]); // do body of loop
            emitGotoAbs(currloc, (char *)"go to beginning of loop");
            backPatchAJumpToHere(breakloc, (char *)"Jump past loop [backpatch]");
            // backpatch jump to end of loop
            breakloc = skiploc; // restore for break statement
            emitComment((char *)"END WHILE");
        break;

        OpK:
            if (currnode->child[1]) {
                emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side");
                toffset--; emitComment((char *)"TOFF dec:", toffset);
                codegenExpression(currnode->child[1]);
                toffset++; emitComment((char *)"TOFF inc:", toffset);
                emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
            }
            // More code here



    case CompoundK:
        { 
            int savedToffset;
            savedToffset = toffset;
            toffset = currnode->size; // recover the end of activation record
            emitComment((char *)"COMPOUND");
            emitComment((char *)"TOFF set:", toffset);
            codegenGeneral(currnode->child[0]); // process inits
            emitComment((char *)"Compound Body");
            codegenGeneral(currnode->child[1]); // process body
            toffset = savedToffset;
            emitComment((char *)"TOFF set:", toffset);
            emitComment((char *)"END COMPOUND");
        }
        break;
        
    default:
        break;
    }
}


// process functions
void codegenFun(TreeNode *currnode)
{
    emitComment((char *)"");
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
    emitComment((char *)"FUNCTION", currnode->attr.name);
    toffset = currnode->size; // recover the end of activation record
    emitComment((char *)"TOFF set:", toffset);

    // IMPORTANT:For function nodes the offset is defined to be the position of the
    // function in the code space! This is accessible via the symbol table.
    // remember where this function is:
    currnode->offset = emitSkip(0); // offset holds the instruction address!!
    // Store return address
    emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");

    // Generate code for the statements...
    codegenGeneral(currnode->child[1]);
    // In case there was no return statement
    // set return register to 0 and return
    emitComment((char *)"Add standard closing in case there is no return statement");
    emitRM((char *)"LDC", RT, 0, 6, (char *)"Set return value to 0");
    emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
    emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
    emitGoto(0, AC, (char *)"Return");
    emitComment((char *)"END FUNCTION", currnode->attr.name);
}

void codegenGeneral(TreeNode *currnode)
{ 
    while (currnode) {
        switch (currnode->nodekind) {
            case StmtK:
                codegenStatement(currnode);
                break;
            case ExpK:
                emitComment((char *)"EXPRESSION");
                codegenExpression(currnode);
                break;
            case DeclK:
                codegenDecl(currnode);
                break;
        }
        currnode = currnode->sibling;
    }
}

void commentLineNum(TreeNode *currnode)
{
    char buf[16];
    if (linenumFlag) {
        sprintf(buf, "%d", currnode->lineno);
        emitComment((char *)"Line: ", buf);
    }
}


void codegenLibraryFun(TreeNode *currnode)
{ 

    emitComment((char *)"");
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
    emitComment((char *)"FUNCTION", currnode->attr.name);
    // remember where this function is
    currnode->offset = emitSkip(0);
    // Store return address
    emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");


    // Next slides here
    if (strcmp(currnode->attr.name, (char *)"input")==0) {
        emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputb")==0) {
        emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputc")==0) {
        emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    }
    else if (strcmp(currnode->attr.name, (char *)"input")==0) {
        emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputb")==0) {
        emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputc")==0) {
        emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    }
    else if (strcmp(currnode->attr.name, (char *)"output")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUT", AC, AC, AC, (char *)"Output integer");
    }
    else if (strcmp(currnode->attr.name, (char *)"outputb")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTB", AC, AC, AC, (char *)"Output bool");
    }else if (strcmp(currnode->attr.name, (char *)"outputc")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTC", AC, AC, AC, (char *)"Output char");
    }
    else if (strcmp(currnode->attr.name, (char *)"input")==0) {
        emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputb")==0) {
        emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputc")==0) {
        emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    }
    else if (strcmp(currnode->attr.name, (char *)"output")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUT", AC, AC, AC, (char *)"Output integer");
    }
    else if (strcmp(currnode->attr.name, (char *)"outputb")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTB", AC, AC, AC, (char *)"Output bool");
    }
    else if (strcmp(currnode->attr.name, (char *)"outputc")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTC", AC, AC, AC, (char *)"Output char");
    }
    else if (strcmp(currnode->attr.name, (char *)"outnl")==0) {
        emitRO((char *)"OUTNL", AC, AC, AC, (char *)"Output a newline");
    }
    else {
        emitComment((char *)"ERROR(LINKER): No support for special function");
        emitComment(currnode->attr.name);
    }


    emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
    emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
    emitGoto(0, AC, (char *)"Return");
    emitComment((char *)"END FUNCTION", currnode->attr.name);
}


void initAGlobalSymbol(std::string sym, void *ptr)
{ 
    TreeNode *currnode;
    // printf("Symbol: %s\n", sym.c_str()); // dump the symbol table
    currnode = (TreeNode *)ptr;
    // printf("lineno: %d\n", currnode->lineno); // dump the symbol table
    if (currnode->lineno != -1) {
        if (currnode->isArray) {
            emitRM((char *)"LDC", AC, currnode->size-1, 6, (char *)"load size of array", currnode->attr.name);
            emitRM((char *)"ST", AC, currnode->offset+1, GP, (char *)"save size of array", currnode->attr.name);
        }
        if (currnode->kind.decl==VarK && (currnode->varKind == Global || currnode->varKind == LocalStatic)) {
            if (currnode->child[0]) {
                // compute rhs -> AC;
                codegenExpression(currnode->child[0]);
                // save it
                emitRM((char *)"ST", AC, currnode->offset, GP, (char *)"Store variable", currnode->attr.name);
            }
        }
    }
}


void initGlobalArraySizes()
{
    emitComment((char *)"INIT GLOBALS AND STATICS");
    globals->applyToAllGlobal(initAGlobalSymbol);
    emitComment((char *)"END INIT GLOBALS AND STATICS");
}

// Generate init code ...
void codegenInit(int initJump, int globalOffset)
{ 
    backPatchAJumpToHere(initJump, (char *)"Jump to init [backpatch]");
    emitComment((char *)"INIT");
    //OLD pre 4.6 TM emitRM((char *)"LD", GP, 0, 0, (char *)"Set the global pointer");
    emitRM((char *)"LDA", FP, globalOffset, GP, (char *)"set first frame at end of globals");
    emitRM((char *)"ST", FP, 0, FP, (char *)"store old fp (point to self)");
    initGlobalArraySizes();
    emitRM((char *)"LDA", AC, 1, PC, (char *)"Return address in ac");
    { 
        // jump to main
        TreeNode *funcNode;
        funcNode = (TreeNode *)(globals->lookup((char *)"main"));
        if (funcNode) {
            emitGotoAbs(funcNode->offset, (char *)"Jump to main");
        }
        else {
            printf((char *)"ERROR(LINKER): Procedure main is not defined.\n");
            numErrors++;
        }
    }
    emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
    emitComment((char *)"END INIT");
}

int offsetRegister(VarKind v) {
    switch (v) {
    case Local:       return FP;
    case Parameter:   return FP;
    case Global:      return GP;
    case LocalStatic: return GP;
    default:
        printf((char *)"ERROR(codegen): looking up offset register for a variable of type %d\n", v);
        return 666;
    }
}




#endif