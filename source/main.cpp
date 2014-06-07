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

#include <iostream>
#include <string>
#include "udep.h"
#include "program.h"

language_t determineLangauge(std::string filename){
    unsigned long len = filename.length();
    for (unsigned long i = len - 1; i > 0; i--){
        if (filename[i] == '.'){
            std::string ext = filename.substr(i + 1, len - i - 1);
            if (ext == "c")
                return c;
            else if (ext == "py")
                return python;
            else
                break;
        }
    }
    printf("Cannot determine language, either langauge not implemented or extension unrecognized, please include program type in program arguments (NYI)");
    exit(1);
}

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
        fprintf(stderr, "Usage: udep <filename>\n");
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
    
    Program prog = Program(std::string(program), determineLangauge(std::string(argv[1])));
    prog.checkProg();

    return 0;
}

