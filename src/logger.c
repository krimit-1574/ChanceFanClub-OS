//Saad Alam
//A00486772
//This source file implements the centralized logger process that listens for log messages sent through a named pipe (FIFO) and writes them to a log file with timestamps. It also prints the logged messages to the console for demonstration purposes. The logger can be shut down by sending a specific command through the FIFO.
// src/logger.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#define FIFO_PATH "/tmp/os_project_logger_fifo"
#define LOG_FILE "../logs/logs.txt" // Assumes execution from /bin

int main() {
    int fd;
    char buffer[512];
    FILE *file;

    // 1. Create the FIFO (Named Pipe) if it doesn't exist
    mkfifo(FIFO_PATH, 0666);

    printf("Logger Module Started. Listening for events...\n");

    // 2. Infinite loop to keep the logger alive
    while (1) {
        // Open the pipe for reading
        fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1) continue;

        // Read the incoming message
        if (read(fd, buffer, sizeof(buffer)) > 0) {
            
            // 3. Generate Timestamp
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char time_str[64];
            // Format: YYYY-MM-DD HH:MM:SS
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

            // 4. Open the log file in append mode and write
            file = fopen(LOG_FILE, "a");
            if (file != NULL) {
                fprintf(file, "[%s] %s\n", time_str, buffer);
                fflush(file); // Ensure it writes to disk immediately
                fclose(file);
            }
            
            // Also print to console for demonstration purposes
            printf("LOGGED: [%s] %s\n", time_str, buffer);
            
            // Secret shutdown command to exit gracefully
            if (strstr(buffer, "SHUTDOWN_LOGGER") != NULL) {
                close(fd);
                break;
            }
        }
        close(fd);
    }

    // Cleanup
    unlink(FIFO_PATH);
    printf("Logger cleanly shut down.\n");
    return 0;
}