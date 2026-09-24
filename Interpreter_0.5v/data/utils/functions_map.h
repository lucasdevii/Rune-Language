#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../parser_datas/AST_node.h"
#include "variables_map.h"

typedef void (*RuneFunction)(ASTNode *, VariablesMap *);

typedef struct EntryFunctions {
    char *identifier;
    RuneFunction function;
    struct EntryFunctions *next;
} EntryFunctions;

typedef struct {
    EntryFunctions *nodes[50];
} FunctionsMap;

extern FunctionsMap *functionsMap;

int Hash(const char *identifier);

FunctionsMap *FunctionsMapInit(void);
void FunctionsMapAdd(const char *identifier, RuneFunction function);
RuneFunction FunctionsMapGet(const char *identifier);
int FunctionsMapRemove(const char *identifier);

