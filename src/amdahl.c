#include <stdio.h>
#include "logger_helper.h"

void clear_buffer_amdahl() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    log_action("User entered Amdahl's Law module.");
    double parallel_fraction;
    int cores;
    int choice;

    while(1) {
        printf("\n--- Amdahl's Law ---\n");
        printf("1. Calculate Speedup\n");
        printf("2. Compare Serial vs Parallel Execution Time\n");
        printf("3. Return to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clear_buffer_amdahl();
            continue;
        }

        if (choice == 3) {
            log_action("User returned to Main Menu from Amdahl's law.");
            return 0;
        }

        printf("Enter parallel fraction (0 to 1): ");
        if (scanf("%lf", &parallel_fraction) != 1) {
            printf("Invalid input.\n"); clear_buffer_amdahl(); continue;
        }
        if (parallel_fraction < 0 || parallel_fraction > 1) {
            printf("Invalid fraction. Must be between 0 and 1.\n");
            continue;
        }

        printf("Enter number of cores: ");
        if (scanf("%d", &cores) != 1) {
             printf("Invalid input.\n"); clear_buffer_amdahl(); continue;
        }
        if (cores <= 0) {
            printf("Invalid number of cores. Must be >= 1.\n");
            continue;
        }

        double speedup = 1.0 / ((1.0 - parallel_fraction) + (parallel_fraction / cores));

        if (choice == 1) {
            printf("Maximum theoretical speedup: %.4fX\n", speedup);
            char log_msg[150];
            snprintf(log_msg, sizeof(log_msg), "Amdahl: Calculated speedup %.4f (P=%.2f, N=%d).", speedup, parallel_fraction, cores);
            log_action(log_msg);
        } else if (choice == 2) {
            double serial_time;
            printf("Enter estimated serial execution time (units): ");
            if (scanf("%lf", &serial_time) != 1) {
                 printf("Invalid input.\n"); clear_buffer_amdahl(); continue;
            }
            double parallel_time = serial_time / speedup;
            printf("\n--- Comparison ---\n");
            printf("Serial Execution Time  : %.2f units\n", serial_time);
            printf("Parallel Execution Time: %.2f units\n", parallel_time);
            printf("------------------\n");
            char log_msg[150];
            snprintf(log_msg, sizeof(log_msg), "Amdahl: Compared execution (Serial:%.2f, Parallel:%.2f).", serial_time, parallel_time);
            log_action(log_msg);
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
