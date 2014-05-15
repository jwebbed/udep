#include <string.h>
#include <stdlib.h>

#include "sets/sets.h"
#include "csearch.h"

enum _struct {
    initial,
    _space,
    enum_struct,
    _typedef
};

struct set* findEnumStructs(char* prog, const char* es){
    struct set* set = initSet();
    char buf[BUF_SIZE];
    
    size_t s_len = strlen(es);
    
    enum _struct state = initial;
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
        if (comment == none) {
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
        
        if (state == initial && (strncmp(prog + k, es, s_len) == 0)){
            k+= s_len - 1;
            state = _space;
        } else if (state == _space){
            if (ch == '{'){
                state = _typedef;
                continue;
            } else if (ch == ' ' || ch == '\t') {
                whitespace++;
            } else if (validIndentifierChar(ch)){
                if (whitespace == 0)
                    state = initial;
                else if (validInitialIndentifierChar(ch)){
                    whitespace = 0;
                    start = k;
                    state = enum_struct;
                    continue;
                }
            } else
                exit(1);
        } else if (state == _typedef) {
            if (ch == '}'){
                whitespace = 1;
                state = _space;
            } else {
                continue;
            }
        } else if (state == enum_struct && !validIndentifierChar(ch)){
            strncpy(buf, prog + start, k - start);
            buf[k - start] = '\0';
            appendString(buf, set);
            state = initial;
        }
    }
    
    return set;
}
