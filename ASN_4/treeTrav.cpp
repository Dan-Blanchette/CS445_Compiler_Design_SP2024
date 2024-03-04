void treeTraverseDecl(TreeNode *syntree, SymblTable *symtab)
{
   // debug statement here
   TreeNode * c0,  *c1, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];

   switch(syntree->kind.decl)
   {
      case FunK:
         // debug goes here
         int foffset = -2;
   }
}