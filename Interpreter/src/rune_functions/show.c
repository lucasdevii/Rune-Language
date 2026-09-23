#include "../../data/rune_functions/functions/show.h"

#include <stdio.h>

void show(ASTNode *node){
    printf("%s\n", node->call.arguments);
}