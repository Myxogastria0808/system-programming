#include <stdio.h>  /* fprintf() */
#include <stdlib.h> /* exit() */
#include <string.h> /* strcmp() */

extern int http_receive_request(FILE *in, char *filename, size_t size);
extern char *chomp(char *str);
extern int string_split(char *str, char del, int *countp, char ***vecp);
extern void free_string_vector(int qc, char **vec);
extern int countchr(char *s, char c);

#define BUFFERSIZE 1024

int main(int argc, char *argv[]) {
    char filename[BUFFERSIZE];
    int res;

    if (argc != 1) {
        fprintf(stderr, "Usage: %s < request-filename\n", argv[0]);
        exit(1);
    }
    res = http_receive_request(stdin, filename, BUFFERSIZE);
    if (res)
        printf("filename is [%s].\n", filename);
    else
        printf("Bad request.\n");
}

int http_receive_request(FILE *in, char *filename, size_t size) {
    char requestline[BUFFERSIZE];
    char rheader[BUFFERSIZE];

    snprintf(filename, size, "NOFILENAME");
    if (fgets(requestline, BUFFERSIZE, in) <= 0) {
        printf("No request line.\n");
        return (0);
    }

    // validation of requestline
    // 1. if the requestline contains '<' or '..', it's dangerous
    if (strchr(requestline, '<') || strstr(requestline, "..")) {
        fprintf(stderr, "Dangerous request line found.\n");
        return (0);
    }
    // 2. split the requestline
    int count;
    char **vec;
    chomp(requestline); /* remove \r\n */
    if (string_split(requestline, ' ', &count, &vec) < 0) {
        perror("string_split-malloc");
        exit(1);
    }
    // 3. if the count is not 3, it's a bad request
    if (count != 3) {
        fprintf(stderr, "Expected 3 parts, got %d.\n", count);
        free_string_vector(count, vec);
        return (0);
    }
    // 4. if the first part is not "GET", it's a bad request
    if (strcmp(vec[0], "GET") != 0) {
        fprintf(stderr, "Expected 'GET', got '%s'.\n", vec[0]);
        free_string_vector(count, vec);
        return (0);
    }
    // 5. if the last part is not "HTTP/1.0" or "HTTP/1.1", it's a bad request
    if (strcmp(vec[2], "HTTP/1.0") != 0 && strcmp(vec[2], "HTTP/1.1") != 0) {
        fprintf(stderr, "Expected 'HTTP/1.0' or 'HTTP/1.1', got '%s'.\n",
                vec[2]);
        // free
        free_string_vector(count, vec);
        return (0);
    }

    printf("requestline is [%s]\n", requestline);
    while (fgets(rheader, BUFFERSIZE, in)) {
        chomp(rheader); /* remove \r\n */
        if (strcmp(rheader, "") == 0) break;
        printf("Ignored: %s\n", rheader);
    }
    if (strchr(requestline, '<') || strstr(requestline, "..")) {
        printf("Dangerous request line found.\n");
        return (0);
    }
    // 6. copy the second part to filename
    snprintf(filename, size, "%s", vec[1]);
    // 7. free
    free_string_vector(count, vec);
    // 8. return 1 to indicate success
    return (1);
}

char *chomp(char *str) {
    int len;

    len = strlen(str);
    if (len >= 2 && str[len - 2] == '\r' && str[len - 1] == '\n') {
        str[len - 2] = str[len - 1] = 0;
    } else if (len >= 1 && (str[len - 1] == '\r' || str[len - 1] == '\n')) {
        str[len - 1] = 0;
    }
    return (str);
}

int string_split(char *str, char del, int *countp, char ***vecp) {
    char **vec;
    int count_max, i, len;
    char *s, *p;

    if (str == 0) return (-1);
    count_max = countchr(str, del) + 1;
    vec = malloc(sizeof(char *) * (count_max + 1));
    if (vec == 0) return (-1);

    for (i = 0; i < count_max; i++) {
        while (*str == del) str++;
        if (*str == 0) break;
        for (p = str; *p != del && *p != 0; p++) continue;
        /* *p == del || *p=='\0' */
        len = p - str;
        s = malloc(len + 1);
        if (s == 0) {
            int j;
            for (j = 0; j < i; j++) {
                free(vec[j]);
                vec[j] = 0;
            }
            free(vec);
            return (-1);
        }
        memcpy(s, str, len);
        s[len] = 0;
        vec[i] = s;
        str = p;
    }
    vec[i] = 0;
    *countp = i;
    *vecp = vec;
    return (i);
}

void free_string_vector(int qc, char **vec) {
    int i;
    for (i = 0; i < qc; i++) {
        if (vec[i] == NULL) break;
        free(vec[i]);
    }
    free(vec);
}

int countchr(char *s, char c) {
    int count;
    for (count = 0; *s; s++)
        if (*s == c) count++;
    return (count);
}
