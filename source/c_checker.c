#include <stdlib.h>
#include <string.h>

#include "c_checker.h"
#include "csearch.h"

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
    
    c_set *set = getDeclarations("string.h");
    printSet(set->function_set);
}

c_set *mergeCSet(c_set *set1, c_set *set2){
    c_set *set;
    set->function_set = mergeSets(set1->function_set, set2->function_set);
    set->struct_set = mergeSets(set1->struct_set, set2->struct_set);
    set->enum_set = mergeSets(set1->enum_set, set2->enum_set);
    return set;
}

c_set *initCSet(){
    c_set *set = malloc(sizeof(c_set));
    set->name = NULL;
    set->enum_set = initSet();
    set->function_set = initSet();
    set->struct_set = initSet();
    return set;
}

c_set* csetcpy(c_set *set){
    c_set * nset = initCSet();
    strncpy(nset->name, set->name, strlen(set->name));
    nset->function_set = setcpy(set->function_set);
    nset->enum_set = setcpy(set->enum_set);
    nset->struct_set = setcpy(set->struct_set);
    return nset;
}