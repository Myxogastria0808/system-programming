#include <stdio.h>
#include <stdlib.h>
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

int main(void) {
    char buf5[5];
    char buf20[20];
    char *s1 = "01234567890";
    int len;

    // size_t strlcpy(char *dst, const char *src, size_t size);
    // 1. strlcpy は src の文字列を dst にコピーする．
    // 2. size_t はコピー先 dst のサイズを表す．
    // 3. strlcpy の戻り値は src の文字列の長さ strlen(src).
    // 4. dst の末尾にヌル文字 \0 を追加する．
    len = strlcpy(buf5, s1, sizeof(buf5));
    printf(
        "copy to buf5:  s1=\"%s\", len-s1=%d, str-in-buf=\"%s\", "
        "len-str-in-buf=%ld\n",
        s1, len, buf5, strlen(buf5));

    len = strlcpy(buf20, s1, sizeof(buf20));
    printf(
        "copy to buf20: s1=\"%s\", len-s1=%d, str-in-buf=\"%s\", "
        "len-str-in-buf=%ld\n",
        s1, len, buf20, strlen(buf20));

    len = my_strlcpy(buf5, s1, sizeof(buf5));
    printf(
        "copy to buf5:  s1=\"%s\", len-s1=%d, str-in-buf=\"%s\", "
        "len-str-in-buf=%ld\n",
        s1, len, buf5, strlen(buf5));

    len = my_strlcpy(buf20, s1, sizeof(buf20));
    printf(
        "copy to buf20: s1=\"%s\", len-s1=%d, str-in-buf=\"%s\", "
        "len-str-in-buf=%ld\n",
        s1, len, buf20, strlen(buf20));

    // char *strdup(const char *s); /* 文字列の複製 */
    // 1. 関数の内部で動的にメモリ領域を確保する
    char *s2 = strdup(s1);
    if (s2 == NULL) {
        perror("strdup failed");
        return 1;
    }
    printf(
        "s2=\"%s\", len-s1=%ld, str-in-s2=\"%s\", "
        "len-str-in-s2=%ld\n",
        s2, strlen(s2), s2, strlen(s2));
    free(s2);

    char *s3 = my_strdup(s1);
    if (s3 == NULL) {
        perror("strdup failed");
        return 1;
    }
    printf(
        "s3=\"%s\", len-s1=%ld, str-in-s3=\"%s\", "
        "len-str-in-s3=%ld\n",
        s3, strlen(s3), s3, strlen(s3));
    free(s3);

    // 実験
    // char buf[1];
    // len = strlcpy(buf, s1, sizeof(buf));
    // printf(
    //     "copy to buf: s1=\"%s\", len-s1=%d, str-in-buf=\"%s\", "
    //     "len-str-in-buf=%ld\n",
    //     s1, len, buf, strlen(buf));

    return 0;
}
