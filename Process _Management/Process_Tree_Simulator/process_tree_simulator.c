#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    //Main process forks Child1
    pid_t child1 = fork();

    if (child1 == 0) {
        // ---- This block is executed only by Child1 ----

        // Child1 forks Grandchild1
        pid_t grandchild1 = fork();

        if(grandchild1 > 0) {
            // This is still Child1 (parent of Grandchild1)
            printf("Child1: PID = %d, PPID = %d\n", getpid(), getppid());
        }
        else if(grandchild1 == 0) {
            // This is Grandchild1
            printf("GrandChild1: PID = %d, PPID = %d\n", getpid(), getppid());
        }
        else {
            perror("fork");
        }

        // To prevent Child1 and Grandchild1 from executing the rest of main
        return 0;
    }
    else if (child1 > 0) {
        // ---- This block is executed only by the Main process (after forking Child1) ----

        // Main forks Child2
        pid_t child2 = fork();

        if (child2 == 0) {
            // ---- This block is executed only by Child2 ----

            //Child2 forks Grandchild2
            pid_t grandchild2 = fork();

            if(grandchild2 > 0) {
                // This is still Child2 (parent of Grandchild2)
                printf("Child2: PID = %d, PPID = %d\n", getpid(), getppid());
            }
            else if(grandchild2 == 0) {
                // This is Grandchild2
                printf("GrandChild2: PID = %d, PPID = %d\n", getpid(), getppid());
            }
            else {
                perror("fork");
            }

            // Prevent Child2 and Grandchild2 from executing the rest of main
            return 0;
        }
        else if (child2 > 0) {
            // Still in Main process (parent of Child1 and Child2)
            printf("Main: PID = %d, PPID = %d\n", getpid(), getppid());
        }
        else {
            perror("fork");
        }
    }
    else {
        perror("fork");
    }

    return 0;
}
