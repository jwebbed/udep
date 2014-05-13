#include "c_checker.h"
#include "csearch.h"
#include "sets/sets.h"

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

c_set mergeCSet(c_set set1, c_set set2){
    c_set set;
    set.function_set = mergeSets(set1.function_set, set2.function_set);
    set.struct_set = mergeSets(set1.struct_set, set2.struct_set);
    set.enum_set = mergeSets(set1.enum_set, set2.enum_set);
    return set;
}