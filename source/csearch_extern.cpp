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
    string buf;
    enum _extern state = init;
    size_t index = 0;
    size_t length = prog.length();
    int start = 0;
    
    
    while (index != string::npos){
        index = prog.find("extern", index);
        if (index != string::npos){
            start = index;
            index = prog.find(";", index);
            if (index != string::npos){
                buf = prog.substr(start, index - start);
                {
                    size_t lasti = 0;
                    size_t i = 0;
                    while (i != string::npos){
                        i = buf.find(" ", i + 1);
                        if (i != string::npos)
                            lasti = i;
                        else
                            break;
                    }
                    cout << buf.substr(lasti, lasti - i) << "\n";
                    rset.insert(buf.substr(lasti, lasti - i));
                }
            }
        }
    

    }
    return rset;
}