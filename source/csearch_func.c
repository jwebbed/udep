#include <string.h>

#include "c_checker.h"

enum func {
    init,
    name,
    space_after_name,
    left_bracket,
    declaration
};

char* keywords[] = { "while", "for", "sizeof", "if", "else", "switch" };

bool isKeyword(char* buf){
    char* word;
    int i = 0;
    for (word = keywords[i]; i < 6; word = keywords[++i]){
        if (strcmp(buf, word) == 0)
            return true;
    }
    return false;
}

struct set* _findFunctionCalls(char * prog, int header){
    struct set* set = initSet();
    char buf[BUF_SIZE];
    
    enum func state = init;
    enum comment comment = none;
    int depth = 0;
    
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
                state = init;
            }
            else if (ch == '*') {
                comment = block;
                state = init;
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
        
        // Looks for functions
        if (state == init){
        init:
            if (validInitialIndentifierChar(ch)){
                state = name;
                start = k;
            }
        } else if (state == name){
            if (ch == ' '){
                state = space_after_name;
            } else if (ch == '('){
                state = left_bracket;
            } else if (!validIndentifierChar(ch)){
                state = init;
            }
        } else if (state == space_after_name){
            if (ch == '('){
                state = left_bracket;
            } else if (ch != ' '){
                state = name;
                start = k;
            }
        } else if (state == left_bracket){
            if (header || depth){
                strncpy(buf, prog + start, k - start - 1);
                buf[k - start - 1] = '\0';
                stripWhiteSpace(buf);
                if (!isKeyword(buf)) appendString(buf, set);
            }
            state = init;
            goto init;
        }
    }
    return set;
}