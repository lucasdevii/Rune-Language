#include "token.h"
#include "parser_datas/AST_node.h"

ASTNodeType getASTType(Token *current);
void fillNodeWithNewTokens(Token **current, ASTNode *node);
int parser(Token *head);