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

#include <string>
#include <iostream>

#include "csearch.h"

using namespace std;

enum _extern {
    init,
    _extern,
    whitespace,
    post_enum_struct_whitespace,
    typedec,
    post_typedec_whitespace,
    variable_dec
};

set<string> findExterns(string prog){
    set<string> rset;
    enum _extern state = init;
    size_t index = 0;
    int start = 0;
    int length = 1;
    
    while (index != string::npos){
    loop_top:
        // Look for external variables
        if (state == init){

            index = prog.find("extern", index);
            state = _extern;
        } else if (state == _extern){
            index += 6;
            state = whitespace;
        } else if (state == whitespace){
            if (prog[index] == ' '){
                index++;
            } else if (prog[index] == 's' && prog[index+1] == 't' && prog[index+2] == 'r'
                       && prog[index+3] == 'u' && prog[index+4] == 'c' && prog[index+5] == 't'){
                index += 6;
                //state = post_enum_struct_whitespace;
            } else if (prog[index] == 'e' && prog[index+1] == 'n'
                       && prog[index+2] == 'u' && prog[index+3] == 'm'){
                index += 4;
                //state = post_enum_struct_whitespace;
            } else if (validInitialIndentifierChar(prog[index])){
                state = typedec;
            } else {
                state = init;
            }
        } else if (state == typedec){
            if (validIndentifierChar(prog[index])){
                index++;
            } else if (prog[index] == ' ') {
                state = post_typedec_whitespace;
                index++;
            }
        } else if (state == post_typedec_whitespace){
            if (prog[index] == ' ' || prog[index] == '*'){
                index++;
            } else if (validInitialIndentifierChar(prog[index])){
                start = ++index;
                state = variable_dec;
            }
        } else if (state == variable_dec){
            std::cout << prog[index] << '\n';
            if (validIndentifierChar(prog[index])){
                length++;
                index++;
            } else if (prog[index] == ' ' || prog[index] == '\n' || prog[index] == '\t'){
                rset.insert(prog.substr(start, length));
                length = 1;
                state = init;
                goto loop_top;
            }
        }
    }
    
    

    
    return rset;
}