#include "semantics.h"
#include <string.h>
#include "parser.tab.h"


// GLOBAL SCOPE VARS

// memory offsets: ensure counts are updated until end of runtime
static int foffset;
static int goffset = 0;
static bool newScope = false;
static int varCounter = 0;

// Progress Apr 8th NOTE:
/* 
   I'm working on hunting down an incorrect size for the foffset
   program shows -1 as part of the file output diffs when it should be -3.
   There must be a place I'm missing adding -2 to the value but I'm not sure
   where.
*/

// not sure if this is needed yet
// static bool isNewScope = true;

TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax tree
                           bool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    )
{
   syntree = loadIOLib(syntree);

   // treeTraverse(syntree, symtabX); 

   return syntree;
}

// Generating 10 nodes as indicated by slide 4.
TreeNode *loadIOLib(TreeNode *syntree)
{
   // renamed node variables to reflect slide labels
   TreeNode *input, *inputB, *inputC;
   TreeNode *output, *outputB, *outputC;
   TreeNode *Param_output, *Param_output_b, *Param_output_c; 
   TreeNode *outnl;

   input = newDeclNode(DeclKind::FuncK, ExpType::Integer);
   input->lineno = -1; // all are -1
   input->attr.name = strdup("input");
   input->type = ExpType::Integer;

   inputB = newDeclNode(DeclKind::FuncK, ExpType::Boolean);
   inputB->lineno = -1; // all are -1
   inputB->attr.name = strdup("inputb");
   inputB->type = ExpType::Boolean;

   inputC = newDeclNode(DeclKind::FuncK, ExpType::Boolean);
   inputC->lineno = -1; // all are -1
   inputC->attr.name = strdup("inputc");
   inputC->type = ExpType::Char;

   Param_output = newDeclNode(DeclKind::ParamK, ExpType::Void);
   // Param_output->lineno = -1; // all are -1
   Param_output->attr.name = strdup("*dummy*");
   Param_output->type = ExpType::Integer;

   Param_output_b = newDeclNode(DeclKind::ParamK, ExpType::Void);
   // Param_output_b->lineno = -1; // all are -1
   Param_output_b->attr.name = strdup("*dummy*");
   Param_output_b->type = ExpType::Boolean;

   Param_output_c = newDeclNode(DeclKind::ParamK, ExpType::Void);
   // Param_output_c->lineno = -1; // all are -1
   Param_output_c->attr.name = strdup("*dummy*");
   Param_output_c->type = ExpType::Char;

   output = newDeclNode(DeclKind::FuncK, ExpType::Void);
   output->lineno = -1; // all are -1
   output->attr.name = strdup("output");
   output->type = ExpType::Void;
   output->child[0] = Param_output;

   outputB = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outputB->lineno = -1; // all are -1
   outputB->attr.name = strdup("outputb");
   outputB->type = ExpType::Void;
   // child node as seen in slides
   outputB->child[0] = Param_output_b;

   outputC = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outputC->lineno = -1; // all are -1
   outputC->attr.name = strdup("outputc");
   outputC->type = ExpType::Void;
   // child node as seen in slides
   outputC->child[0] = Param_output_c;

   outnl = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outnl->lineno = -1; // all are -1
   outnl->attr.name = strdup("outnl");
   outnl->type = ExpType::Void;
   outnl->child[0] = NULL;

   // input connected to output
   input->sibling = output;
   // output connect to inputb
   output->sibling = inputB;
   // inputb connected to outputgb
   inputB->sibling = outputB;
   // outputb connected to inputc
   outputB->sibling = inputC;
   // inputc connected to outputc
   inputC->sibling = outputC;
   // outputc connected to outnl
   outputC->sibling = outnl;
   // outnl connected to the sytnax tree nodes
   outnl->sibling = syntree;
   
   return input;
}


void treeTraverse(TreeNode *currentNode, SymbolTable *symtab)
{
   if (currentNode == NULL) return;

   switch(currentNode->nodekind)
   {
      case NodeKind::DeclK:
         treeTraverseDecl(currentNode, symtab);
         break;

      case NodeKind::StmtK:
         treeTraverseStmt(currentNode, symtab);
         break;
      
      case NodeKind::ExpK:
         treeTraverseExp(currentNode, symtab);
         break;
      
      default:
         printf("unknown nodekind\n");
         break;
   }
   if(currentNode->sibling != NULL) 
   {
      treeTraverse(currentNode->sibling, symtab);
   }

   return;
}


