#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_checker.h"

c_set* buildCSet(char* prog){
    c_set* set = malloc(sizeof(c_set));
    set->function_set = findFunctionCalls(prog);
    set->struct_set = findStructs(prog);
    set->enum_set = findEnums(prog);
    set->include_set = findIncludes(prog);
    set->name = NULL;
    return set;
}

void check_c(char* prog){
    c_set* set = buildCSet(prog);
    struct set_node* n;
    include inc;
    
    for (n = set->include_set->head; n != NULL; n = n->next){
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

    freeCSet(set);
    freeCMap(header_map);
}

