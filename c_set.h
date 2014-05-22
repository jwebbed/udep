//
//  c_set.h
//  udep
//
//  Created by Jonathan Webb on 2014-05-22.
//  Copyright (c) 2014 Jonathan Webb. All rights reserved.
//

#ifndef __udep__c_set__
#define __udep__c_set__

#include <iostream>
#include <set>


#endif /* defined(__udep__c_set__) */

class c_set {
public:
    std::string name;
    std::set<std::string> function_set;
    std::set<std::string> struct_set;
    std::set<std::string> enum_set;
    std::set<std::string> include_set;
    c_set (char * prog);
};