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

#ifndef udep_csearch_h
#define udep_csearch_h

#include <set>
#include <string>

std::set<std::string> _findFunctionCalls(std::string prog, int header);
#define findFunctionCalls(prog) _findFunctionCalls((prog), 0)
#define findFunctionDeclarations(prog) _findFunctionCalls((prog), 1)

std::set<std::string> findExterns(std::string prog);
std::set<std::string> findIncludes(std::string prog);
std::set<std::string> findEnumStructs(std::string prog, const std::string es);
#define findStructs(prog) findEnumStructs((prog), "struct")
#define findEnums(prog) findEnumStructs((prog), "enum")

#define isAlphabetic(c) (isLowerCase(c) || isUpperCase(c))
#define validInitialIndentifierChar(c) (isAlphabetic((c)) || (c) == '_')
#define validIndentifierChar(c) (isAlphanumeric(c) || (c) == '_')
#define BUF_SIZE 100

bool isUpperCase(char c);
bool isLowerCase(char c);
bool isAlphanumeric(char c);
std::string trimTrailingWhitespace(std::string str);
std::string removeComments(std::string prog);

enum comment {
    none,
    potential,
    block,
    line
};

#endif
