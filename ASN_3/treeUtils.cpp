#include "treeUtils.h"

#include "treeNodes.h"
#include "scanType.h"
#include <string.h>
#include <stdlib.h>

// lots of these save the TokenData block so line number and yytext are saved
TreeNode *cloneNode(TreeNode *currnode)
{

}

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token=NULL,
                      TreeNode *c0=NULL,
                      TreeNode *c1=NULL,
                      TreeNode *c2=NULL)
{
   TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
   newNode->nodekind = NodeKind::DeclK;
   newNode->kind.stmt = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}  // save TokenData block!!

TreeNode *newStmtNode(StmtKind kind, TokenData *token, TreeNode *c0=NULL, 
   TreeNode *c1=NULL, TreeNode *c2=NULL)
{
   TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
   newNode->nodekind = NodeKind::StmtK;
   newNode->kind.stmt = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0=NULL,
                     TreeNode *c1=NULL,
                     TreeNode *c2=NULL)
{

}

char *tokenToStr(int type)
{

}

char *expTypeToStr(ExpType type, bool isArray=false, bool isStatic=false)
{

}

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
   fprintf(out, "Hi I'm a node. I should say something about myself");
}

void printTreeRecursive(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation,
int depth, int siblingCount = 1)
{
   //pre-order depth first search start at the first node and print it out
   if(syntaxTree == NULL)
   {
      return;
   }
   
   // Draw enough . . . for this node
   printTreeNode(out, syntaxTree, showExpType, showAllocation);
   fprintf(out, "\n");
   /*for loop here for the depth 0 is the root node*/
   for (int q = 0; q < MAXCHILDREN; q++)
   {
      // draw .  .  . for depth
      if(syntaxTree->child[q] != NULL)
      {
         // two spaces at the end
         fprintf(out, "Child: %d  ",q);
         printTreeRecurive(out, syntaxTree->child[q], showExpType, showAllocation, depth +  1);
      }
   }

   TreeNode *sibling = syntaxTree->sibling;
   if(sibling)
   {
      // show . . depth
      // again two spaces at the end
      fprintf(out, "Sibling: %d  ", siblingCount);
      printTreeRecursive(out, sibling, showExpType, showAllocation, depth, siblingCount + 1);
   }

}

void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
   if(syntaxTree == NULL)
   {
      fprintf(out, "NULL\n");
      return;
   }
   printTreeRecusive(out, sytnaxTree, showExpType, showAllocaion, 0);

   TreeNode *sibling = syntaxTree->sibling;
}