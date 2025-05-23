    /*
    * simple_file_logger.c
    * Periodically logs timestamped messages to a file.
    * Author: Swathi G
    * Usage: Logs N entries with 2-second delay between them.
    */

    #include <unistd.h>
    #include <fcntl.h>
    #include <time.h>
    #include <stdio.h>
    #include <string.h>

    #define SLEEP_TIME 2
    
    int main() {

        int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("open");
            return -1;
        }

        int logs;
        printf("Enter number of logs to record: ");
        scanf("%d",&logs);

        for(int i=0; i<logs; i++) {
            time_t now = time(NULL);  //return Epoch time
            if(now == (time_t)-1) {
                perror("time");
                close(fd);
                return -1;
            }

            char *str = ctime(&now);   //Takes seconds and returns Time in Day Month Date Time Year
            ssize_t bytes = write(fd, (const void *)str, strlen(str));  //writes to file

            if(bytes == -1) {
                perror("write");
                close(fd);
                return -1;
            }

            sleep(SLEEP_TIME);           //Sleeps for Two seconds
        }

        close(fd);
        return 0;
    }