#include <stdbool.h>

// Function Call Finders
struct set* _findFunctionCalls(char * prog, int header);
#define findFunctionCalls(prog) _findFunctionCalls((prog), 0)
#define findFunctionDeclarations(prog) _findFunctionCalls((prog), 1)

struct set* findIncludes(char * prog);
struct set* findEnums(char* prog);
struct set* findStructs(char* prog);
struct set* findDefines(char * prog);

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
