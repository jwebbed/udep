#include "c_checker.h"
#include "sets.h"

void check_c(char* prog){
    struct set* function_set = findFunctionCalls(prog);
    struct set* struct_set = findStructs(prog);
    struct set* enum_set = findEnums(prog);
    struct set* include_set = findIncludes(prog);
    
    printSet(include_set);
    
    freeSet(function_set);
    freeSet(struct_set);
    freeSet(enum_set);
    freeSet(include_set);
}