#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void create_file();
void read_file();
void list_files();
void delete_file();

int main() {
    int choice;

    while (1) {
        printf("\n--- File Management System ---");
        printf("\n1. Create File");
        printf("\n2. Read File");
        printf("\n3. List Files");
        printf("\n4. Delete File");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1: create_file(); break;
            case 2: read_file(); break;
            case 3: list_files(); break;
            case 4: delete_file(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// 1. Create a new file and write content to it
void create_file() {
    char filename[100], content[500];
    FILE *fptr;

    printf("Enter filename (e.g., test.txt): ");
    scanf("%s", filename);
    getchar(); 

    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error creating file!\n");
        return;
    }

    printf("Enter content to write: ");
    fgets(content, sizeof(content), stdin);
    fprintf(fptr, "%s", content);
    
    fclose(fptr);
    printf("File created successfully.\n");
}

// 2. Read and display the content of a file
void read_file() {
    char filename[100], ch;
    FILE *fptr;

    printf("Enter filename to read: ");
    scanf("%s", filename);

    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    printf("\n--- File Content ---\n");
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    printf("\n--------------------\n");

    fclose(fptr);
}

// 3. List all files in the current directory
void list_files() {
    struct dirent *de; 
    DIR *dr = opendir("."); // Open current directory

    if (dr == NULL) {
        printf("Could not open directory.\n");
        return;
    }

    printf("\n--- Directory Listing ---\n");
    while ((de = readdir(dr)) != NULL) {
        // Skip current and parent directory pointers
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            printf("%s\n", de->d_name);
        }
    }
    closedir(dr);
}

// 4. Delete a file from the system
void delete_file() {
    char filename[100];

    printf("Enter filename to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error: Unable to delete the file.\n");
    }
}