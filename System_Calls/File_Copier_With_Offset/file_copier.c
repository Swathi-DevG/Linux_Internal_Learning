/*
 * file_copier_with_offset.c
 * Copies data from source file to destination starting from a specific offset.
 * Author: Swathi G
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 10   

int main(int argc, char *argv[]) {
    
    if(argc < 4) {
        printf("Usage: %s <source_file> <destination_file> <offset>\n", argv[0]);
        return -1;
    }

    char *src_file = argv[1];
    char *dest_file = argv[2];
    off_t offset = atoi(argv[3]);

    if(offset < 0) {
        printf("Error: Invalid Offset\n");
        return -1;
    }

    int fd_src = open(src_file, O_RDONLY);
    int fd_dest = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if((fd_dest == -1) || (fd_src == -1)) {
        perror("open");
        return -1;
    }

    off_t new = lseek(fd_src, offset, SEEK_SET);

    if(new == -1) {
        perror("lseek");
        close(fd_dest);
        close(fd_src);
        return -1;
    }

    char buf[BUFFER_LEN];
    ssize_t r;

    do {
        r = read(fd_src, buf, BUFFER_LEN);
        if( r == -1) {
            perror("read");
            close(fd_src);
            close(fd_dest);
            return -1;
        }

        ssize_t w = write(fd_dest, buf, r);
        if(w != r) {
            perror("write");
            close(fd_src);
            close(fd_dest);
            return -1;
        }
        
    }while(r>0);

    close(fd_src);
    close(fd_dest);
    
    return 0; 
}