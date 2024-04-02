#include "semantics.h"


// GLOBAL SCOPE VARS

// memory offsets: ensure counts are updated until end of runtime
static int foffset = 0;
static int goffset = 0;

// not sure if this is needed
// static bool isNewScope = true;


TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax treebool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    );
{
   syntree = loadIOLib(syntree);
   // traverse the tree while doing the sematic analysis
   treeTraverse(syntree, symtab);
   // update and track globals
   globalOffset = goffset;
   return syntree;
}

// Generating 10 nodes as indicated by slide 4.
TreeNode *IOLib(TreeNode *syntree)
{
   // renamed node variables to reflect slide labels
   TreeNode *Func_input, *Func_inputB, *Func_inputC;
   TreeNode *Func_output, *Func_outputB, *Func_outputC;
   TreeNode *Param_output, *Param_outputB, Param_outputC; 
   TreeNode *Func_outnl;

   Func_input = newDeclNode(DeclKind::FuncK, Integer);
   Func_input->lineno = -1;
   Func_input->attr.name = strdup("input");
   Func_input->type = Integer;

   Func_inputB = newDeclNode(DeclKind::FuncK, Boolean);
   Func_inputB->lineno = -1;
   Func_inputB->attr.name = strdup("inputb");
   Func_inputB->type = Boolean;

   Func_inputC = newDeclNode(DeclKind::FuncK, Boolean);
   Func_inputC->lineno = -1;
   Func_inputC->attr.name = strdup("inputc");
   Func_inputC->type = Char;

   Param_output = newDeclNode(DeclKind::ParamK, Void);
   // Param_output->lineno = -1; Not Needed
   Param_output->attr.name = strdup("*dummy*");
   Param_output->type = Integer;

   Param_outputB = newDeclNode(DeclKind::ParamK, Void);
   // Param_outputB->lineno = -1; Not Needed
   Param_outputB->attr.name = strdup("*dummy*");
   Param_outputB->type = Boolean;

   Param_outputC = newDeclNode(DeclKind::ParamK, Void);
    // Param_outputC->lineno = -1; Not Needed
   Param_outputC->attr.name = strdup("*dummy*");
   Param_outpuC->type = Char;

   Func_output = newDeclNode(DeclKind::FuncK, Void);
   Func_output->lineno = -1;
   Func_output->attr.name = strdup("output");
   Func_output->type = Integer;

   Func_outputB = newDeclNode(DeclKind::FuncK, Void);
   Func_outputB->lineno = -1;
   Func_outputB->attr.name = strdup("outputb");
   Func_outputB->type = Boolean;

   Func_outputC = newDeclNode(DeclKind::FuncK, Void);
   Func_outputC->lineno = -1;
   Func_outputC->attr.name = strdup("outputc");
   Func_outputC->type = Char;

   Func_outnl = newDeclNode(DeclKind::FuncK, Void);
   Func_outnl->lineno = -1;
   Func_outnl->attr.name = strdup("outnl");
   Func_outnl->type = Void;
   Func_outnl->child[0] = NULL;

   // input connected to output
   Func_input->sibling = Func_output;
   // output connect to inputb
   Func_output->sibling = Func_inputB;
   Func_output->child[0] = Param_output;
   // inputb connected to outputgb
   Func_inputB->sibling = Func_outputB;
   Func_outputB->child[0] = Param_outputB;
   // outputb connected to inputc
   Func_outputB->sibling = Func_inputC;
   // inputc connected to outputc
   Func_inputC->sibling = Func_outputC;
   Func_outputC->child[0] = Param_outputC;
   // outputc connected to outnl
   Func_outputC->sibling = Func_outnl;
   // outnl connected to the sytnax tree nodes
   Func_outnl->sibling = syntree;
   Func_outnl->child[0] = NULL;

   return Func_input;
}


void treeTraverse(TreeNode *syntree, SymbolTable *symtab)
{
   int tempFoffset = foffset;
   bool isNodeCompound;
   // if the syntree is empty, do nothing
   if (syntree == NULL)
   {
      return;
   }

   isNodeCompound = compoundCheck(syntree);
   if (isNodeCompound == true)
   {
      char *newScope = strdup("{");
      symtab->enter("new scope " + (string)newScope);
   }

   // traverse the left child. Update symbol table 
   treeTraverse(syntree->child[0], symtab);
   // check the left node kind
   switch(syntree->nodekind)
   {
      case DeclK:
         treeTraverseDecl(syntree, symtab);
         break;

      case StmtK:
         treeTraverseStmt(syntree, symtab);
         break;
      
      case ExpK:
         treeTraverseExp(syntree, symtab);
         break;
      
      default:
         //print some sort of error
         break;
   }
   // end switch

   if (isNodeCompound == true)
   {
      symtab->leave();
   }

   if (syntree->kind.stmt == ForK && syntree->nodekind == StmtK)
   {
      foffset -= 2;
   }
   // visit the right child. Update symbol table
   treeTraverse(syntree->child[1], symtab);
   treeTraverse(syntree->child[2], symtab);

   if (syntree->kind.stmt == ForK && syntree->nodekind == NodeKind::StmtK)
   {
      syntree->size = foffset;
   }

   if( syntree->kind.stmt == CompoundK && syntree->nodekind == NodeKind::StmtK)
   {
      syntree->size = foffset;
      foffset = tempFoffset;
   }

   // now traverse the sibling nodes
   treeTraverse(syntree->sibling, symtab);

   if (syntree->kind.stmt == ForK && syntree->nodekind == StmtK)
   {
      foffset = tempFoffset;
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
               syntree->varKind = LocalStatic;
               syntree->offset = goffset;
               goffset -= syntree->size; 
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
      case ParamK:

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
               syntree->varKind = LocalStatic;
               syntree->offset = goffset;
               goffset -= syntree->size;
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
      case IfK:
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
            // probably an error w06
         }
         break;    
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