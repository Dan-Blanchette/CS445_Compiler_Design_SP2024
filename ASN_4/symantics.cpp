#include "semantics.h"

int foffset = 0;
int goffset = 0;


TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax treebool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    );
{
   // code goes here
}

void treeTraverse(TreeNode *syntree, SymbolTable *symtab)
{
   // code for bottom up parsing: post order algorithm code
}

bool insertCheck(TreeNode *syntree, SymbolTable *symtab)
{
   if (!symtab->insert(syntree->attr.name, syntree))
   {
      return false;
   }
   return true;
}

void treeTraverseDecl(TreeNode *syntree, SymbolTable *symtab)
{
   // debug statement here
   TreeNode *c0,  *c1, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];

   switch(syntree->kind.decl)
   {
      case FunK:
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
            treeTraverse(c0, symtab);
         }
         if (insertCheck(syntree, symtab))
         {
            if (symtab->depth() == 1)
            {
               syntree->varKind = Global;
               syntree->offset = goffset;
               goffset -= syntree->size;
            }
            else if(syntree->isStatic)
            {
               //// remember to finish this
            }
            else
            {
               syntree->varKind = Local;
               syntree->offset = foffset;
               foffset -= syntree->size;
            }
         }
         // no break statement needed here
      case paramK:

         if (insertCheck(syntree, symtab))
         {
            if (symtab->depth() == 1)
            {
               syntree->varKind = Global;
               syntree->offset = goffset;
               goffset -= syntree->size;
            }
            else if(syntree->isStatic)
            {
               //// remember to finish this
            }
            else
            {
               syntree->varKind = Local;
               syntree->offset = foffset;
               foffset -= syntree->size;
            }
         }
         if(syntree->kind.decl == ParamK)
         {
            syntree->VarKind = Parameter;
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
   TreeNode *c0,  *c1, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];

   switch(syntree->kind.stmt)
   {
      case CompoundK:
         // tree traverse your left child
         treeTraverse(c0, symtab);
         // deal with your self
         syntree->size = foffset;
         // traverse your right child
         treeTraverse(c1, symtab);
         break;
      case IfK;
         break;
      case ReturnK:
         break;
      case WhileK:
         break;
      case ForK:
         break;
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
         treeTraverse(c0, symtab);
         treeTraverse(c1, symtab);
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
                  syntree->attr.op == NEQ )
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
            syntree->size = temp->size;
         }
         else
         {
           // This looks like an error condition symbol table vaue is not there w06
         }
         break;      
      case ConstantK:
         syntree->isConst = true;
         break;
      case IdK:
         if (temp = (TreeNode *)(symtab->lookup(syntree->attr.name)))
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
            // probably and error w06
         }
         break;    
   }
}