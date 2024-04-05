#include "semantics.h"
#include "parser.tab.h"


// GLOBAL SCOPE VARS

// memory offsets: ensure counts are updated until end of runtime
static int foffset;
static int goffset;

// not sure if this is needed
// static bool isNewScope = true;

TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax tree
                           bool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    )
{
   syntree = loadIOLib(syntree);
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
   output->type = ExpType::Integer;

   outputB = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outputB->lineno = -1; // all are -1
   outputB->attr.name = strdup("outputb");
   outputB->type = ExpType::Void;
   // child node as seen in slides
   outputB->child[0] = Param_outputB;

   outputC = newDeclNode(DeclKind::FuncK, ExpType::Void);
   outputC->lineno = -1; // all are -1
   outputC->attr.name = strdup("outputc");
   outputC->type = ExpType::Void;
   // child node as seen in slides
   outputC->child[0] = Param_outputC;

   Func_outnl = newDeclNode(DeclKind::FuncK, ExpType::Void);
   Func_outnl->lineno = -1; // all are -1
   Func_outnl->attr.name = strdup("outnl");
   Func_outnl->type = ExpType::Void;
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
   // if the syntree is empty, do nothing
   if (syntree != nullptr)
   {
      treeTraverse(syntree->child[0], symtab);
      // check the left node kind
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
            treeTraverse(syntree->sibling, symtab);
            break;
      }
   // end switch
   }
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
         foffset = -1;
         insertCheck(syntree, symtab);
         symtab->enter(syntree->attr.name);
         treeTraverse(c0, symtab);
         syntree->varKind = Global;
         syntree->size = foffset - 1;
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
               syntree->offset = foffset - 1;
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
   TreeNode *c0,  *c1, *c2, *temp;
   c0 = syntree->child[0];
   c1 = syntree->child[1];
   c2 = syntree->child[2];

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
         treeTraverse(c0, symtab);
         syntree->size = foffset -1;
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
         treeTraverse(c0, symtab);
         foffset--;
         treeTraverse(c1, symtab);
         foffset--;
         treeTraverse(c2, symtab);
         foffset--;
         syntree->size = foffset;
         break;
      default:
         printf("unknow kind.stmt");
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
            // syntree->isArray = temp->isArray;
            // syntree->isStatic = temp->isStatic;
            // syntree->varKind = temp->varKind;
            // syntree->offset = temp->offset;
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
         // if (syntree->type == syntree->isArray && ExpType::Char)
         // {
         //    syntree->varKind = Global;
         //    syntree->offset = (goffset - 1);
         //    goffset -= syntree->size;
         // }
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