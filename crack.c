#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "md5.h"

const int PASS_LEN=20;        
const int HASH_LEN=33;        


int tryguess(char *hash, char *guess)
{
    int guess_length = strlen(guess);
    char *hashed_guess = md5(guess, guess_length);
    if(!strcmp(hash, hashed_guess)){
        free(hashed_guess);
        return 1;
    } else {
        free(hashed_guess);
        return 0;
    }
}


off_t file_length (char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1) return -1;
    return info.st_size;
}


char **read_dictionary(char *filename, int *size) {
    *size = 0;
    
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Could not open %s for reading.\n", filename);
        exit(1);
    }
    
    int length = file_length(filename);
    char *contents = malloc(length);
    fread(contents, sizeof(char), length, f);
    fclose(f);
    
    for (int i = 0; i < length; i++) {
        if (*(contents + i) == '\n') {
            *(contents + i) = '\0';
            *size = *size + 1;
        }
    }
    
    char **strings = malloc(*size * sizeof(char *));
    
    int count = 0;
    *strings = contents;
    
    for (int i = 1; i < length; i++) {
        if (*(contents + i) == '\0'){
            count = count + 1;
            if (count > (*size - 1)) break;
            *(strings + count) = contents + i + 1;
        }
    }
    
    return strings;
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    int dlen;
    char **dict = read_dictionary(argv[2], &dlen);
    
    FILE *hashes = fopen(argv[1], "r");
    if (!hashes) {
        printf ("Could not open %s for reading.\n", argv[1]);
        exit(1);
    }
    
    char hash[HASH_LEN];
    while (fgets(hash, HASH_LEN, hashes) != NULL) {
        for (int i = 0; i < dlen; i++) {
            char *temp = dict[i];
            if (tryguess(hash, temp)) {
                printf ("%s | %s\n", hash, temp);
            }
        }
    }
    free(*dict);
    free (dict);
    fclose (hashes);
}