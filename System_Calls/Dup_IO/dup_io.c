/*
 * duo_io.c
 * Perform standard input and output operations without using printf and scanf
 * Author: Swathi G
 */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LENGTH 50
int main() {

    int dup_printf = dup(STDOUT_FILENO);

    if (dup_printf < 0) {
        perror("dup");
        return -1;
    }

    char *str = "Hello World!, This is not displayed using Printf\n";
    ssize_t bytes =  write(dup_printf, str, strlen(str));

    if (bytes == -1) {
        perror("write");
        close(dup_printf);
        return -1;
    }

    char buf[BUFFER_LENGTH];
    int dup_scanf = dup(STDIN_FILENO);

    if(dup_scanf == -1) {
        perror("dup");
        close(dup_printf);
        return -1;
    }

    str = "Enter String: ";
    bytes =  write(dup_printf, str, strlen(str));

    if (bytes == -1) {
        perror("write");
        close(dup_printf);
        return -1;
    }

    ssize_t r = read(dup_scanf, buf, BUFFER_LENGTH);
    if(r == -1) {
        perror("read");
        close(dup_printf);
        close(dup_scanf);
        return -1;
    }
    buf[r] = '\0';
    str = "Read from user without using Scanf is: ";
    bytes =  write(dup_printf, str, strlen(str));

    if (bytes == -1) {
        perror("write");
        close(dup_printf);
        close(dup_scanf);
        return -1;
    }

    bytes = write(dup_printf, buf, r);
    if (bytes == -1) {
        perror("write");
        close(dup_printf);
        close(dup_scanf);
        return -1;
    }


    close(dup_printf);
    close(dup_scanf);
    
    return 0;
}