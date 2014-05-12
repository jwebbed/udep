#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// checks if a header file exists in the input dir,
// returns 1 if sucessful 0 if not
int checkHeader(const char* dir, char* header){
    char full[strlen(dir) + strlen(header)];
    strcat(full, dir);
    strcat(full, header);
    return access(full, R_OK);
}

// searches for a header file
// returns 1 if sucessful 0 if not
int searchHeader(char* header, FILE** fp){
    if (checkHeader("/usr/local/include/", header)){
        char full[strlen("/usr/local/include/") + strlen(header)];
        strcat(full, "/usr/local/include/");
        strcat(full, header);
        FILE* f = fopen(full, "r");
        fp = &f;
        return 1;
    } else if (checkHeader("/usr/target/include/", header)){
        char full[strlen("/usr/target/include/") + strlen(header)];
        strcat(full, "/usr/target/include/");
        strcat(full, header);
        FILE* f = fopen(full, "r");
        fp = &f;
        return 1;
    } else if (checkHeader("/usr/include/", header)){
        char full[strlen("/usr/include/") + strlen(header)];
        strcat(full, "/usr/include/");
        strcat(full, header);
        FILE* f = fopen(full, "r");
        fp = &f;
        return 1;
    } else {
        return 0;
    }
}
