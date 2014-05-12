#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t syswrite(int fildes, const void *buf, size_t nbytes){
    long size;
    if ((size = write(fildes, buf, nbytes)) < 0){
        fprintf(stderr, "write");
        exit(1);
    }
    return size;
}