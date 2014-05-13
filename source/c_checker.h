typedef struct {
    struct set* function_set;
    struct set* struct_set;
    struct set* enum_set;
} c_set;


int getHeader(char** file, char* header);
c_set mergeCSet(c_set set1, c_set set2);
