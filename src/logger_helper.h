#ifndef LOGGER_HELPER_H
#define LOGGER_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void log_action(const char* message) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed in logger helper");
    } else if (pid == 0) {
        // Child process invokes logger
        // We assume the executable is run from bin/ directory, so ./logger exists.
        execl("./logger", "./logger", message, NULL);
        perror("execl failed (logger not found in bin/?)"); // Executed only if execl fails
        exit(1);
    } else {
        // Parent waits for logger to finish
        waitpid(pid, NULL, 0);
    }
}

#endif
