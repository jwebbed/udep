#include <string.h>
#include <stdlib.h>

#include "sets.h"
#include "csearch.h"

enum _enum {
    initial,
    _space,
    enum_struct
};

struct set* findEnums(char* prog){
    struct set* set = initSet();
    char buf[BUF_SIZE];
    
    enum _enum state = initial;
    enum comment comment = none;
    int depth = 0;
    int whitespace = 0;
    
    size_t len = strlen(prog);
    int k = 0;
    int start = 0;
    for (char ch = prog[k]; k < len; ch = prog[++k]){
        if (ch == '{') depth++;
        else if (ch == '}') depth--;
        
        // Looks for comments
        if (comment == none){
            if (ch == '/') comment = potential;
        } else if (comment == potential){
            if (ch == '/') {
                comment = line;
                state = initial;
            }
            else if (ch == '*') {
                comment = block;
                state = initial;
            } else comment = none;
        } else if (comment == block){
            if (ch == '*' && prog[k+1] == '/') {
                k++;
                comment = none;
            }
            continue;
        } else if (comment == line){
            if (ch == '\n') comment = none;
            continue;
        }
        
        if (state == initial && ch == 'e'){
            if(prog[k+1] == 'u' && prog[k+2] == 'u' && prog[k+3] == 'm' && (k+3) < len){
                k+=3;
                state = _space;
            }
        } else if (state == _space){
            if (validIndentifierChar(ch)){
                if (whitespace == 0)
                    state = initial;
                else if (validInitialIndentifierChar(ch)){
                    whitespace = 0;
                    start = k;
                    state = enum_struct;
                    continue;
                }
            } else if (ch == ' ') whitespace++;
            else exit(1);
        } else if (state == enum_struct && !validIndentifierChar(ch)){
            strncpy(buf, prog + start, k - start);
            buf[k - start] = '\0';
            appendString(buf, set);
            state = initial;
        }
        
    }
    return set;
}