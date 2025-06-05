#include <string.h>

size_t my_strlcpy(char *dst, const char *src, size_t size) {
    // get src length
    size_t src_len = strlen(src);
    // copy up to size - 1 characters from src to dst
    size_t actual_size = size - 1;
    for (size_t i = 0; i < actual_size; i++) {
        dst[i] = src[i];
    }
    // set null the end of the destination string
    dst[actual_size] = '\0';

    return src_len;
}
