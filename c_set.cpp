//
//  c_set.cpp
//  udep
//
//  Created by Jonathan Webb on 2014-05-22.
//  Copyright (c) 2014 Jonathan Webb. All rights reserved.
//

#include "c_set.h"
#include "csearch.h"

c_set::c_set(char* prog){
    this->function_set = findFunctionCalls(prog);
    this->struct_set = findStructs(prog);
    this->enum_set = findEnums(prog);
    this->include_set = findIncludes(prog);
}
/*
 
 c_set *mergeCSet(c_set *set1, c_set *set2){
 c_set *set = initCSet();
 set->function_set = mergeSets(set1->function_set, set2->function_set);
 set->struct_set = mergeSets(set1->struct_set, set2->struct_set);
 set->enum_set = mergeSets(set1->enum_set, set2->enum_set);
 set->include_set = mergeSets(set1->include_set, set2->include_set);
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

*/