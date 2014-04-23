struct set_node{
    struct set_node* next;
    struct set_node* prev;
    char* data;
};

struct set{
    struct set_node* head;
    struct set_node* tail;
};

struct set* initSet();
void append(char* data, struct set* set);
void freeSet(struct set* set);
void printSet(struct set* set);