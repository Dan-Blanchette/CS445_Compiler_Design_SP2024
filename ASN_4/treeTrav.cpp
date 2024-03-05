#include "treeUtils.h"
#include "treeTrav.h"


void treeTraverseDecl(TreeNode *syntree, SymblTable *symtab)
{
   // debug statement here
   int foffset = 0;
   int goffset = 0;
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
         treeTraverse(c1, symtab);
         symtab->leave();
         break;

      case VarK:
         // printf("VarK");
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
         break;
      case
   }
}