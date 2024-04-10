#include "semantics.h"
#include <string.h>
#include "parser.tab.h"


// GLOBAL SCOPE VARS

// memory offsets: ensure counts are updated until end of runtime
static int foffset;
static int goffset;

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
   // globalOffset = goffset;
   treeTraverse(syntree, symtabX);
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
   Param_output->lineno = -1; // all are -1
   Param_output->attr.name = strdup("*dummy*");
   Param_output->type = ExpType::Integer;

   Param_output_b = newDeclNode(DeclKind::ParamK, ExpType::Void);
   Param_output_b->lineno = -1; // all are -1
   Param_output_b->attr.name = strdup("*dummy*");
   Param_output_b->type = ExpType::Boolean;

   Param_output_c = newDeclNode(DeclKind::ParamK, ExpType::Void);
   Param_output_c->lineno = -1; // all are -1
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


void treeTraverse(TreeNode *syntree, SymbolTable *symtab)
{
   int tempOffset = foffset;
   bool isComp = false;
   // if the syntree is empty, do nothing
   if (syntree != nullptr)
   {
      switch(syntree->nodekind)
      {
         case NodeKind::DeclK:
            treeTraverseDecl(syntree, symtab);
            break;

         case NodeKind::StmtK:
            treeTraverseStmt(syntree, symtab);
            break;
         
         case NodeKind::ExpK:
            treeTraverseExp(syntree, symtab);
            break;
         
         default:
            printf("unknown nodekind\n");
            break;
      } 
      // end switch

      // if there is a for loop, foffset is -2 (according to notes from class)
      if (syntree->nodekind == StmtK && syntree->kind.stmt == ForK)
      {
         foffset -= 2;
      }

      treeTraverse(syntree->child[1], symtab);
      treeTraverse(syntree->child[2], symtab);

      if (syntree->nodekind == StmtK && syntree->kind.stmt == ForK)
      {
         syntree->size = foffset;
      }

      if (isComp)
      {
         symtab->leave();
      }

      if (syntree->nodekind == StmtK && syntree->kind.stmt == CompoundK)
      {
         syntree->size = foffset;
         // not sure if this is needed
         foffset = tempOffset;
      }

      // Be sure to traverse the siblings
      treeTraverse(syntree->sibling, symtab);

      if (syntree->nodekind == StmtK && syntree->kind.stmt == ForK)
      {
         foffset = tempOffset;
      }
   }
   return;
}

void treeTraverseDecl(TreeNode *syntree, SymbolTable *symtab)
{
   // debug statement here
   TreeNode *c0,  *c1, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];

   switch(syntree->kind.decl)
   {
      case FuncK:
         // debug goes here
         foffset = -2;
         insertCheck(syntree, symtab);
         symtab->enter(syntree->attr.name);

         treeTraverse(c0, symtab);
         syntree->varKind = Global;
         syntree->size = foffset;
         treeTraverse(c1, symtab);
         symtab->leave();
         break;

      case VarK:
         // printf("VarK");
         if(c0 != NULL)
         {
            syntree->isAssigned = true;
            syntree->varKind = Local;
            treeTraverse(c0, symtab);
         }
         // no break statement needed here
      case ParamK:
         // printf("In ParamK\n");
         if (insertCheck(syntree, symtab))
         {
            if (symtab->depth() == 1)
            {
               // printf("In ParamK depth check %d\n", goffset);
               syntree->varKind = Global;
               syntree->offset = goffset;
               goffset -= syntree->size;
            }
            else if(syntree->isStatic)
            {
               // printf("In ParamK is static %d\n", goffset);
               syntree->varKind = LocalStatic;
               syntree->offset = goffset;
               goffset -= syntree->size;
            }
            else
            {
               // printf("In ParamK else %d %d\n", foffset, syntree->size);
               syntree->varKind = Local;
               syntree->offset = foffset;
               foffset -= syntree->size;
               printf("offset: %d", foffset);
            }
         }
         if(syntree->kind.decl == ParamK)
         {
            syntree->varKind = Parameter;
         }
         else if(syntree->isArray)
         {
            syntree->offset--;
         }
         break;

      default:
         printf("Unknown kind.decl");         
   }   
}

