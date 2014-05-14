#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sets/sets.h"
#include "csearch.h"

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
struct set* findIncludes(char * prog){
    struct set* set = initSet();
    char buf[BUF_SIZE];
    
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
                //printf("%.*s\n", k - start + 1, prog + start);
                strncpy(buf, prog + start + 9, k - start - 8);
                buf[k - start - 8] = '\0';
                appendString(buf, set);
            } else {
                state = fail;
            }
        }
        if (state == fail){
            fprintf(stderr, "ur program dosen't compile bruv");
            exit(1);
        }
    }
    return set;
}


include includeInit(char* name){
    include inc;
    if (name[0] == '<')
        inc.type = global;
    else if (name[0] == '"')
        inc.type = local;
    inc.name = calloc(strlen(name) - 1, 0);
    strncpy(inc.name, name + 1, strlen(name) - 2);
    return inc;
}