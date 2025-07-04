#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

int main(void) {
    DIR *dirp;
    struct dirent *direntp;
    struct stat st;
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
            //
            // struct dirent {
            //     ino_t d_ino;             /* Inode number */
            //     off_t d_off;             /* Not an offset; see below */
            //     unsigned short d_reclen; /* Length of this record */
            //     unsigned char d_type;    /* Type of file; not supported
            /*                                 by all filesystem types */
            //     char d_name[256];        /* Null-terminated filename */
            // };
            //
            // struct stat {
            //     dev_t st_dev;            /* ID of device containing file */
            //     ino_t st_ino;            /* Inode number */
            //     mode_t st_mode;          /* File type and mode */
            //     nlink_t st_nlink;        /* Number of hard links */
            //     uid_t st_uid;            /* User ID of owner */
            //     gid_t st_gid;            /* Group ID of owner */
            //     dev_t st_rdev;           /* Device ID (if special file) */
            //     off_t st_size;           /* Total size, in bytes */
            //     blksize_t st_blksize;    /* Block size for filesystem I/O */
            //     blkcnt_t st_blocks;      /* Number of 512B blocks allocated
            //     */ struct timespec st_atim; /* Time of last access */ struct
            //     timespec st_mtim; /* Time of last modification */ struct
            //     timespec st_ctim; /* Time of last status change */
            // };
            if (stat(direntp->d_name, &st) == -1) {
                perror("stat");
                exit(EXIT_FAILURE);
            }
            printf("%s %ld\n", direntp->d_name, st.st_size);
        }
    }
    // closedir() ... close directory
    closedir(dirp);
    return 0;
}