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

void append(char* data, struct set* set){
    if (set->head == NULL){
        set->head = malloc(sizeof(struct set_node));
        set->head->next = NULL;
        set->head->prev = NULL;
        set->head->data = malloc(strlen(data));
        strcpy(set->head->data, data);
    } else if (set->tail == NULL){
        int x = strcmp(set->head->data, data);
        if (x != 0){
            set->tail = malloc(sizeof(struct set_node));
            set->tail->next = NULL;
            set->tail->prev = set->head;
            set->head->next = set->tail;
            set->tail->data = malloc(strlen(data));
            strcpy(set->tail->data, data);
        }
    } else {
        for (struct set_node* n = set->head; n != NULL; n = n->next){
            if (strcmp(n->data, data) == 0) return;
        }
        set->tail->next = malloc(sizeof(struct set_node));
        set->tail->next->prev = set->tail;
        set->tail = set->tail->next;
        set->tail->next = NULL;
        set->tail->data = malloc(strlen(data));
        strcpy(set->tail->data, data);
    }
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
