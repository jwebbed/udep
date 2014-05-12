struct set_node{
    struct set_node* next;
    struct set_node* prev;
    char* data;
    char* meta;
};

struct set{
    struct set_node* head;
    struct set_node* tail;
};

struct set* initSet();
void appendString(char* data, struct set* set);
void freeSet(struct set* set);
void printSet(struct set* set);
int nodeInSet(struct set_node* node, struct set* set);