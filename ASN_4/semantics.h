#include <string.h>
#include "treeNodes.h"
#include "treeUtils.h"
#include "symbolTable.h"
#include "parser.tab.h" // Always put this last

TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax tree
                           bool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    );

void treeTraverse(TreeNode* syntree, SymbolTable *symtab);
void treeTraverseDecl(TreeNode *syntree, SymbolTable *symtab);
void treeTraverseStmt(TreeNode *syntree, SymbolTable *symtab);
void treeTraverseExp(TreeNode *syntree, SymbolTable *symtab);
bool insertCheck(TreeNode *syntree, SymbolTable *symtab);
