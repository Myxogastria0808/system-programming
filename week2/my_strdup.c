#include <string.h>

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *new_str = malloc(len + 1);
    //  validate about creating malloc
    if (new_str == NULL) {
        return NULL;
    }
    // copy
    for (size_t i = 0; i <= len; i++) {
        new_str[i] = s[i];
        // set null the end of the new string
        if (i == len) {
            new_str[i] = '\0';
        }
    }
    return new_str;
}
