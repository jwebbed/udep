#include "sets/sets.h"

// c_set declarations
typedef struct {
    char * name;
    struct set* function_set;
    struct set* struct_set;
    struct set* enum_set;
    struct set* include_set;
} c_set;

c_set* getDeclarations(char* header);
c_set* mergeCSet(c_set *set1, c_set *set2);
c_set* initCSet();
c_set* csetcpy(c_set *set);
void freeCSet(c_set *set);
void setname(c_set *set, char * name);

// c_map declarations
typedef struct set c_map;
extern c_map* header_map;
#define initCMap() initSet()
void appendCSet(c_map *map, c_set *set);
c_set * getCSet(c_map *map, char* name);
void freeCMap(c_map* map);