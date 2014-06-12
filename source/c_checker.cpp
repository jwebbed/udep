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

#include <map>
#include <iostream>

#include "c_checker.h"
#include "csearch.h"
#include "Program.h"
#include "helpers.h"

void Program::check_c(){
    c_set set = c_set((char*)removeComments(this->prog).c_str());
    /*
    set.printSet();
    std::cout << '\n';
     */
    
    std::set<std::string> allset, usedset, mset, fset, eset, sset, nset;
    std::map<std::string, c_set> header_map;
    std::string name;
    for (auto i : set.include_set){
        if (i[0] == '<'){
            name = i.substr(1, (i.length() - 2));
            header_map[name] = getDeclarations(name);
            allset.insert(name);
        }
    }
    
    std::map<std::string, std::set<std::string>> fmap, emap, smap;
    for (auto node : header_map){
        fmap[node.first] = node.second.function_set;
        emap[node.first] = node.second.enum_set;
        smap[node.first] = node.second.struct_set;
    }
    
    fset = minSubset(set.function_set, fmap);
    eset = minSubset(set.enum_set, emap);
    sset = minSubset(set.struct_set, smap);
    
    mset.insert(fset.begin(), fset.end());
    mset.insert(eset.begin(), eset.end());
    mset.insert(sset.begin(), sset.end());
    
    nset = uniqueSubset(allset, mset);
    
    /*
     Go through all the unused headers and check if they have
     any external variables. If they do then check if it's used
     in the program
     */
    
    std::cout << "unused headers" << '\n' << "-------------" << '\n';
    for (auto c : nset){
        std::cout << c << '\n';
    }
    
    delete total_header_map;
}

