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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_checker.h"


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
