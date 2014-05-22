//
//  main.cpp
//  udep
//
//  Created by Jonathan Webb on 2014-05-22.
//  Copyright (c) 2014 Jonathan Webb. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[])
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
    
    char* program = (char*)calloc(sz + 1, sizeof(char));
	fread(program, sizeof(char), sz, fp);
    if (ferror(fp)){
        perror("fread");
        exit(1);
    }

    return 0;
}

