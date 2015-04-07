#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

char *sha256(const char *str, int length) {
    int n;
    SHA256_CTX c;
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char *out = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);

    SHA256_Init(&c);

    while (length > 0) {
        if (length > 512) {
            SHA256_Update(&c, str, 512);
        } else {
            SHA256_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    SHA256_Final(digest, &c);

    for (n = 0; n < SHA256_DIGEST_LENGTH; ++n) {
        snprintf(&(out[n*2]), SHA256_DIGEST_LENGTH*2, "%02x", (unsigned int)digest[n]);
    }

    out[SHA256_DIGEST_LENGTH * 2] = '\0';

    return out;
}
