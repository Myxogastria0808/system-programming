// struct dirent {
//     ino_t d_ino;             /* Inode number */
//     off_t d_off;             /* Not an offset; see below */
//     unsigned short d_reclen; /* Length of this record */
//     unsigned char d_type;    /* Type of file; not supported
//                                 by all filesystem types */
//     char d_name[256];        /* Null-terminated filename */
// };

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

int main(void) {
    DIR *dirp;
    struct dirent *direntp;
    int org_errno, errno;
    if ((dirp = opendir(".")) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while (1) {
        org_errno = errno = 12345;
        direntp = readdir(dirp);
        if (direntp == NULL) {
            if (errno == org_errno) {
                /* 全ディレクトリエントリを読み終えた */
                break;
            } else {
                /* ディレクトリエントリの読み出しエラー */
                perror("readdir");
                closedir(dirp);
                exit(EXIT_FAILURE);
            }
        } else {
            /* ディレクトリエントリの読み出し成功 */
            printf("%s\n", direntp->d_name);
        }
    }
    closedir(dirp);
    return 0;
}