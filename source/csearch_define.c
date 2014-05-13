#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sets/sets.h"
#include "csearch.h"

enum declare {
    pound,
    d,
    e,
    f,
    i,
    n,
    _e,
    space,
    declaration,
    end,
    nope
};

/* I seriously couldnt be bothered with posix regex so I just used a DFA
 it's probably more efficient tbh as i'm 90% sure it uses a DFA anyways,
 this allows me to optimize for the specific situation and skip characters */

/* This does not work /shrug
struct set* findDeclares(char * prog){
    struct set* set = initSet();
    char buf[BUF_SIZE];
    
    enum declare state = nope;
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
            if (ch == 'd') state = d; else state = nope;
        } else if (state == d) {
            if (ch == 'e') state = e; else state = nope;
        } else if (state == e) {
            if (ch == 'f') state = f; else state = nope;
        } else if (state == f) {
            if (ch == 'i') state = i; else state = nope;
        } else if (state == i) {
            if (ch == 'n') state = n; else state = nope;
        } else if (state == n) {
            if (ch == 'e') state = _e; else state = nope;
        } else if (state == _e) {
            if (ch == ' ') state = space; else state = nope;
        } else if (state == space) {
            if (validIndentifierChar(ch) || ch == '$') state = declaration; else state = nope;
        } else if (state == declaration) {
            
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
} */
