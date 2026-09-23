#include "../../data/utils/functions_map.h"

#include <string.h>

FunctionsMap *functionsMap = NULL;

FunctionsMap *FunctionsMapInit(void){
    return calloc(1, sizeof(FunctionsMap));
}

void FunctionsMapAdd(const char *identifier, RuneFunction function)
{
    if (functionsMap == NULL || identifier == NULL || function == NULL) {
        return;
    }

    int bucketLocation = Hash(identifier);
    EntryFunctions *informations = malloc(sizeof(EntryFunctions));

    if (informations == NULL) {
        return;
    }

    informations->identifier = strdup(identifier);
    informations->function = function;
    informations->next = functionsMap->nodes[bucketLocation];
    functionsMap->nodes[bucketLocation] = informations;
}

RuneFunction FunctionsMapGet(const char *identifier)
{
    if (functionsMap == NULL || identifier == NULL) {
        return NULL;
    }

    int bucketIndex = Hash(identifier);
    EntryFunctions *currentEntry = functionsMap->nodes[bucketIndex];

    while (currentEntry != NULL) {
        if (strcmp(currentEntry->identifier, identifier) == 0) {
            return currentEntry->function;
        }

        currentEntry = currentEntry->next;
    }

    return NULL;
}