/* Zombie Process Demonstration: Child completes its execution before Parent */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid > 0) {  // Parent process
        printf("Parent Started with PID : %d\n", getpid());
        printf("Parent Stated Sleeping\n");
        sleep(10);  // Parent sleeps for 10 seconds, during which the child is a zombie

        int status;
        wait(&status);  // Parent waits and collects child exit status, cleaning zombie

        if (WIFEXITED(status)) {
            printf("Child terminated with status %d\n", WEXITSTATUS(status));
        }
        printf("Parent Ended\n");
    }
    else if (pid == 0) {  // Child process
        printf("Child Started with PID: %d\n", getpid());
        printf("Child Ended\n");
        // Child exits immediately, becoming a zombie until parent calls wait()
    }
    else {
        perror("fork");  // Fork failed
    }

    return 0;
}
