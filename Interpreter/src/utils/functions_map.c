#include "../../data/utils/functions_map.h"

#include <string.h>

FunctionsMap *FunctionsMapInit(void){
    return calloc(1, sizeof(FunctionsMap));
}

void FunctionsMapAdd(FunctionsMap *map, const char *identifier, RuneFunction function)
{
    if (map == NULL || identifier == NULL || function == NULL) {
        return;
    }

    int bucketLocation = Hash(identifier);
    EntryFunctions *informations = malloc(sizeof(EntryFunctions));

    if (informations == NULL) {
        return;
    }

    informations->identifier = strdup(identifier);
    informations->function = function;
    informations->next = map->nodes[bucketLocation];
    map->nodes[bucketLocation] = informations;
}

RuneFunction FunctionsMapGet(FunctionsMap *map, const char *identifier)
{
    if (map == NULL || identifier == NULL) {
        return NULL;
    }

    int bucketIndex = Hash(identifier);
    EntryFunctions *currentEntry = map->nodes[bucketIndex];

    while (currentEntry != NULL) {
        if (strcmp(currentEntry->identifier, identifier) == 0) {
            return currentEntry->function;
        }

        currentEntry = currentEntry->next;
    }

    return NULL;
}

int FunctionsMapRemove(FunctionsMap *map, const char *identifier)
{
    if (map == NULL || identifier == NULL) {
        return 0;
    }

    int bucketIndex = Hash(identifier);
    EntryFunctions *currentEntry = map->nodes[bucketIndex];
    EntryFunctions *beforeEntry = NULL;

    while (currentEntry != NULL) {
        if (strcmp(currentEntry->identifier, identifier) == 0) {
            if (beforeEntry != NULL) {
                beforeEntry->next = currentEntry->next;
            }
            else {
                map->nodes[bucketIndex] = currentEntry->next;
            }

            free(currentEntry->identifier);
            free(currentEntry);
            return 1;
        }

        beforeEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    return 0;
}