void treeTraverseStmt(TreeNode *syntree, SymbolTable *symtab)
{
   TreeNode *c0,  *c1, *c2, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];
   c2 = syntree->child[2];

   switch(syntree->kind.stmt)
   {
      case CompoundK:
         int newScopeOffset;
         symtab->enter((char *)"compound statement");
         newScopeOffset = foffset;
         // tree traverse your left child
         treeTraverse(c0, symtab);
         // deal with your self
         syntree->size = foffset;
         // traverse your right child
         treeTraverse(c1, symtab);
         foffset = newScopeOffset;
         symtab->leave();
         break;

      case IfK:
         treeTraverse(c0, symtab);
         syntree->size = foffset - 1;
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
         syntree->size = foffset;
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

void treeTraverseExp(TreeNode *syntree, SymbolTable *symtab)
{
   TreeNode *c0,  *c1, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];

   switch(syntree->kind.exp)
   {
      case OpK:
         // treeTraverse(c0, symtab);
         // treeTraverse(c1, symtab);
      case AssignK:
         treeTraverse(c0, symtab);
         treeTraverse(c1, symtab);
         if(syntree->attr.op == int('+') || syntree->attr.op == int('['))
         {
            syntree->type = c0->type;
         }
         else if(syntree->attr.op == AND || syntree->attr.op == OR || 
                  syntree->attr.op == LEQ || syntree->attr.op == GEQ ||
                  syntree->attr.op == NOT || syntree->attr.op == int('<') ||
                  syntree->attr.op == int('>') || syntree->attr.op == EQ ||
                  syntree->attr.op == NEQ)
         {
            syntree->type = ExpType::Boolean;
         }
         else
         {
            syntree->type = ExpType::Integer;
         }         
         break;
      case CallK:
         if(temp = (TreeNode *)(symtab->lookup(syntree->attr.name)))
         {
            temp->isUsed = true;
            syntree->type = temp->type;
            syntree->isArray = temp->isArray;
            syntree->isStatic = temp->isStatic;
            syntree->varKind = temp->varKind;
            syntree->offset = temp->offset;
            syntree->size = temp->size;
         }
         else
         {
           // This looks like an error condition symbol table value is not there w06
         }
         break;      
      case ConstantK:
         syntree->isConst = true;
         // case where string constant could be initialized in the global space.
         if (syntree->type == syntree->isArray && ExpType::Char)
         {
            syntree->varKind = Global;
            syntree->offset = (goffset - 1);
            goffset -= syntree->size;
         }
         break;
      case IdK:
         if ((temp = (TreeNode *)(symtab->lookup(syntree->attr.name))))
         {
            temp->isUsed = true;
            syntree->type = temp->type;
            syntree->isStatic = temp->isStatic;
            syntree->isArray = temp->isArray;
            syntree->size = temp->size;
            syntree->varKind = temp->varKind;
            syntree->offset = temp->offset;
         }
         else
         {
            // probably an error w06
         }
         break;
      default:
         printf("unknown kind.exp");    
   }
}

bool insertCheck(TreeNode *syntree, SymbolTable *symtab)
{
   if (!symtab->insert(syntree->attr.name, syntree))
   {
      return false;
   }
   return true;
}

bool compoundCheck(TreeNode *syntree)
{
   if (syntree == NULL)
   {
      return false;
   }

   if (syntree->kind.decl == FuncK && syntree->nodekind == DeclK)
   {
      foffset = -2;
      return true;
   }

   if (syntree->nodekind == StmtK)
   {
      if (syntree->kind.stmt == ForK || syntree->kind.stmt == CompoundK)
      {
         return true;
      }
   }

   return false;
}