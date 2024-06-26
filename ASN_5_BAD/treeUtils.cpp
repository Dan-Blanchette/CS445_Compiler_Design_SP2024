#include "treeUtils.h"

// Assignment 4 in progress
/* Assignment 4 Completed and Passing All Test Cases*/

static int nodeIdNum = 0;

// lots of these save the Token_Data block so line number and yytext are saved
TreeNode *cloneNode(TreeNode *currnode)
{
   // create a new tree node in memory
   TreeNode *copyNode = new TreeNode;
   // copy the node data from the current node to the node copy variable
   // copyNode = currnode;
   // this is great if we want to copy just the
   // current node's data.

   // but if it's a parent node we need to also
   // copy all the struct data in treeNodes.h
   // so we need to use a loop to copy all the children and update their attributes
   // and siblings if there are any.
   int num = 0;
   // copy children and sibling data
   for (num; num < MAXCHILDREN; num++)
   {
      copyNode->child[num] = currnode->child[num];
   }

   // copy the siblings
   copyNode->sibling = currnode->sibling;
   copyNode->nodeNum = nodeIdNum++;

   // copy the node line number
   copyNode->lineno = currnode->lineno;

   // copy the node kind
   copyNode->nodekind = currnode->nodekind;

   // copy the node kind struct data
   copyNode->kind.decl = currnode->kind.decl;
   copyNode->kind.stmt = currnode->kind.stmt;
   copyNode->kind.exp = currnode->kind.exp;

   // copy the node ExpType type and boolean data
   copyNode->type = currnode->type;
   copyNode->isStatic = currnode->isStatic;
   copyNode->isArray = currnode->isArray;
   copyNode->isConst = currnode->isConst;
   copyNode->isUsed = currnode->isUsed;
   copyNode->isAssigned = currnode->isAssigned;

   // copy the node attributes struct
   copyNode->attr.op = currnode->attr.op;
   copyNode->attr.value = currnode->attr.value;
   copyNode->attr.cvalue = currnode->attr.cvalue;
   copyNode->attr.name = currnode->attr.name;
   copyNode->attr.string = currnode->attr.string;


   // copy varKind and extra inferred node data
   copyNode->varKind = currnode->varKind;
   copyNode->offset = currnode->offset;
   copyNode->size = currnode->size;

   // return the copy of the node
   return copyNode;
}
// NOTE : This will be the same for statement and exp functions
TreeNode *newDeclNode(DeclKind kind, ExpType type, Token_Data *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = new TreeNode; // allocate memory for new a new node

   newNode->size = 1;
   newNode->offset = 0;
   newNode->nodekind = NodeKind::DeclK;
   newNode->kind.decl = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;
   newNode->sibling = NULL;
   // Node Data
   newNode->type = type;
   newNode->nodeNum = nodeIdNum++;
   
   
   if (token != NULL)
   {
      newNode->lineno = token->linenum;
      // update the rest of the node data
      newNode->attr.op = token->tokenclass;
      newNode->attr.value = token->nvalue;
      newNode->attr.cvalue = token->cvalue;
      newNode->attr.name = token->svalue;
   }
   else
   {
      newNode->lineno = -1;
   }
   
   return newNode;
}

TreeNode *newStmtNode(StmtKind kind, Token_Data *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   TreeNode *newNode = new TreeNode; // allocate memory for new a new node
   newNode->size = 1;
   newNode->offset = 0;
   newNode->nodekind = NodeKind::StmtK;
   newNode->kind.stmt = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;
   newNode->sibling = NULL;

   // write to stmt node struct vars
   newNode->nodeNum = nodeIdNum++;
   newNode->lineno = token->linenum;
   
   // update the rest of the node data
   newNode->attr.value = token->nvalue;
   newNode->attr.op = token->tokenclass;
   newNode->attr.cvalue = token->cvalue;
   newNode->attr.name = token->svalue;
   newNode->attr.string = token->tokenstr;

   return newNode;
}

TreeNode *newExpNode(ExpKind kind, Token_Data *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
   // create a new struct node
   TreeNode *newNode = new TreeNode; // allocate memory for new a new node
   newNode->size = 1;
   newNode->offset = 0;   
   newNode->nodekind = NodeKind::ExpK;
   newNode->kind.exp = kind;
   newNode->child[0] = c0;
   newNode->child[1] = c1;
   newNode->child[2] = c2;
   newNode->sibling = NULL;
   // Update ExpNode struct vars
   newNode->nodeNum = nodeIdNum++;
   newNode->lineno = token->linenum;

   // update the rest of the node data
   newNode->attr.op = token->tokenclass;
   newNode->attr.value = token->nvalue;
   newNode->attr.cvalue = token->cvalue;
   newNode->attr.name = token->svalue;

   return newNode;
}

