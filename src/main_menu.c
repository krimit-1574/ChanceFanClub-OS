#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "logger_helper.h" 

void run_module(const char* module_name) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed in main menu");
    } else if (pid == 0) {
        // Child
        execl(module_name, module_name, NULL);
        perror("Exec failed for module");
        exit(1);
    } else {
        // Parent waits for child program to finish completely
        waitpid(pid, NULL, 0);
    }
}

void clear_buffer_main() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    int choice;
    log_action("System Started. Main Menu initialized.");

    while(1) {
        printf("\n==========================================\n");
        printf("    OPERATING SYSTEMS FINAL PROJECT\n");
        printf("==========================================\n");
        printf("------Main Menu------\n");
        printf("1. Peterson's Solution\n");
        printf("2. File Management\n");
        printf("3. Contiguous Memory Allocation\n");
        printf("4. Amdahl's Law\n");
        printf("5. Exit System\n");
        printf("==========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            clear_buffer_main();
            continue;
        }
        
        switch(choice) {
            case 1:
                log_action("User selected Peterson's Solution.");
                run_module("./peterson");
                break;
            case 2:
                log_action("User selected File Management.");
                run_module("./file_management");
                break;
            case 3:
                log_action("User selected Contiguous Memory Allocation.");
                run_module("./memory");
                break;
            case 4:
                log_action("User selected Amdahl's Law.");
                run_module("./amdahl");
                break;
            case 5:
                log_action("User exited the system.");
                printf("Exiting... Have a nice day!\n");
                return 0;
            default:
                printf("Invalid choice. Please pick between 1-5.\n");
        }
    }
    return 0;
}
