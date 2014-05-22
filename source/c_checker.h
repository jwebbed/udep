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

#include <stdbool.h>
#include "sets/sets.h"

// c_set declarations
typedef struct {
    char * name;
    struct set* function_set;
    struct set* struct_set;
    struct set* enum_set;
    struct set* include_set;
} c_set;

c_set* getDeclarations(char* header);
c_set* mergeCSet(c_set *set1, c_set *set2);
c_set* initCSet();
c_set* csetcpy(c_set *set);
void freeCSet(c_set *set);
void setname(c_set *set, char * name);

// c_map declarations
typedef struct set c_map;
extern c_map* header_map;
#define initCMap() initSet()
void appendCSet(c_map *map, c_set *set);
c_set * getCSet(c_map *map, char* name);
void freeCMap(c_map* map);
c_set* mergeCMapToCSet(c_map* map);