char varBuff[200];
char *varkToStr(VarKind varK)
{
   char *strToReturn;
   // debug
   // printf("Inside vark2Str\n");
   if (varK == VarKind::Global)
   {   
      strToReturn = (char *)"Global";
   }
   else if (varK == VarKind::LocalStatic)
   {
      strToReturn = (char *)"LocalStatic";
   }
   else if (varK == VarKind::Local)
   {
      strToReturn = (char *)"Local";
   }
   else if (varK == VarKind::Parameter)
   {
      strToReturn = (char *)"Parameter";
   }
   else
   {
      strToReturn = (char *)"None";
   }
         
   sprintf(varBuff, "%s", strToReturn);
   return varBuff;
}

// The first parameter is an exp_type(void, integer, bool, char, or undefinedType)
// The second parameter is referrring to the boolean value flag isArray (part of the TreeNode struct)
// and the last is another boolean value flag that checks for a static value (part of the TreeNode struct)
char expBuff[100];
char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
   char *exp_type_name;
   // how do I convert the listed exp types to become a string value?
   // how does this tie into the yacc file and it's functionality?
   if (isStatic)
   {
      if (isArray)
      {
         switch(type)
         {
            case ExpType::Boolean:
               return (char *)"static array of type bool";
               break;
            case ExpType::Char:
               return (char *)"static array of type char";
               break;
            case ExpType::Integer:
               return (char *)"static array of type int";
               break;
            case ExpType::UndefinedType:
                (char *)"static array of type UNDEFINED";
               break;
            case ExpType::Void:
               return (char *)"static array of type void";
               break;
         }         
      }
      switch(type)
      {
         case ExpType::Boolean:
            return (char *)"static type bool";
            break;
         case ExpType::Char:
            return (char *)"static type char";
            break;
         case ExpType::Integer:
            return (char *)"static type int";
            break;
         case ExpType::UndefinedType:
            return (char *)"static type UNDEFINED";
            break;
         case ExpType::Void:
            return (char *)"static type void";
            break;
      }
   }

   
   switch (type)
   {
   case ExpType::Boolean:
      exp_type_name = (char *)"type bool";
      break;

   case ExpType::Char:
      exp_type_name = (char *)"type char";
      break;

   case ExpType::Integer:
      exp_type_name = (char *)"type int";
      break;

   case ExpType::Void:
      exp_type_name = (char *)"type void";
      break;

   default:
      exp_type_name = (char *)"UNDEFINED";
      break;
   }
   
   sprintf(expBuff, "%s%s%s%s", (isStatic && isArray ? (char*)"static " : ""), 
            (isArray && isStatic ? (char *)"static " : ""), 
            (isArray ? (char *)"array of " : ""), 
             exp_type_name);

   return expBuff; 
}

