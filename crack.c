#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN=20;        // Maximum any password will be
const int HASH_LEN=33;        // Length of MD5 hash strings

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Hash the guess using MD5

    // Compare the two hashes

    // Free any malloc'd memory

    return 0;
}

// Read in the dictionary file and return the array of strings
// and store the length of the array in size.
// This function is responsible for opening the dictionary file,
// reading from it, building the data structure, and closing the
// file.
char **read_dictionary(char *filename, int *size)
{
    *size = 0;
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Read the dictionary file into an array of strings.
    int dlen;
    char **dict = read_dictionary(FILL THIS IN);

    // Open the hash file for reading.
    

    // For each hash, try every entry in the dictionary.
    // Print the matching dictionary entry.
    // Need two nested loops.
}
