/*
 Copyright (c) 2014 Jonathan Webb
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <stdlib.h>

#include "c_checker.h"

void appendCSet(c_map *map, c_set *set){
    struct set_node *node = appendString(set->name, map);
    if (node != NULL){
        node->meta = malloc(sizeof(set));
        node->meta = set;
    }
}

c_set* getCSet(c_map *map, char* name){
    struct set_node* n = linSearch(map, name);
    if (n != NULL)
        return n->meta;
    else
        return NULL;
}

void freeCMap(c_map* map){
    for (struct set_node* n = map->head; n != NULL; n = n->next)
        freeCSet((c_set*)n->meta);
    freeSet(map);
}


c_set* mergeCMapToCSet(c_map* map){
    c_set* set = initCSet();
    for (struct set_node* n = map->head; n != NULL; n = n->next)
        set = mergeCSet(set, (c_set*)n->meta);
    return set;
    
}
