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
    // opendir() ... open directory
    if ((dirp = opendir(".")) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while (1) {
        org_errno = errno = 12345;
        // readdir() ... read per directory entry
        direntp = readdir(dirp);
        if (direntp == NULL) {
            if (errno == org_errno) {
                // complete reading all directory entries
                break;
            } else {
                // error occurred while reading directory entry
                perror("readdir");
                closedir(dirp);
                exit(EXIT_FAILURE);
            }
        } else {
            // successfully read directory entry
            // struct dirent {
            //     ino_t d_ino;             /* Inode number */
            //     off_t d_off;             /* Not an offset; see below */
            //     unsigned short d_reclen; /* Length of this record */
            //     unsigned char d_type;    /* Type of file; not supported
            /*                                 by all filesystem types */
            //     char d_name[256];        /* Null-terminated filename */
            // };
            printf("%s %u\n", direntp->d_name, direntp->d_reclen);
        }
    }
    // closedir() ... close directory
    closedir(dirp);
    return 0;
}