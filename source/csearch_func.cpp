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
#include <string.h>

#include "csearch.h"

using namespace std;

enum func {
    init,
    name,
    space_after_name,
    left_bracket,
    declaration
};

const char* keywords[] = { "while", "for", "sizeof", "if", "else", "switch" };

bool isKeyword(char* buf){
    const char* word;
    int i = 0;
    for (word = keywords[i]; i < 6; word = keywords[++i]){
        if (strcmp(buf, word) == 0)
            return true;
    }
    return false;
}

set<string>* _findFunctionCalls(char * prog, int header){
    set<string> *set = new std::set<string>;
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
                if (!isKeyword(buf))
                    set->insert(string(buf));
            }
            state = init;
            goto init;
        }
    }
    return set;
}