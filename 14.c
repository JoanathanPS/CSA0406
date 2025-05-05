#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// Function to copy a file
void copy() {
    const char *sourcefile = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    const char *destination_file = "C:/Users/itssk/OneDrive/Desktop/sk.txt";
    int source_fd = open(sourcefile, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return;
    }

    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            break;
        }
    }

    if (bytesRead == -1) {
        perror("Error reading source file");
    } else {
        printf("File copied successfully.\n");
    }

    close(source_fd);
    close(dest_fd);
}

// Function to create a file and allow user input
void create() {
    char path[100];
    printf("Enter the file path to create: ");
    scanf("%s", path);
    
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return;
    }
    
    printf("File created successfully at %s.\n", path);
    fclose(fp);
}

// Function to delete a file
void deleteFile() {
    const char *filePath = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    
    if (remove(filePath) == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }
}

int main() {
    int n;
    printf("1. Create \t2. Copy \t3. Delete\nEnter your choice: ");
    scanf("%d", &n);

    switch (n) {
        case 1:
            create();
            break;
        case 2:
            copy();
            break;
        case 3:
            deleteFile();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
