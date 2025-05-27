    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/wait.h>

    int main() {

        // Create a named FIFO (first-time creation)
        int rt = mkfifo("fifo_file.txt", 0666);
        if(rt == -1) {
            perror("mkfifo");
            return -1;
        }

        // Create a child process
        pid_t pid = fork();

        if(pid == -1) {
            perror("fork");
            return -1;
        }
        if(pid > 0) {
            //parent
            int fd = open("fifo_file.txt", O_WRONLY);
            if(fd == -1) {
                perror("open parent");
                return -1;
            }
            char buf[50];
            printf("Write to Fifo: ");
            fgets(buf,50,stdin);
            size_t len = strlen(buf);

            // Remove trailing newline if present
            if (len > 0 && buf[len - 1] == '\n') {
                buf[len - 1] = '\0';
                len--;
            }

             // Write to the FIFO
            if( write(fd, buf, len) == -1) {
                perror("write");
                return -1;
            }
            close(fd);
            wait(NULL);
            unlink("fifo_file.txt");    // Remove the FIFO file from filesystem
        }
        else {

            //child
            int fd = open("fifo_file.txt", O_RDONLY);
            if(fd == -1) {
                perror("open child");
                return -1;
            }

            // Read from FIFO
            char buf[50];
            int r = read(fd, buf, 50);
            if(r == -1) {
                perror("read");
            }

            buf[r] = '\0';
            printf("Received from Fifo: %s\n",buf);
            close(fd);
        }
    }