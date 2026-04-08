//Saad Alam
//A00486772
//This source file implements the Peterson's solution for mutual exclusion using shared memory and process synchronization. It simulates two processes that attempt to enter a critical section while ensuring that only one process can be in the critical section at a time. The processes communicate their intentions and states through shared memory, and log their actions using a centralized logger.
// src/peterson.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "logger_api.h" // Include our custom logger

// Define a structure for our shared memory
typedef struct {
    int flag[2];
    int turn;
} SharedData;

int main() {
    // 1. Set up Shared Memory using mmap
    // MAP_SHARED allows both processes to see changes. MAP_ANONYMOUS means it's not backed by a file.
    SharedData *shared = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, 
                              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    // Initialize shared variables
    shared->flag[0] = 0;
    shared->flag[1] = 0;
    shared->turn = 0;

    send_log("Peterson", "Starting Peterson's Solution Simulation");

    // 2. Fork to create two processes
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    int process_id;
    int other_process;

    if (pid == 0) {
        // Child Process
        process_id = 1;
        other_process = 0;
    } else {
        // Parent Process
        process_id = 0;
        other_process = 1;
    }

    // 3. The Simulation Loop (Simulating multiple attempts to enter)
    for (int i = 0; i < 2; i++) {
        char log_msg[256];

        // --- ENTRY SECTION --- [cite: 19]
        // Indicate this process wants to enter
        shared->flag[process_id] = 1;
        // Give the turn to the other process politely
        shared->turn = other_process; 

        snprintf(log_msg, sizeof(log_msg), "Process %d: Entering ENTRY section.", process_id);
        send_log("Peterson", log_msg);

        // Busy Waiting Loop 
        // "While the other process wants to enter AND it is the other process's turn, I will wait."
        while (shared->flag[other_process] == 1 && shared->turn == other_process) {
            // Spinning... (busy waiting)
        }

        // --- CRITICAL SECTION --- [cite: 19]
        snprintf(log_msg, sizeof(log_msg), "Process %d: Entering CRITICAL section.", process_id);
        send_log("Peterson", log_msg);
        
        printf("Process %d is inside the Critical Section.\n", process_id);
        sleep(1); // Simulate work being done to prove mutual exclusion

        snprintf(log_msg, sizeof(log_msg), "Process %d: Leaving CRITICAL section.", process_id);
        send_log("Peterson", log_msg);

        // --- EXIT SECTION --- [cite: 19]
        // Indicate this process is done and no longer wants to enter
        shared->flag[process_id] = 0; 
        
        snprintf(log_msg, sizeof(log_msg), "Process %d: In EXIT section. Flag set to 0.", process_id);
        send_log("Peterson", log_msg);
        
        // Simulating some non-critical work before looping again
        sleep(1); 
    }

    // 4. Cleanup
    if (pid > 0) {
        // Parent waits for child to finish to prevent zombie processes
        wait(NULL); 
        // Free the shared memory
        munmap(shared, sizeof(SharedData));
        send_log("Peterson", "Simulation complete. Shared memory unmapped.");
        printf("Peterson's simulation completed successfully.\n");
    }

    return 0;
}