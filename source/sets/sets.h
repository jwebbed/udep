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
#define mergeSets(setone, settwo) mergeNSets(2, (setone), (settwo))
struct set* mergeNSets(int count, ...);
int setLen(struct set* set);
struct set* setcpy(struct set* set1);
struct set_node* linSearch(struct set* set, char * data);
struct set* uniqueSet(struct set* set1, struct set* set2);
