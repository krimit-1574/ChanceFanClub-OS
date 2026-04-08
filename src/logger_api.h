//Saad Alam
//A00486772
// This header file defines the API for sending log messages to a centralized logger process using a named pipe (FIFO).
// src/logger_api.h
#ifndef LOGGER_API_H
#define LOGGER_API_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/os_project_logger_fifo"

// Function to send a message to the centralized logger
void send_log(const char *module_name, const char *message) {
    int fd;
    char buffer[512];
    
    // Format the message to include the module name
    snprintf(buffer, sizeof(buffer), "[%s] %s", module_name, message);
    
    // Open the FIFO in write-only mode
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd != -1) {
        write(fd, buffer, strlen(buffer) + 1);
        close(fd);
    } else {
        printf("Warning: Logger is not running.\n");
    }
}

#endif