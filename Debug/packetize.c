#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#include "data.h"

FILE *logfp = NULL;


/* Read a file, break it into packets.*/

/* Notes:
 * getopt is a useful library function to make it easier to read in command line arguments, 
 * especially those with options. Read the man page (man 3 getopt) for more information.
 */

int main(int argc, char *argv[]) {
    FILE *infp = stdin;
    FILE *outfp = NULL;
    char opt;
    extern int optind;
    extern char *optarg;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                infp = fopen(optarg, "r");
                if(!infp) {
                    perror("fopen");
                    exit(1);
                }
                break;
               default: /* '?' */
                   fprintf(stderr, "Usage: %s [-f inputfile ] outputfile\n",
                           argv[0]);
                   exit(1);
               }
           }
     if(optind >= argc) {
        fprintf(stderr, "Expected outputfile name\n");
        exit(1);
     }

     if(!(outfp = fopen(argv[optind], "w"))){
        perror("fopen");
        exit(1);
     }

     /* The files have been opened for you.  Write the rest of the program here.*/
    if(fseek(infp, 0, SEEK_END)){
        perror("fseek");
        exit(1);
    }
    unsigned long final_size = ftell(infp);
    if (final_size == -1L){
        perror("ftell");
        exit(1);
    }
    rewind(infp);
    while (final_size > 256){
        final_size -= 256;
    }
    
    struct packet *current = malloc(sizeof(struct packet));
    if (current == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }
    unsigned short i = 0;
    unsigned long size;
    unsigned char *chunk = malloc(MAXSIZE);
    if (chunk == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }
    
    while (true){
        size = fread(chunk, 1, MAXSIZE, infp);
        if (ferror(infp)){
            perror("fread failed");
            exit(1);
        }
        current->payload = chunk;
        current->block_size = size;
        current->crc = crc_message(XMODEM_KEY, chunk, size);
        current->block_num = i++;
        
        fwrite(current, sizeof(struct packet), 1, outfp);
        if (ferror(outfp)){
            perror("fwrite failed");
            exit(1);
        }
        fwrite(chunk, size, 1, outfp);
        if (ferror(outfp)){
            perror("fwrite failed");
            exit(1);
        }
        if (size != 256){
            break;
        }
    }
    
    free(current);
    free(chunk);
    
    if (fclose(infp)){
        perror("Failed to close input file");
        exit(1);
    }
    if (fclose(outfp)){
        perror("Failed to close output file");
        exit(1);
    }
    
    return 0;
}
