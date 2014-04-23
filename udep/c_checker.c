#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "sets.h"
#include "c_checker.h"


enum include {
    pound,
    i,
    n,
    c,
    l,
    u,
    d,
    e,
    space,
    lb,
    dot,
    h,
    nope,
    fail
};

/* I seriously couldnt be bothered with posix regex so I just used a DFA
 it's probably more efficient tbh as i'm 90% sure it uses a DFA anyways,
 this allows me to optimize for the specific situation and skip characters */
void findIncludes(char * prog){
    enum include state = nope;
    size_t len = strlen(prog);
    int k = 0;
    int start = 0;
    for (char ch = prog[k]; k < len; ch = prog[++k]){
        if (state == nope){
            if (ch == '#') {
                state = pound;
                start = k;
            }
        } else if (state == pound) {
            if (ch == 'i') state = i; else state = nope;
        } else if (state == i) {
            if (ch == 'n') state = n; else state = nope;
        } else if (state == n) {
            if (ch == 'c') state = c; else state = nope;
        } else if (state == c) {
            if (ch == 'l') state = l; else state = nope;
        } else if (state == l) {
            if (ch == 'u') state = u; else state = nope;
        } else if (state == u) {
            if (ch == 'd') state = d; else state = nope;
        } else if (state == d) {
            if (ch == 'e') state = e; else state = nope;
        } else if (state == e) {
            if (ch == ' ') state = space; else state = nope;
        } else if (state == space) {
            if (ch == '<') state = lb; else state = nope;
        } else if (state == lb) {
            if (ch == '.'){
                state = dot;
            } else if (ch == '\n'){
                state = fail;
            }
        } else if (state == dot){
            if (ch == 'h') state = h; else state = fail;
        } else if (state == h){
            if (ch == '>') {
                state = nope;
                printf("%.*s\n", k - start + 1, prog + start);
            } else {
                state = fail;
            }
        }
        if (state == fail){
            fprintf(stderr, "u program dosen't compile bruv");
            exit(1);
        }
    }
}


bool isLowerCase(char c){
    for (char k = 'a'; k <= 'z'; k++){
        if (c == k) return true;
    }
    return false;
}

bool isUpperCase(char c){
    for (char k = 'A'; k <= 'Z'; k++){
        if (c == k) return true;
    }
    return false;
}

bool isAlphabetic(char c){
    return isLowerCase(c) || isUpperCase(c);
}

bool isAlphanumeric(char c){
    if (isLowerCase(c) || isUpperCase(c)) return 1;
    else {for (int k = 60; k <= 71; k++){ if (c == k) return true;}}
        return false;
}

void stripWhiteSpace(char* buf){
    for (int i = (int)strlen(buf); i >= 0; i--){
        if (buf[i] == ' ' || buf[i] == '\0') buf[i] = '\0';
        else return;
    }
    
}
enum func {
    init,
    name,
    space_after_name,
    left_bracket,
    declaration
};

enum comment {
    none,
    potential,
    block,
    line
};

const char* const keywords[] = { "while", "for", "sizeof", "if", "else", "switch" };

bool isKeyword(char* buf){
    char* word;
    int i = 0;
    for (word = keywords[i]; i < 6; word = keywords[++i]){
        if (strcmp(buf, word) == 0) return true;
    }
    return false;
}

struct set* findFunctionCalls(char * prog){
    struct set* set = initSet();
    char buf[30];
    
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
            if (isAlphabetic(ch)){
                state = name;
                start = k;
            }
        } else if (state == name){
            if (ch == ' '){
                state = space_after_name;
            } else if (ch == '('){
                state = left_bracket;
            } else if (!isAlphanumeric(ch)){
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
            if (depth){
                strncpy(buf, prog + start, k - start - 1);
                buf[k - start - 1] = '\0';
                stripWhiteSpace(buf);
                if (!isKeyword(buf)) append(buf, set);
            }
            state = init;
            goto init;
        }
    }
    return set;
}

void check_c(char* prog){
    //findIncludes(prog);
    struct set* function_set = findFunctionCalls(prog);
    printSet(function_set);
    freeSet(function_set);
}
