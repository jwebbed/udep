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

#include "csearch.h"
using namespace std;

enum _struct {
    initial,
    _space,
    enum_struct,
    _typedef
};

set<string> findEnumStructs(string prog, const string es){
    set<string> set;
    string buf;
    
    size_t s_len = es.length();
    
    enum _struct state = initial;
    enum comment comment = none;
    int depth = 0;
    int whitespace = 0;
    
    size_t len = prog.length();
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
        
        if (state == initial && (prog.substr(k, es.length()) == es)){
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
            buf = prog.substr(start, k - start);
            set.insert(buf);
            state = initial;
        }
    }
    
    return set;
}
