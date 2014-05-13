struct set* findIncludes(char * prog);
struct set* findFunctionCalls(char * prog);
struct set* findEnums(char* prog);
struct set* findStructs(char* prog);
int getHeader(char** file, char* header);