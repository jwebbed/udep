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

#include "c_set.h"
#include "csearch.h"

c_set::c_set(){
    
}

c_set::c_set(char* prog){
    this->function_set = findFunctionCalls(prog);
    this->struct_set = findStructs(std::string(prog));
    this->enum_set = findEnums(std::string(prog));
    this->include_set = findIncludes(prog);
}

c_set::c_set(char* prog, char* name){
    this->name = std::string(name);
    this->function_set = findFunctionCalls(prog);
    this->struct_set = findStructs(prog);
    this->enum_set = findEnums(prog);
    this->include_set = findIncludes(prog);
}

c_set::c_set(char * prog, std::string name){
    this->name = name;
    this->function_set = findFunctionCalls(prog);
    this->struct_set = findStructs(std::string(prog));
    this->enum_set = findEnums(std::string(prog));
    this->include_set = findIncludes(prog);
}

c_set::c_set(c_set *set){
    this->name = set->name;
    this->function_set = std::set<std::string>(set->function_set);
    this->struct_set = std::set<std::string>(set->struct_set);
    this->enum_set = std::set<std::string>(set->enum_set);
    this->include_set = std::set<std::string>(set->include_set);
}

void c_set::merge(c_set set){
    this->function_set.insert(set.function_set.begin(), set.function_set.end());
    this->struct_set.insert(set.struct_set.begin(), set.struct_set.end());
    this->enum_set.insert(set.enum_set.begin(), set.enum_set.end());
    this->include_set.insert(set.include_set.begin(), set.include_set.end());
}

void c_set::printSet(){
    std::cout << "function set\n";
    std::cout << "------------\n";
    for (auto i : this->function_set){
        std::cout << i << '\n';
    }
    
    std::cout << '\n';
    std::cout << "struct set\n";
    std::cout << "------------\n";
    for (auto i : this->struct_set){
        std::cout << i << '\n';
    }
    
    std::cout << '\n';
    std::cout << "enum set\n";
    std::cout << "------------\n";
    for (auto i : this->enum_set){
        std::cout << i << '\n';
    }
    
    std::cout << '\n';
    std::cout << "include set\n";
    std::cout << "------------\n";
    for (auto i : this->include_set){
        std::cout << i << '\n';
    }
    
    
}
