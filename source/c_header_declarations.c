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
#include <unistd.h>
#include <errno.h>

#include "c_checker.h"

// checks if a header file exists in the input dir,
// returns 1 if sucessful 0 if not
int checkHeader(const char* dir, char* header){
    char full[strlen(dir) + strlen(header)];
    strcpy(full, dir);
    strcat(full, header);
    return (access(full, F_OK) == 0);
}

/* 
 * searches for a header file
 * returns 1 if sucessful 0 if not
 */
int searchHeader(char* header, FILE** fp){
    if (checkHeader("/usr/local/include/", header)){
        char full[strlen("/usr/local/include/") + strlen(header)];
        strcpy(full, "/usr/local/include/");
        strcat(full, header);
        
        *fp = fopen(full, "r");
        if (*fp == NULL) exit(1);
        
        return 1;
    } else if (checkHeader("/usr/target/include/", header)){
        char full[strlen("/usr/target/include/") + strlen(header)];
        strcpy(full, "/usr/target/include/");
        strcat(full, header);
        
        *fp = fopen(full, "r");
        if (*fp == NULL) exit(1);
        
        return 1;
    } else if (checkHeader("/usr/include/", header)){
        char full[strlen("/usr/include/") + strlen(header)];
        strcpy(full, "/usr/include/");
        strcat(full, header);
        
        *fp = fopen(full, "r");
        if (*fp == NULL) exit(1);
        
        return 1;
    } else {
        return 0;
    }
}

int getHeader(char** file, char* header){
    FILE* fp;
    if (searchHeader(header, &fp)){
        fseek(fp, 0L, SEEK_END);
        long sz = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        
        *file = calloc(sz + 1, sizeof(char));
        fread(*file, sizeof(char), sz, fp);
        if (ferror(fp)){
            perror("fread");
            exit(1);
        }
        return 1;
    } else {
        return 0;
    }
}

c_map* header_map = NULL;

c_set *getDeclarations(char* header){
    if (header_map == NULL)
        header_map = initCMap();
    
    c_set* set = initCSet();
    c_set* found_set;
    include inc;
    char* prog;
    
    if (getHeader(&prog, header)){
        setname(set, header);
        set->function_set = findFunctionDeclarations(prog);
        set->struct_set = findStructs(prog);
        set->enum_set = findEnums(prog);
        
        struct set* include_set = findIncludes(prog);
        set->include_set = include_set;
        appendCSet(header_map, csetcpy(set));
        
        if (setLen(include_set) > 0){
            for (struct set_node* n = include_set->head; n != NULL; n = n->next) {
                inc = includeInit(n->data);
                if (inc.type == global){
                    if ((found_set = getCSet(header_map, inc.name)) != NULL){
                        set = mergeCSet(set, found_set);
                    } else {
                        set = mergeCSet(set, getDeclarations(inc.name));
                    }
                }
            }
        }
    }
    return set;
}




