#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sets.h"

struct set* initSet(){
    struct set* set = malloc(sizeof(struct set));
    set->head = NULL;
    set->tail = NULL;
    return set;
}

struct set_node* initNode(){
    struct set_node* node = malloc(sizeof(struct set_node));
    node->data = NULL;
    node->meta = NULL;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


int append(struct set_node* node, struct set* set){
    if (set->head == NULL){
        set->head = node;
        return 1;
    } else if (set->tail == NULL){
        int x = strcmp(set->head->data, node->data);
        if (x != 0){
            set->tail = node;
            set->tail->prev = set->head;
            set->head->next = set->tail;
            return 1;
        }
    } else if (!nodeInSet(node, set)){
        set->tail->next = node;
        set->tail->next->prev = set->tail;
        set->tail = set->tail->next;
        return 1;
    }
    return 0;
}

void appendString(char* data, struct set* set){
    struct set_node* node = initNode();
    node->data = malloc(strlen(data));
    strcpy(node->data, data);
    if(!append(node, set)) free(node);
}

void _freeSet(struct set_node* node){
    if (node == NULL) return;
    _freeSet(node->next);
    free(node);
}

void freeSet(struct set* set){
    _freeSet(set->head);
    free(set);
}

void _printSet(struct set_node* node){
    if (node == NULL) return;
    printf("%s\n", node->data);
    _printSet(node->next);
}

void printSet(struct set* set){
    _printSet(set->head);
}

struct set_node* nodecpy(struct set_node* node){
    struct set_node* node_copy = initNode();
    if (node->data != NULL){
        node_copy->data = malloc(strlen(node->data));
        strcpy(node_copy->data, node->data);
    } else {
        node_copy->data = NULL;
    }
    if (node->meta != NULL){
        node_copy->meta = malloc(strlen(node->meta));
        strcpy(node_copy->meta, node->meta);
    } else {
        node_copy->meta = NULL;
    }
    return node_copy;
}

int nodeInSet(struct set_node* node, struct set* set){
    for (struct set_node* n = set->head; n != NULL; n = n->next)
        if (strcmp(n->data, node->data) == 0)
            return 1;
    return 0;
}

struct set* setUnion(struct set* set1, struct set* set2){
    struct set* un = initSet();
    for (struct set_node* n = set1->head; n != NULL; n = n->next)
        if (nodeInSet(n, set2))
            append(nodecpy(n), un);
    return un;
}
