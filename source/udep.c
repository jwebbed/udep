#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "udep.h"



int main(int argc, char * argv[])
{
    FILE* fp;
    if (argc == 2){
        fp = fopen(argv[1], "r");
        if (errno == ENOENT){
            fprintf(stderr, "File does not exist\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Usage: udep <filename>.c\n");
        exit(1);
    }
    
    
    
    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
    char* program = calloc(sz + 1, sizeof(char));
	fread(program, sizeof(char), sz, fp);
    if (ferror(fp)){
        perror("fread");
        exit(1);
    }
    
    check_c(program);

    return 0;
}


