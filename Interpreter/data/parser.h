#include "token.h"
#include "parser_datas/AST_node.h"

ASTNodeType GetASTType(Token *current);
void FillNodeWithNewTokens(Token **current, ASTNode *node);
int Parser(Token *headTokenList, ASTList *headASTList);