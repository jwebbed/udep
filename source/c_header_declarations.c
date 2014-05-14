#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "sets/sets.h"
#include "c_checker.h"
#include "csearch.h"

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

c_set getDeclarations(char* header){
    c_set set = initCSet();
    char* prog;
    if (getHeader(&prog, header)){
        set.function_set = findFunctionDeclarations(prog);
        set.struct_set = findStructs(prog);
        set.enum_set = findEnums(prog);
        
        struct set* include_set = findIncludes(prog);
        include inc;
        if (setLen(include_set) > 0){
            for (struct set_node* n = include_set->head; n != NULL; n = n->next) {
                inc = includeInit(n->data);
                if (inc.type == global)
                    set = mergeCSet(set, getDeclarations(inc.name));
            }
        }
    }
    return set;
}




