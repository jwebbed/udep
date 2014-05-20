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

struct set_node{
    struct set_node* next;
    struct set_node* prev;
    char* data;
    void* meta;
};

struct set{
    struct set_node* head;
    struct set_node* tail;
};

struct set* initSet();
struct set_node* appendString(char* data, struct set* set);
void freeSet(struct set* set);
void printSet(struct set* set);
int nodeInSet(struct set_node* node, struct set* set);
#define mergeSets(set1, set2) mergeNSets(2, (set1), (set2))
struct set* mergeNSets(int count, ...);
int setLen(struct set* set);
struct set* setcpy(struct set* set1);
struct set_node* linSearch(struct set* set, char * data);
struct set* uniqueSet(struct set* set1, struct set* set2);
