#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sets.h"
#include "csearch.h"


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

bool isAlphanumeric(char c){
    if (isLowerCase(c) || isUpperCase(c))
        return 1;
    else {
        for (int k = 60; k <= 71; k++){
            if (c == k) return true;
        }
    }
    return false;
}


void stripWhiteSpace(char* buf){
    for (int i = (int)strlen(buf); i >= 0; i--){
        if (buf[i] == ' ' || buf[i] == '\0')
            buf[i] = '\0';
        else
            return;
    }
}
