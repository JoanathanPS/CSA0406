#include <stdio.h>

// First Fit Allocation
void firstfit(int mp[], int p[], int m, int n) {
    int alloc[m];
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                alloc[i] = j;
                mp[j] -= p[i];
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("\nProcess %d of size %d allocated to memory block %d", i + 1, p[i], alloc[i] + 1);
        else
            printf("\nProcess %d of size %d must wait", i + 1, p[i]);
    }
}

// Sort in ascending order
void sort(int a[], int idx[], int n) {
    for (int i = 0; i < n; i++) idx[i] = i;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[idx[i]] > a[idx[j]]) {
                int temp = idx[i];
                idx[i] = idx[j];
                idx[j] = temp;
            }
        }
    }
}

// Best Fit Allocation
void bestfit(int mp[], int p[], int m, int n) {
    int alloc[m];
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int best = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (best == -1 || mp[j] < mp[best])
                    best = j;
            }
        }
        if (best != -1) {
            alloc[i] = best;
            mp[best] -= p[i];
        }
    }

    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("\nProcess %d of size %d allocated to memory block %d", i + 1, p[i], alloc[i] + 1);
        else
            printf("\nProcess %d of size %d must wait", i + 1, p[i]);
    }
}

// Worst Fit Allocation
void worstfit(int mp[], int p[], int m, int n) {
    int alloc[m];
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int worst = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (worst == -1 || mp[j] > mp[worst])
                    worst = j;
            }
        }
        if (worst != -1) {
            alloc[i] = worst;
            mp[worst] -= p[i];
        }
    }

    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("\nProcess %d of size %d allocated to memory block %d", i + 1, p[i], alloc[i] + 1);
        else
            printf("\nProcess %d of size %d must wait", i + 1, p[i]);
    }
}

// Main Function
int main() {
    int m, n, mp[20], p[20], choice;
    printf("Number of memory partitions: ");
    scanf("%d", &n);
    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter memory partitions:\n");
    for (int i = 0; i < n; i++) scanf("%d", &mp[i]);

    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++) scanf("%d", &p[i]);

    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            firstfit(mp, p, m, n);
            break;
        case 2:
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice.");
    }

    return 0;
}
