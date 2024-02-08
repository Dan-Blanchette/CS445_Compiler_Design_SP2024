#include "treeUtils.h"
#include "treeNodes.h"
#include "scanType.h"
#include <stdlib.h>

// lots of these save the Token_Data block so line number and yytext are saved
// TreeNode *cloneNode(TreeNode *currnode)
// {

// }

TreeNode *newDeclNode(DeclKind kind,ExpType type,Token_Data *token,
                  TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
   newNode->nodekind = NodeKind::DeclK;
   newNode->kind.decl = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}  // save Token_Data block!!

TreeNode *newStmtNode(StmtKind kind, Token_Data *token, TreeNode *c0, 
                  TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
   newNode->nodekind = NodeKind::StmtK;
   newNode->kind.stmt = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}

TreeNode *newExpNode(ExpKind kind, Token_Data *token,
                  TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
   newNode->nodekind = NodeKind::ExpK;
   newNode->kind.exp = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}

// char *tokenToStr(int type)
// {

// }

// char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
// {
   
// }

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
   /*for loop to check for max children. If the depth = 0, then it is the root node*/
   for (int q = 0; q < MAXCHILDREN; q++)
   {
      // draw .  .  . for depth
      if(syntaxTree->child[q] != NULL)
      {
         // two spaces at the end
         fprintf(out, "Child: %d  ", q);
         printTreeRecursive(out, syntaxTree->child[q], showExpType, showAllocation, depth +  1);
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
   printTreeRecursive(out, syntaxTree, showExpType, showAllocation, 0);

   TreeNode *sibling = syntaxTree->sibling;
}