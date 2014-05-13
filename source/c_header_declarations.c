#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "sets.h"
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