void treeTraverseDecl(TreeNode *currentNode, SymbolTable *symtab)
{
   // debug statement here
   TreeNode *c0,  *c1, *temp;
   c0 = currentNode->child[0];
   c1 = currentNode->child[1];

   switch(currentNode->kind.decl)
   {
      case FuncK:
         newScope = false;
         // debug goes here
         foffset = -2;
         insertCheck(currentNode, symtab);
         symtab->enter(currentNode->attr.name);
         // printf("foffset before %d\n", foffset);
         treeTraverse(c0, symtab);
         // printf("foffset after %d\n", foffset);
         currentNode->varKind = Global;
         currentNode->size = foffset;
         treeTraverse(c1, symtab);
         symtab->leave();
         newScope = true;
         break;

      case VarK:
         // printf("VarK");
         if(c0 != NULL)
         {
            currentNode->isAssigned = true;
            // currentNode->varKind = Local; // Local
            treeTraverse(c0, symtab);
         }
         // no break statement needed here
      case ParamK:
         // printf("In ParamK\n");
         // printf("%d %s %d\n", symtab->depth(), currentNode->attr.name, goffset);
         if (insertCheck(currentNode, symtab))
         {
            // printf("Check Succeeded\n");
            if (symtab->depth() == 1)
            {
               // printf("In ParamK depth check %d\n", goffset);
               currentNode->varKind = Global;
               currentNode->offset = goffset;
               goffset -= currentNode->size;
            }
            else if(currentNode->isStatic)
            {
               // printf("In ParamK is static %d\n", goffset);
               currentNode->varKind = LocalStatic;
               currentNode->offset = goffset;
               goffset -= currentNode->size;
               
               {
                  // char *newName;
                  // newName = new char[strlen(currentNode->attr.name) + 10];
                  // sprintf(newName, "%s-%d", currentNode->attr.name, ++varCounter);
                  symtab->insertGlobal(currentNode->attr.name, currentNode);

                  // delete [] newName;
               }
            }
            else
            {
               // printf("In ParamK else %d %d\n", foffset, currentNode->size);
               currentNode->varKind = Local;
               currentNode->offset = foffset;
               foffset -= currentNode->size;
               // printf("offset inside: %d\n", foffset);
            }
         }
         // else 
         //   printf("input check has failed\n");

         if(currentNode->kind.decl == ParamK)
         {
            currentNode->varKind = Parameter;
         }
         else if(currentNode->isArray)
         {
            currentNode->offset--;
         }
         break;

      default:
         printf("Unknown kind.decl");         
   }   
}

void treeTraverseStmt(TreeNode *currentNode, SymbolTable *symtab)
{
   TreeNode *c0,  *c1, *c2, *temp;
   c0 = currentNode->child[0];
   c1 = currentNode->child[1];
   c2 = currentNode->child[2];

   if (currentNode->kind.stmt != CompoundK) 
   {
      newScope = true;
   }
   switch(currentNode->kind.stmt)
   {
      case CompoundK:
         if (newScope)
         {
            // printf("Inside the if CompK\n");
            int newScopeOffset;
            symtab->enter((char *)"compound statement");
            newScopeOffset = foffset;
            // printf("NewScopeOffset %d\n", newScopeOffset);
            // printf("current size: %d\n", currentNode->size);
            // tree traverse your left child
            treeTraverse(c0, symtab);
            // deal with your self
            currentNode->size = foffset;
            // traverse your right child
            treeTraverse(c1, symtab);
            symtab->leave();
            foffset = newScopeOffset;
            //printf("foffset  at end of if statement %d\n", foffset); //- 11
         }
         else
         {
            // printf("Entered Else of CompoundK\n");
            newScope = true;
            // printf("CompK %s foffset before %d\n", currentNode->attr.name, foffset);
            treeTraverse(c0, symtab);
            // printf("CompK %s foffset after %d\n", currentNode->attr.name, foffset);
            currentNode->size = foffset;
            // printf("CompK %s foffset after %d\n", currentNode->attr.name, foffset);
            treeTraverse(c1, symtab);
         }
         break;

      case IfK:
         treeTraverse(c0, symtab);
         currentNode->size = foffset - 1;
         treeTraverse(c1, symtab);
         treeTraverse(c2, symtab);
         break;
      case ReturnK:
         treeTraverse(c0, symtab);
         break;
      case RangeK:
         treeTraverse(c0, symtab);
         treeTraverse(c1, symtab);
         treeTraverse(c2, symtab);
         break;
      case BreakK:         
         break;
      case WhileK:
         break;
      case ForK:
         int newScopeOffset2;
         symtab->enter((char *)"For");
         newScopeOffset2 = foffset;
         // tree traverse your left child
         treeTraverse(c0, symtab);
         foffset -= 2;
         // deal with your self
         currentNode->size = foffset;
         // traverse your right child
         treeTraverse(c1, symtab);
         // traverse child 2
         treeTraverse(c2, symtab);
         foffset = newScopeOffset2;
         symtab->leave();
         break;
      default:
         printf("unknown kind.stmt");
   }
}

