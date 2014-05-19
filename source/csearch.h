#include <stdbool.h>
#include "cset.h"

//#include "c_checker.h"

// Function Call Finders
struct set* _findFunctionCalls(char * prog, int header);
#define findFunctionCalls(prog) _findFunctionCalls((prog), 0)
#define findFunctionDeclarations(prog) _findFunctionCalls((prog), 1)

struct set* findIncludes(char * prog);
struct set* findDefines(char * prog);
struct set* findEnumStructs(char* prog, const char* es);
#define findStructs(prog) findEnumStructs((prog), "struct")
#define findEnums(prog) findEnumStructs((prog), "enum")

typedef enum {
    local,
    global
} include_type;

typedef struct {
    char* name;
    include_type type;
    c_set* complete_set;
    c_set* unique_set;
    bool used;
} include;

include includeInit(char* name);

// Internal

#define isAlphabetic(c) (isLowerCase(c) || isUpperCase(c))
#define validInitialIndentifierChar(c) (isAlphabetic((c)) || (c) == '_')
#define validIndentifierChar(c) (isAlphanumeric(c) || (c) == '_')
#define BUF_SIZE 100

bool isUpperCase(char c);
bool isLowerCase(char c);
bool isAlphanumeric(char c);
void stripWhiteSpace(char* buf);

enum comment {
    none,
    potential,
    block,
    line
};
