#include <netdb.h>      /* getaddrinfo() */
#include <netinet/in.h> /* struct sockaddr_in */
#include <stdio.h>
#include <stdlib.h>     /* exit() */
#include <string.h>     /* memset(), memcpy() */
#include <string.h>     /* strlen() */
#include <sys/socket.h> /* socket() */
#include <sys/types.h>  /* socket() */
#include <unistd.h>     /* close() */

extern int http_client_one(char *server, int port, char *file_path);
extern int http_send_request(FILE *out, char *server, char *file_path);
extern int http_receive_response(FILE *in, char buf[], int size);
extern int tcp_connect(char *server, int portno);
extern int fdopen_sock(int sock, FILE **inp, FILE **outp);

//* network functions *//
#define PORTNO_BUFSIZE 30

int tcp_connect(char *server, int portno) {
    struct addrinfo hints, *ai, *p;
    char portno_str[PORTNO_BUFSIZE];
    int s = 0;
    int err = 0;
    snprintf(portno_str, sizeof(portno_str), "%d", portno);
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    if ((err = getaddrinfo(server, portno_str, &hints, &ai))) {
        fprintf(stderr, "unknown server %s (%s)\n", server, gai_strerror(err));
        goto error0;
    }
    for (p = ai; p; p = p->ai_next) {
        if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
            perror("socket");
            goto error1;
        }
        if (connect(s, p->ai_addr, p->ai_addrlen) >= 0) {
            break;
        } else {
            close(s);
        }
    }
    freeaddrinfo(ai);
    return (s);
error1:
    freeaddrinfo(ai);
error0:
    return EXIT_FAILURE;
}

int fdopen_sock(int sock, FILE **inp, FILE **outp) {
    int sock2;
    if ((sock2 = dup(sock)) < 0) {
        return EXIT_FAILURE;
    }
    if ((*inp = fdopen(sock2, "r")) == NULL) {
        close(sock2);
        return EXIT_FAILURE;
    }
    if ((*outp = fdopen(sock, "w")) == NULL) {
        fclose(*inp);
        *inp = 0;
        return EXIT_FAILURE;
    }
    setvbuf(*outp, (char *)NULL, _IONBF, 0);
    return (EXIT_SUCCESS);
}

//* http functions *//
#define BUFFERSIZE 1024

int http_client_one(char *server, int port, char *file_path) {
    int sock;
    FILE *in, *out;
    char rbuf[BUFFERSIZE];
    int res;

    // connect to a server
    sock = tcp_connect(server, port);
    if (sock < 0) return EXIT_FAILURE;
    if (fdopen_sock(sock, &in, &out) < 0) {
        fprintf(stderr, "fdopen()\n");
        close(sock);
        return EXIT_FAILURE;
    }

    // send request
    res = http_send_request(out, server, file_path);
    if (res < 0) {
        fprintf(stderr, "fprintf()\n");
        fclose(in);
        fclose(out);
        return EXIT_FAILURE;
    }

    // receive response
    res = http_receive_response(in, rbuf, BUFFERSIZE);
    if (res < 0) {
        fprintf(stderr, "fprintf()\n");
        fclose(in);
        fclose(out);
        return EXIT_FAILURE;
    }

    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}

int http_send_request(FILE *out, char *server, char *file_path) {
    int res;
    /* send a request */
    res =
        fprintf(out, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", file_path, server);
    return res;
}

int http_receive_response(FILE *in, char buf[], int size) {
    char *line;
    /* receive a response */
    while (1) {
        line = fgets(buf, size, in);
        // show received line
        if (line != NULL) {
            fprintf(stdout, "%s", line);
        } else {
            break;
        }
    }

    return EXIT_SUCCESS;
}

//* main function *//
int main(int argc, char *argv[]) {
    // init
    char *server;
    int port;
    char *file_path;
    int error_number;

    // arguments validation
    if (argc != 4) {
        fprintf(stderr, "Usage: %s server port file_path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // parse arguments
    // argv[1]: server, argv[2]: port, argv[3]: file_path
    server = argv[1];
    port = strtol(argv[2], NULL, 10);
    file_path = argv[3];

    // communicate to a server
    error_number = http_client_one(server, port, file_path);

    return error_number;
}
