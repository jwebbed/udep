#include "c_checker.h"
#include "sets.h"

void check_c(char* prog){
    struct set* function_set = findFunctionCalls(prog);
    struct set* struct_set = findStructs(prog);
    struct set* enum_set = findEnums(prog);
    struct set* include_set = findIncludes(prog);
    
    //printSet(function_set);
    
    freeSet(function_set);
    freeSet(struct_set);
    freeSet(enum_set);
    freeSet(include_set);
    
    
    char *header;
    if (getHeader(&header, "string.h")){
        struct set* fset = findFunctionDeclarations(header);
        //printf("%s\n", header);
        printSet(fset);
        freeSet(fset);
    }
    
}