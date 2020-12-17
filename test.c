#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdlib.h"

#include "lib_tar.h"

int main(int argc, char *argv[]) {
    tar_header_t *header =(tar_header_t *) malloc(512);
    printf("size of header : %lu \n", sizeof(header->name));
}

