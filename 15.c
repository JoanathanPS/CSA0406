#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];

    // Construct the full path for the directory
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);

    // Check if the subdirectory exists, if not, create it
    struct stat st = {0};
    if (stat(mainDirPath, &st) == -1) {
        if (mkdir(mainDirPath, 0700) == -1) {
            perror("Error creating subdirectory");
            return 1;
        }
        printf("Subdirectory created: %s\n", mainDirPath);
    }

    // Construct the full file path
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);

    // Create the file
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    // Write content to the file
    fprintf(file, "This is an example file content.");

    // Close the file
    fclose(file);

    printf("File created successfully: %s\n", filePath);

    return 0;
}
