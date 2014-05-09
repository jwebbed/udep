void check_c(char* prog);

enum language {
    c
};

#ifdef _WIN32
	#define OS 0
#elif __APPLE__ 
	#define OS 1
#else 
	#define OS 2
#endif

#define WINDOWS 0
#define OSX 1
#define OTHER 2