void treeTraverseExp(TreeNode *currentNode, SymbolTable *symtab)
{
   TreeNode *c0,  *c1, *temp;
   c0 = currentNode->child[0];
   c1 = currentNode->child[1];

   switch(currentNode->kind.exp)
   {
      case OpK:
         treeTraverse(c0, symtab);
         treeTraverse(c1, symtab);
         if (currentNode->attr.op == int('<') || currentNode->attr.op == int('>'))
         {
            currentNode->type = ExpType::Boolean;
         }
         break;

      case AssignK:
         treeTraverse(c0, symtab);
         treeTraverse(c1, symtab);

         if(currentNode->attr.op == int('+') || currentNode->attr.op == int('[') || 
            currentNode->attr.op == int('='))
         {
            currentNode->type = c0->type;
         }
         else if(currentNode->attr.op == AND || currentNode->attr.op == OR || 
                  currentNode->attr.op == LEQ || currentNode->attr.op == GEQ ||
                  currentNode->attr.op == NOT || currentNode->attr.op == int('<') ||
                  currentNode->attr.op == int('>') || currentNode->attr.op == EQ ||
                  currentNode->attr.op == NEQ)
         {
            currentNode->type = ExpType::Boolean;
         }
         else
         {
            currentNode->type = ExpType::Integer;
         }         
         break;
      case CallK:
         treeTraverse(c0, symtab);
         treeTraverse(c1, symtab);
         if(temp = (TreeNode *)(symtab->lookup(currentNode->attr.name)))
         {
            temp->isUsed = true;
            currentNode->type = temp->type;
            // currentNode->isArray = temp->isArray;
            // currentNode->isStatic = temp->isStatic;
            // currentNode->varKind = temp->varKind;
            // currentNode->offset = temp->offset;
            // currentNode->size = temp->size;
         }
         else
         {
           // This looks like an error condition symbol table value is not there w06
         }
         break;      
      case ConstantK:
         currentNode->isConst = true;
         // case where string constant could be initialized in the global space.
         if (currentNode->type == ExpType::Char && currentNode->isArray)
         {
            currentNode->varKind = Global;
            currentNode->offset = (goffset - 1);
            goffset -= currentNode->size;
         }
         currentNode->isConst = true;
         break;
      case IdK:
         if ((temp = (TreeNode *)(symtab->lookup(currentNode->attr.name))))
         {
            temp->isUsed = true;
            currentNode->type = temp->type;
            currentNode->isStatic = temp->isStatic;
            currentNode->isArray = temp->isArray;
            currentNode->size = temp->size;
            currentNode->varKind = temp->varKind;
            currentNode->offset = temp->offset;
         }
         else
         {
            printf("An Error Occured\n");
            // probably an error w06
         }
         break;
      default:
      // another error?
         printf("unknown kind.exp");    
   }
}

bool insertCheck(TreeNode *currentNode, SymbolTable *symtab)
{
   if (!symtab->insert(currentNode->attr.name, currentNode))
   {
      // printf("symbol %s already declared at line %d", currentNode->lineno, currentNode->attr.name);
      return false;
   }
   return true;
}
