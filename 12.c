#include <stdio.h>

void bestfit(int mp[], int p[], int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        int bestIdx = -1;
        for (j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (bestIdx == -1 || mp[j] < mp[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            printf("\nProcess %d fits in memory partition %d\n", p[i], mp[bestIdx]);
            mp[bestIdx] -= p[i]; // Reduce the memory size of the partition
        } else {
            printf("\nProcess %d must wait for a free partition\n", p[i]);
        }
    }
}

void firstfit(int mp[], int p[], int m, int n) {
    for (int i = 0; i < m; i++) {
        int allocated = 0;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                printf("\nProcess %d fits in memory partition %d\n", p[i], mp[j]);
                mp[j] -= p[i]; // Reduce the memory size of the partition
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("\nProcess %d must wait for a free partition\n", p[i]);
        }
    }
}

void worstfit(int mp[], int p[], int m, int n) {
    for (int i = 0; i < m; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (worstIdx == -1 || mp[j] > mp[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            printf("\nProcess %d fits in memory partition %d\n", p[i], mp[worstIdx]);
            mp[worstIdx] -= p[i]; // Reduce the memory size of the partition
        } else {
            printf("\nProcess %d must wait for a free partition\n", p[i]);
        }
    }
}

int main() {
    int m, n, mp[20], p[20], ch;
    printf("Number of memory partitions: ");
    scanf("%d", &n);

    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter the memory partitions:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }

    printf("Enter the process sizes:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }

    printf("1. Firstfit\n2. Bestfit\n3. Worstfit\nEnter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
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
            printf("Invalid choice\n");
            break;
    }

    return 0;
}
