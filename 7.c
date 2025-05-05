#include <stdio.h>

int main() {
    int at[10], bt[10], pr[10];
    int n, i, j, temp, time = 0, count, completed = 0, sum_wait = 0, sum_turnaround = 0, start;
    float avg_wait, avg_turnaround;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter the arrival time and burst time for Process[%d]:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        pr[i] = i + 1; // Process ID
    }

    // Sort processes by arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                // Swap arrival times
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                // Swap burst times
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                // Swap process IDs
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
            }
        }
    }

    printf("\n\nProcess\t| Arrival Time | Burst Time | Start Time | End Time | Waiting Time | Turnaround Time\n");
    printf("------------------------------------------------------------------------------------------\n");

    while (completed < n) {
        count = 0;

        // Count how many processes have arrived till now
        for (i = completed; i < n; i++) {
            if (at[i] <= time)
                count++;
            else
                break;
        }

        // Sort the ready queue (arrived processes) by burst time
        if (count > 1) {
            for (i = completed; i < completed + count - 1; i++) {
                for (j = i + 1; j < completed + count; j++) {
                    if (bt[i] > bt[j]) {
                        // Swap arrival times
                        temp = at[i]; at[i] = at[j]; at[j] = temp;
                        // Swap burst times
                        temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                        // Swap process IDs
                        temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                    }
                }
            }
        }

        start = time;
        time += bt[completed]; // End time is start + burst
        int waiting = start - at[completed];
        int turnaround = time - at[completed];

        printf("P[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t\t|\t%d\n",
               pr[completed], at[completed], bt[completed], start, time, waiting, turnaround);

        sum_wait += waiting;
        sum_turnaround += turnaround;
        completed++;
    }

    avg_wait = (float)sum_wait / n;
    avg_turnaround = (float)sum_turnaround / n;

    printf("\nAverage Waiting Time: %.2f", avg_wait);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);

    return 0;
}
