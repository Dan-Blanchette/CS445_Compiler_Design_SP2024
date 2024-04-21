#include <string.h>
#include "treeNodes.h"
#include "treeUtils.h"
#include "symbolTable.h"

TreeNode *semanticAnalysis(TreeNode *syntree,          // pass in and return an annotated syntax tree
                           bool shareCompoundSpaceIn,   // SPECIAL OPTION: make compound after a function share scope
                           bool noDuplicateUndefsIn,    // SPECIAL OPTION: no duplicate undefines
                           SymbolTable *symtabX,       // pass in and return the symbol table
                           int &globalOffset            // return the offset past the globals
    );

// need to make the 10 new nodes from slide 4 and generate the symbol table with default values?
TreeNode *loadIOLib(TreeNode *syntree);

void treeTraverse(TreeNode* currentNode, SymbolTable *symtab);
void treeTraverseDecl(TreeNode *currentNode, SymbolTable *symtab);
void treeTraverseStmt(TreeNode *currentNode, SymbolTable *symtab);
void treeTraverseExp(TreeNode *currentNode, SymbolTable *symtab);
bool insertCheck(TreeNode *currentNode, SymbolTable *symtab);
bool compoundCheck(TreeNode *currentNode);
