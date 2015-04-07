/*
 * Create a SHA256 hex digest from a string.
 * 65-byte string is malloc'd by this function. The caller must free it.
 * When compiling, link to:  -l ssl -l crypto
 */
char *sha256(const char *str, int length);
