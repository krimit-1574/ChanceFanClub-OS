#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./logger <message>\n");
        return 1;
    }
    
    // Open the log file in append mode.
    // The working directory given the project setup is bin/
    FILE *log_file = fopen("../logs/logs.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    
    // Get the current local time
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    
    // Log the message with a timestamp
    fprintf(log_file, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
            local->tm_hour, local->tm_min, local->tm_sec,
            argv[1]);
            
    fclose(log_file);
    return 0;
}
