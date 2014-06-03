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

#ifndef __udep__c_set__
#define __udep__c_set__

#include <iostream>
#include <set>

class c_set {
public:
    std::string name;
    std::set<std::string> function_set;
    std::set<std::string> struct_set;
    std::set<std::string> enum_set;
    std::set<std::string> include_set;
    c_set ();
    c_set (char * prog);
    c_set (char * prog, char * name);
    c_set (char * prog, std::string name);
    c_set (c_set *set);
    void merge(c_set set);
    void printSet();
};

#endif /* defined(__udep__c_set__) */