#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // Create a new process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process block
        printf("Child is starting new execution\n");
        
        // Replace child process with "ls -l" command
        if (execlp("ls", "ls", "-l", NULL) == -1) {
            perror("execlp failed");  // Print error if execlp fails
        }
    }
    else if (pid > 0) {
        // Parent process block
        printf("Parent started\n");

        int status;
        printf("Parent started waiting for child to finish\n");

        // Wait for child to terminate
        wait(&status);

        // Check if child exited normally and print its exit status
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }

        printf("Parent terminated\n");
    }
    else {
        // Fork failed
        printf("Error while forking\n");
    }

    return 0;
}
