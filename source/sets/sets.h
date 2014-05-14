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
struct set* mergeSets(struct set* set1, struct set* set2);
int setLen(struct set* set);