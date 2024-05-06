#include "codegen.h"
void codegenExpression(TreeNode *currnode)
{
   switch (currnode->kind.exp)
   {

      case AssignK:
         if (currnode->child[0]->attr.op == '[')
         {
            if (!currnode->child[1] && currnode->child[0]->varKind == Global)
            {
               switch (currnode->attr.op)
               {
               case INC:
                  emitRM((char *)"LDC", AC, int(currnode->child[0]->offset), 6, (char *)"Load integer constant");
                  emitRM((char *)"LDA", 5, currnode->child[0]->offset, 0, (char *)"Load address of base of array", currnode->child[0]->attr.name);
               }
            }

            if (currnode->attr.op == '=')
            {
               if (currnode->isArray)
               {
                  if (currnode->child[1])
                  {
                     emitStrLit(currnode->child[1]->offset, (char *)currnode->child[1]->attr.string);
                     emitRM((char *)"LDA", AC, int(currnode->child[1]->offset), 0, (char *)"Load address of char array");
                  }

                  if (currnode->varKind == Parameter)
                  {
                     emitRM((char *)"LD", AC1, int(currnode->child[0]->offset), 1, (char *)"address of lhs");
                     emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                     emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");
                     emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");
                     emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
                  }

                  else if (currnode->varKind != Parameter)
                  {
                     emitRM((char *)"LDA", AC1, int(currnode->child[0]->offset), 1, (char *)"address of lhs");
                     emitRM((char *)"LD", 5, 1, 3, (char *)"size of rhs");
                     emitRM((char *)"LD", 6, 1, 4, (char *)"size of lhs");
                     emitRO((char *)"SWP", 5, 6, 6, (char *)"pick smallest size");
                     emitRO((char *)"MOV", 4, 3, 5, (char *)"array op =");
                  }
               }
               else
               {
                  
                  emitRM((char *)"LDC", AC, currnode->child[1]->attr.value, 6, (char *)"Load integer constant");
                  emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name);
     
               }
            }

            else
            {

               if (currnode->child[1])
               {
                  emitRM((char *)"LDC", AC, currnode->child[1]->attr.value, 6, (char *)"Load integer constant");
               }

               switch (currnode->attr.op)
               {
               case ADDASS:
                  emitRM((char *)"LD", AC1, int(currnode->child[0]->offset), 1, (char *)"load lhs variable", currnode->child[0]->attr.name);
                  emitRO((char *)"ADD", 3, 4, 3, (char *)"op +=");
                  break;
               case DEC:
                  emitRM((char *)"LD", AC, int(currnode->child[0]->offset), 1, (char *)"load lhs variable", currnode->child[0]->attr.name);
                  emitRM((char *)"LDA", AC, -1, 3, (char *)"decrement value of", currnode->child[0]->attr.name);
                  break;
               case DIVASS:
                  emitRM((char *)"LD", AC1, int(currnode->child[0]->offset), 1, (char *)"load lhs variable", currnode->child[0]->attr.name);
                  emitRO((char *)"DIV", 3, 4, 3, (char *)"op /=");
                  break;
               case MULASS:
                  emitRM((char *)"LD", AC1, int(currnode->child[0]->offset), 1, (char *)"load lhs variable", currnode->child[0]->attr.name);
                  emitRO((char *)"MUL", 3, 4, 3, (char *)"op *=");
                  break;
               case SUBASS:
                  emitRM((char *)"LD", AC1, int(currnode->child[0]->offset), 1, (char *)"load lhs variable", currnode->child[0]->attr.name);
                  emitRO((char *)"SUB", 3, 4, 3, (char *)"op -=");
                  break;
               case INC:
                  emitRM((char *)"LD", AC, int(currnode->child[0]->offset), 1, (char *)"load lhs variable", currnode->child[0]->attr.name);
                  emitRM((char *)"LDA", AC, 1, 3, (char *)"increment value of", currnode->child[0]->attr.name);
                  break;
               }
               emitRM((char *)"ST", AC, currnode->child[0]->offset, FP, (char *)"Store variable", currnode->child[0]->attr.name);
            }
         }
         break;
   }
}