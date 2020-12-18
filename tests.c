#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

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


    lseek(fd,0,SEEK_SET);

    /*
    tar_header_t *header =(tar_header_t *) malloc(512);
    char *path = "wibs";
    int loc = is_symlink(fd, path);
    printf("loc : %i\n",loc);
    if(loc){
        lseek(fd,(loc-1)*512,SEEK_SET);
        read(fd,header,512);
        printf("linkname : %s\n",header->linkname);
        lseek(fd,0,SEEK_SET);
    }
    /*
    char *string="folder/file";
    char *slash= "/";
    char *strst=strstr(string,slash);
    printf("%i\n",strlen(strst)<=1);
    */
    char *path="wobs";
    char **entries = (char **) malloc(20*sizeof(char*));
    for(int i=0;i<20;i++){
        entries[i]=(char*) malloc(100);
    }
    size_t numEntries=20;
    size_t *no_entries=&numEntries;

    ret=list(fd,path,entries,no_entries);
    printf("retval list : %i\nlist no_entries : %li\n",ret, *no_entries);
    for(int i=0;i<ret;i++){
        printf("entry nbr %i : %s\n",i+1,entries[i]);
    }



    return 0;
}
