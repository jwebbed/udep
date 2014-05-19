#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_checker.h"




void check_c(char* prog){
    struct set* function_set = findFunctionCalls(prog);
    struct set* struct_set = findStructs(prog);
    struct set* enum_set = findEnums(prog);
    struct set* include_set = findIncludes(prog);
    
    struct set_node* n;
    include inc;
    
    for (n = include_set->head; n != NULL; n = n->next){
        inc = includeInit(n->data);
        if (inc.type == global)
            getDeclarations(inc.name);
    }
    
    /*
    for (n = header_map->head; n != NULL; n = n->next){
        printf("%s\n", n->data);
        printf("---------\n");
        printSet(((c_set*)n->meta)->function_set);
        printf("\n");
    }
    */

    freeSet(function_set);
    freeSet(struct_set);
    freeSet(enum_set);
    freeSet(include_set);
    freeCMap(header_map);
}

