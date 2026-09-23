#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef void (*RuneFunction)(char *);

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
void FunctionsMapAdd(FunctionsMap *map, const char *identifier, RuneFunction function);
RuneFunction FunctionsMapGet(FunctionsMap *map, const char *identifier);
int FunctionsMapRemove(FunctionsMap *map, const char *identifier);

