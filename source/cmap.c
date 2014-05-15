#include <stdlib.h>

#include "c_checker.h"

void appendCSet(c_map *map, c_set *set){
    struct set_node *node = appendString(set->name, map);
    if (node != NULL){
        node->meta = malloc(sizeof(set));
        node->meta = set;
    }
}

c_set* checkForCSet(c_map *map, char* name){
    struct set_node* n = linSearch(map, name);
    if (n != NULL)
        return n->meta;
    else
        return NULL;
}
