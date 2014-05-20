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

c_set *mergeCSet(c_set *set1, c_set *set2){
    c_set *set = initCSet();
    set->function_set = mergeSets(set1->function_set, set2->function_set);
    set->struct_set = mergeSets(set1->struct_set, set2->struct_set);
    set->enum_set = mergeSets(set1->enum_set, set2->enum_set);
    set->include_set = mergeSets(set1->include_set, set2->include_set);
    return set;
}


c_set *initCSet(){
    c_set *set = malloc(sizeof(c_set));
    set->name = NULL;
    set->enum_set = initSet();
    set->function_set = initSet();
    set->struct_set = initSet();
    set->include_set = initSet();
    return set;
}

c_set* csetcpy(c_set *set){
    c_set * nset = initCSet();
    if (set->name != NULL)
        setname(nset, set->name);
    nset->function_set = setcpy(set->function_set);
    nset->enum_set = setcpy(set->enum_set);
    nset->struct_set = setcpy(set->struct_set);
    nset->include_set = setcpy(set->struct_set);
    return nset;
}

void setname(c_set *set, char * name){
    free(set->name);
    set->name = calloc(sizeof(char) * strlen(name), 0);
    strncpy(set->name, name, strlen(name));
}

void freeCSet(c_set *set){
    free(set->name);
    freeSet(set->function_set);
    freeSet(set->struct_set);
    freeSet(set->enum_set);
    freeSet(set->include_set);
    free(set);
}