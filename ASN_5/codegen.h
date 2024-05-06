#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeNodes.h"
#include "treeUtils.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "parser.l"
#include "parser.y"

void codegen(FILE *codeIn,          // where the code should be written
             char *srcFile,         // name of file compiled
             TreeNode *syntaxTree,  // tree to process
	          SymbolTable *globalsIn,     // globals so function info can be found
	          int globalOffset,      // size of the global frame
             bool linenumFlagIn);   // comment with line numbers

// Node Type Switch Case Functions
void codegenStatment(TreeNode *currentNode);
void codegenExpression(TreeNode *currentNode);
void codegenDecl(TreeNode *currentNode);

void commentLineNum(TreeNode *currnode);

void codegenLibraryFun(TreeNode *currnode);
void codegenFun(TreeNode *currnode);

// nice comments describing what is compiled
void codegenHeader(char *srcFile); 
// general code generation including I/O library
void codegenGeneral(TreeNode *syntaxTree); 
// generation of initialization for run
void codegenInit(int initJump, int globalOffset); 
void initGlobalArraySizes();
void initAGlobalSymbol(std::string sym, void *ptr);
int offsetRegister(VarKind v);

#endif
