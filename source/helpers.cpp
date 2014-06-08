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

#include "helpers.h"

/*
 This is the fundamental algorithm that should be used by all modules.
 As such I will try and make in as module independant as possible for
 maximum reusability and so I can continue to make it as optimal as possible.
 
 Min Subset of Set Problem
 -------------------------
 Input: 
 Set of Elements, Map of Sets which all together include all the elements
 in the first set at least once
 
 Output:
 The minimal set of sets needed from the input map of sets that could be used to construct teh
 first set
 
 Algorithm:
 1. Loop over all sets in the map of sets
    a. Loop over elements inside set
        i. remove any instance of element from other sets
        ii. check if element is inside input set, if yes, mark this set as needed and skip this step in the future
 2. Find key of all the sets marked as needed and add them to a set
 3. Return aforementioned set


*/

std::set<std::string> minSubset(std::set<std::string> iset, std::map<std::string, std::set<std::string>> imap){
    for (auto top = imap.begin(); top != imap.end(); top++) {
        // iterator->first = key
        // iterator->second = value
        // Repeat if you also want to iterate through the second map.
        auto next = top;
        next++;
        for(auto node = next; node != imap.end(); node++){
            for (std::string str : top->second){
                if (node->second.find(str) != node->second.end()){
                    node->second.erase(str);
                }
            }
        }
    }
    
    // so it will compile
    return iset;

}
