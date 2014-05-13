// Function Call Finders
struct set* _findFunctionCalls(char * prog, int header);
#define findFunctionCalls(prog) _findFunctionCalls((prog), 0)
#define findFunctionDeclarations(prog) _findFunctionCalls((prog), 1)

struct set* findIncludes(char * prog);
struct set* findEnums(char* prog);
struct set* findStructs(char* prog);
int getHeader(char** file, char* header);

typedef struct c_set {
    struct set* function_set;
    struct set* struct_set;
    struct set* enum_set;
};