void printTreeNode(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
   // create case statments to print out information
   // for each type of node kind

   // edit: changed from super nested case statements to an if else if else approach for the NodeKinds
   // then kept switch statements for subkind print statments
   if (syntaxTree->nodekind == NodeKind::DeclK)
   {
      switch (syntaxTree->kind.decl)
      {
      case DeclKind::VarK:
         fprintf(out, "Var: %s of %s", syntaxTree->attr.name, expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));
         // Assignment 4 additional Print Statement
         break;

      case DeclKind::FuncK:
         fprintf(out, "Func: %s", syntaxTree->attr.name);
         fprintf(out, " returns %s", expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));   
         // Assignment 4 additional Print Statement
         break;
      case DeclKind::ParamK:
         fprintf(out, "Parm: %s of %s", syntaxTree->attr.name, expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));
         // Assignment 4 additional Print Statement
         break;
      default:
         fprintf(out, "DeclK Node");
         break;
      }
   }
   // Statement Kind printing
   else if (syntaxTree->nodekind == NodeKind::StmtK)
   {  
      // Sub Kinds of Statements
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
            fprintf(out, "StmtK Node");
            break;
      }
      // End Stmnt Switch
   }
   // ExpKind printing
   else if (syntaxTree->nodekind == NodeKind::ExpK)
   {  
      // ExpK Switch Start
      switch (syntaxTree->kind.exp)
      {
         case ExpKind::AssignK:
            fprintf(out, "Assign: %s", tokenToStr(syntaxTree->attr.op));
            break;

         case ExpKind::CallK:
            fprintf(out, "Call: %s", syntaxTree->attr.name);
            break;

         case ExpKind::ConstantK:
            // bool variable to string
            char *boolVal;

            fprintf(out, "Const");
            // ExpTypes If Statment Start
            if(syntaxTree->type == ExpType::Boolean)
            {
               if (syntaxTree->attr.value == 0)
               {
                  boolVal = (char *)"false";
               }
               else
                  boolVal = (char *)"true";
               
               fprintf(out, " %s", boolVal);
            }
            else if (syntaxTree->type == ExpType::Char)
            {
               // it's a string
               if (syntaxTree->isArray)
               {
                  fprintf(out, " %s", syntaxTree->attr.string);
               }
               // it's a char
               else
                  fprintf(out, " '%c'",  syntaxTree->attr.cvalue);

            }
            else if (syntaxTree->type == ExpType::UndefinedType)
            {
               fprintf(out, "SYSTEM ERROR: parse tree contains invalid type for constant: %s\n", expTypeToStr(syntaxTree->type));
            }
            // it's an integer
            else 
            {
               fprintf(out, " %d", syntaxTree->attr.value);
            }
            break;
      

         case ExpKind::IdK:
            fprintf(out, "Id: %s", syntaxTree->attr.name);
            break;

         case ExpKind::OpK:
            fprintf(out, "Op: %s", syntaxTree->attr.name);
            break;

         default:
            fprintf(out, "ExpK Node", syntaxTree->kind.exp);
            break;
      }
      // ExpK Switch End
      if (showExpType)
      {
         fprintf(out, " of %s", expTypeToStr(syntaxTree->type, syntaxTree->isArray, syntaxTree->isStatic));
      }      
   }
   else
   {
      fprintf(out, "I'm a node, I should say something here...", syntaxTree->nodekind);
   }


   
   if (showAllocation && ( 
          ((syntaxTree->nodekind == DeclK)  && (syntaxTree->kind.decl == DeclKind::VarK)) 
        || ((syntaxTree->nodekind == DeclK) && (syntaxTree->kind.decl == DeclKind::FuncK))
        || ((syntaxTree->nodekind == DeclK) && (syntaxTree->kind.decl == DeclKind::ParamK))  
        || ((syntaxTree->nodekind == StmtK) && (syntaxTree->kind.stmt == StmtKind::CompoundK))
        || ((syntaxTree->nodekind == StmtK) && (syntaxTree->kind.stmt == StmtKind::ForK))
        || ((syntaxTree->nodekind == ExpK)  &&  (syntaxTree->kind.exp == ExpKind::IdK))
        || ((syntaxTree->nodekind == ExpK)  &&  (syntaxTree->kind.exp == ExpKind::ConstantK) && (syntaxTree->type == Char)
             && (syntaxTree->isArray))
      ))
   {
      // printf("Entered MemeAllloc\n");
      // updated to fprintf (might be the issue as it was not using the filestream object originally printf())
      fprintf(out, " [mem: %s loc: %d size: %d]", varkToStr(syntaxTree->varKind), syntaxTree->offset, syntaxTree->size);
   } 
   // printf("After MemAlloc Logic\n");
   fprintf(out, " [line: %d]", syntaxTree->lineno);
   return;
}

// helper function for printing .  .  .
void showDepth(FILE *out, int depth)
{
   
   for(int i = 0; i < depth; i++)
   {
      fprintf(out, ".   ");
   }
}


void printTreeRecursive(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation,
                           int depth, int siblingCount = 1)
{
   // pre-order depth first search start at the first node and print it out
   if (syntaxTree == NULL)
   {
      // fprintf(out, "NULL\n");
      return;
   }

   // Draw enough . . . for this node
   printTreeNode(out, syntaxTree, showExpType, showAllocation);
   fprintf(out, "\n");
   
   
   /*for loop to check for max children. If the depth = 0, then it is the root node*/
   for (int i = 0; i < MAXCHILDREN; i++)
   {
      // draw .  .  . for depth
      if (syntaxTree->child[i] != nullptr)
      {
         // two spaces at the end
         showDepth(out, depth);
         fprintf(out, "Child: %i  ", i);
         printTreeRecursive(out, syntaxTree->child[i], showExpType, showAllocation, (depth + 1));
      }
   }

   TreeNode *sibling = syntaxTree->sibling;
   if (sibling != NULL)
   {

      // show . . depth
      showDepth(out, (depth - 1));
      // again two spaces at the end
      fprintf(out, "Sibling: %d  ", siblingCount);
      printTreeRecursive(out, sibling, showExpType, showAllocation, depth, (siblingCount + 1));
   }
   // flush the output buffer maybe?
   // fflush(out);
}


void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
   if (syntaxTree == nullptr)
   {
      fprintf(out, "NULL\n");
      return;
   }
   printTreeRecursive(out, syntaxTree, showExpType, showAllocation, 1);
   return;
}