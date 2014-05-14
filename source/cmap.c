#include <stdlib.h>

#include "c_checker.h"

void appendCSet(c_map *map, c_set *set){
    struct set_node *node = appendString(set->name, map);
    node->meta = set;
}

c_set* checkForCSet(c_map *map, char* name){
    
}