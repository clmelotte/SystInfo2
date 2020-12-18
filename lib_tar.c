#include "lib_tar.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
/**
 * Checks whether the archive is valid.
 *
 * Each non-null header of a valid archive has:
 *  - a magic value of "ustar" and a null,
 *  - a version value of "00" and no null,
 *  - a correct checksum
 *
 * @param tar_fd A file descriptor pointing to the start of a file supposed to contain a tar archive.
 *
 * @return a zero or positive value if the archive is valid, representing the number of headers in the archive,
 *         -1 if the archive contains a header with an invalid magic value,
 *         -2 if the archive contains a header with an invalid version value,
 *         -3 if the archive contains a header with an invalid checksum value
 */
int check_archive(int tar_fd) {


    int count = 0;

    tar_header_t *header = (tar_header_t *) malloc(512);
    int ret = read(tar_fd, header, 512);

    int out=0;
    while (ret == 512) {
        for(int i=0; i<100; i++) {
            if(header->name[i]=='0' || header->name[i]=='\0'){
                if(i == 99){out =1;}
            }
            else{break;}
        }
        if(out){break;}
        count++;

        printf("count %d\n", count);
        if (strcmp(header->magic, "ustar")) {
            return -1;}
        if (header->version[0] != '0' || header->version[1] != '0') { return -2; }

        uint8_t *header_u8f = (uint8_t *) header;
        uint8_t valsumchk = 0;
        for (int i = 0; i < 8; i++) { valsumchk += (uint8_t) header->chksum[i]; }

        uint8_t chksum_chk = 0;
        for (int i = 0; i < 512; i++) { chksum_chk += header_u8f[i]; }
        chksum_chk = chksum_chk - valsumchk;
        int chksum_int = (int) strtol(header->chksum, NULL, 10);
        if (chksum_int == chksum_chk) { return -3; }

        int size = (int) (strtol(header->size, NULL, 8) + 511) / 512;
        for (int i = 0; i <= size; i++) {
            ret = read(tar_fd, header, 512);
        }
    }
    return count;
}




/**
 * Checks whether an entry exists in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive,
 *         any other value otherwise.
 */
int exists(int tar_fd, char *path){
    int n = 512;
    tar_header_t *header =(tar_header_t *) malloc(n);
    int ret = read(tar_fd,header,n);
    while(ret!=0){
        if(strcmp(header->name,path)==0) {
            return 1;
        }
        int size = (int) (strtol(header->size,NULL,8)+511)/512;
        for(int i=0;i<=size;i++) {
            ret = read(tar_fd, header, n);
        }
    }
    return 0;
}

/**
 * Checks whether an entry exists in the archive and is a directory.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive or the entry is not a directory,
 *         any other value otherwise.
 */
int is_dir(int tar_fd, char *path) {
    int n = 512;
    tar_header_t *header =(tar_header_t *) malloc(n);
    int ret = read(tar_fd,header,n);
    while(ret!=0){
        if(strcmp(header->name,path)==0) {
            if (header->typeflag == '5') { return 1; }
            else { return 0; }
        }
        int size = (int) (strtol(header->size,NULL,8)+511)/512;
        for(int i=0;i<=size;i++) {
            ret = read(tar_fd, header, n);
        }
    }
    return 0;
}

/**
 * moi
 * Checks whether an entry exists in the archive and is a file.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 *
 * @return zero if no entry at the given path exists in the archive or the entry is not a file,
 *         any other value otherwise.
 */
int is_file(int tar_fd, char *path) {
    int n = 512;
    tar_header_t *header =(tar_header_t *) malloc(n);
    int ret = read(tar_fd,header,n);
    while(ret!=0){
        if(strcmp(header->name,path)==0) {
            if (header->typeflag == '0' || header->typeflag == '\0') { return 1; }
            else { return 0; }
        }
        int size = (int) (strtol(header->size,NULL,8)+511)/512;
        for(int i=0;i<=size;i++) {
            ret = read(tar_fd, header, n);
        }
    }
    return 0;
}

/**
 * moi
 * Checks whether an entry exists in the archive and is a symlink.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive.
 * @return zero if no entry at the given path exists in the archive or the entry is not symlink,
 *         any other value otherwise.
 */
int is_symlink(int tar_fd, char *path) {
    int n = 512;
    tar_header_t *header =(tar_header_t *) malloc(n);
    int ret = read(tar_fd,header,n);
    while(ret!=0){
        if(strcmp(header->name,path)==0) {
            if (header->typeflag == '2') { return 1; }
            else { return 0; }
        }
        int size = (int) (strtol(header->size,NULL,8)+511)/512;
        for(int i=0;i<=size;i++) {
            ret = read(tar_fd, header, n);
        }
    }
    return 0;
}


/**
 * moi
 * Lists the entries at a given path in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive. If the entry is a symlink, it must be resolved to its linked-to entry.
 * @param entries An array of char arrays, each one is long enough to contain a tar entry
 * @param no_entries An in-out argument.
 *                   The caller set it to the number of entry in entries.
 *                   The callee set it to the number of entry listed.
 *
 * @return zero if no directory at the given path exists in the archive,
 *         any other value otherwise.
 */
int list(int tar_fd, char *path, char **entries, size_t *no_entries) {
    return 0;
}

/**
 * Reads a file at a given path in the archive.
 *
 * @param tar_fd A file descriptor pointing to the start of a tar archive file.
 * @param path A path to an entry in the archive to read from.  If the entry is a symlink, it must be resolved to its linked-to entry.
 * @param offset An offset in the file from which to start reading from, zero indicates the start of the file.
 * @param dest A destination buffer to read the given file into.
 * @param len An in-out argument.
 *            The caller set it to the size of dest.
 *            The callee set it to the number of bytes written to dest.
 *
 * @return -1 if no entry at the given path exists in the archive or the entry is not a file,
 *         -2 if the offset is outside the file total length,
 *         zero if the file was read in its entirety into the destination buffer,
 *         a positive value if the file was partially read, representing the remaining bytes left to be read.
 *
 */
ssize_t read_file(int tar_fd, char *path, size_t offset, uint8_t *dest, size_t *len) {
    return 0;
}