#include "../utils/functions_map.h"
#include "./functions/show.h"


FunctionsMap *FunctionsMapInit(void);

void RegisterRuneFunctions(){
    FunctionsMapAdd(functionsMap, "show", show);
}
