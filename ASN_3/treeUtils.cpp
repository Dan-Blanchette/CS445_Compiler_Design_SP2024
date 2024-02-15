#include "treeUtils.h"
#include "treeNodes.h"
#include "scanType.h"
#include <stdlib.h>

// lots of these save the Token_Data block so line number and yytext are saved
TreeNode *cloneNode(TreeNode *currnode)
{
   // create a new tree node in memory
   TreeNode *copyNode = new TreeNode;
   // copy the node data from the current node to the node copy variable
   copyNode = currnode;
   // return the copy of the node
   return copyNode;
}

TreeNode *newDeclNode(DeclKind kind,ExpType type,Token_Data *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = new TreeNode;
   newNode->nodekind = NodeKind::DeclK;
   newNode->kind.decl = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}  // save Token_Data block!!

TreeNode *newStmtNode(StmtKind kind, Token_Data *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = new TreeNode;
   newNode->nodekind = NodeKind::StmtK;
   newNode->kind.stmt = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}

TreeNode *newExpNode(ExpKind kind, Token_Data *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   // create a new struct node 
   TreeNode *newNode = new TreeNode;
   newNode->nodekind = NodeKind::ExpK;
   newNode->kind.exp = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;

   return newNode;
}

// confused about this implementation as well.
// how to I convert the token type to string?
// char *tokenToStr(int type)
// {
//    // place holder = return 0
//    return 0;
// }

// Need help figuring this part out
// The first parameter is an exp_type(void, integer, bool, char, or undefinedType) switch statement?
// if switch what should the default case be?

// The second parameter is referrring to the boolean value flag isArray (part of the TreeNode struct)
// and the last is another boolean value flag that checks for a static value (part of the TreeNode struct)

char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
   char *exp_type_name;
   // how do I convert the listed exp types to become a string value?
   // how does this tie into the yacc file and it's functionality?
   switch(type)
   {
      case Void:
         exp_type_name = (char*)"void type";
         break;

      case Integer:
         exp_type_name = (char*)"integer type";
         break;

      case Boolean:
         exp_type_name = (char*)"boolean type";
         break;

      case Char:
         exp_type_name = (char *)"char type";
         break;

      case UndefinedType:
         exp_type_name = (char *)"undefined type";
         break;

      default:
         break;
   }

}

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
   // create case statments to print out information
   // for each type of node kind
   switch(syntaxTree->nodekind)
   {
      //Declaration Kind printing
      case NodeKind::DeclK:
         switch (syntaxTree->kind.decl)
         {
            case DeclKind::VarK:
               printf("Var: %s ", syntanxTree->attr.name);
               break;
            case DeclKind::FuncK:
               printf("Func: %s ", syntaxTree->attr.name);
               break;
            case DeclKind::ParamK:
               printf("Param: %s ", syntaxTree->attr.name);
               break;
            default:
               break;
         }

      // Statement Kind printing
      case NodeKind::StmtK:
         switch (syntaxTree->kind.stmt)
         {
            case StmtKind::IfK:
               fprintf(out, "If");
               break;
            
            case StmtKind::WhileK:
               fprintf(out, "While");
               break;

            case StmtKind::ForK:
               fprintf(out, "For");
               break;

            case StmtKind::CompoundK:
               fprintf(out, "Compound");
               break;

            case StmtKind::ReturnK:
               fprintf(out, "Return");
               break;

            case StmtKind::BreakK:
               fprintf(out, "Break");
               break;

            case StmtKind::RangeK:
               fprintf(out, "Range");
               break;

            default:
               fprintf(out, "Statment node kind not recognized: %d", syntaxTree->kind.stmt);
               break;
         }
      // ExpKind printing
      case NodeKind::ExpK:
         switch (syntaxTree->kind.exp)
         {
            case ExpKind::AssignK:
               break;

            case ExpKind::CallK:
               break;

            case ExpKind::ConstantK:
               break;

            case ExpKind::IdK:
               break;

            case ExpKind::OpK:
              break;
              
            default:
              break;
         }
   }
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