#include <stdio.h>

struct priority_scheduling {
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

int main() {
    int number_of_process, total = 0, position;
    float average_waiting_time, average_turnaround_time;
    struct priority_scheduling temp_process;
    int ASCII_number = 65; // ASCII 'A'

    printf("Enter the total number of Processes: ");
    scanf("%d", &number_of_process);

    struct priority_scheduling process[number_of_process];

    printf("\nEnter the Burst Time and Priority of each process:\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].process_name = (char)ASCII_number;
        printf("\nEnter the details of Process %c:\n", process[i].process_name);
        printf("Burst Time: ");
        scanf("%d", &process[i].burst_time);
        printf("Priority (higher number = higher priority): ");
        scanf("%d", &process[i].priority);
        ASCII_number++;
    }

    // Sort based on priority (higher number = higher priority)
    for (int i = 0; i < number_of_process; i++) {
        position = i;
        for (int j = i + 1; j < number_of_process; j++) {
            if (process[j].priority > process[position].priority)
                position = j;
        }
        // Swap
        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    // First process waiting time is 0
    process[0].waiting_time = 0;

    // Calculate waiting time
    for (int i = 1; i < number_of_process; i++) {
        process[i].waiting_time = 0;
        for (int j = 0; j < i; j++) {
            process[i].waiting_time += process[j].burst_time;
        }
        total += process[i].waiting_time;
    }

    average_waiting_time = (float)total / number_of_process;

    // Calculate turnaround time and total
    total = 0;
    printf("\nProcess Name\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < number_of_process; i++) {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;
        total += process[i].turn_around_time;
        printf("    %c\t\t%d\t\t%d\t\t%d\n", process[i].process_name,
               process[i].burst_time, process[i].waiting_time,
               process[i].turn_around_time);
    }

    average_turnaround_time = (float)total / number_of_process;

    printf("\nAverage Waiting Time: %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
