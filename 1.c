#include <stdio.h>
#include <unistd.h>

int main() {
    // Get and print the process ID of the current process
    printf("Process ID: %d\n", getpid());

    // Get and print the parent process ID of the current process
    printf("Parent Process ID: %d\n", getppid());

    return 0;
}
