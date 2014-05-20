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

