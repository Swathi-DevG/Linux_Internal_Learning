#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    
    printf("System Process info: \n");
    system("ps");

    return 0;
}