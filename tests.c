#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "lib_tar.h"

/**
 * You are free to use this file to write tests for your implementation
 */


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("err agc <2 %d",argc);
        return -1;
    }

    int fd = open(argv[1] , O_RDONLY);

    if (fd == -1) {
        printf("fd == -1 %s", strerror(errno));
        return -1;
    }

    int ret = check_archive(fd);
    printf("check_archive returned ... %d\n", ret);

    return 0;
}