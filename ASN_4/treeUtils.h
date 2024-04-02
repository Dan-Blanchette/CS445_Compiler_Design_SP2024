#ifndef _UTIL_H_
#define _UTIL_H_
#include "treeNodes.h"
#include "scanType.h"
#include "semantics.h"
#include <string.h>
#include <iostream>

// lots of these save the Token_Data block so line number and yytext are saved
TreeNode *cloneNode(TreeNode *currnode);
TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      Token_Data *token=NULL,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL);  // save Token_Data block!!
TreeNode *newStmtNode(StmtKind kind,
                      Token_Data *token,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL);
TreeNode *newExpNode(ExpKind kind,
                     Token_Data *token,
                     TreeNode *c0=NULL,
                     TreeNode *c1=NULL,
                     TreeNode *c2=NULL);
char *tokenToStr(int type);
char *varkToStr(int varKind);
char *expTypeToStr(ExpType type, bool isArray=false, bool isStatic=false);

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation);
void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation);
void showDepth(FILE *out, int depth);

#endif
