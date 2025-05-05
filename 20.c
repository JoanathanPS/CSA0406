#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

// Reader thread function
void *reader(void *arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&mutex);         // Enter critical section
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock); // Block writers if this is the first reader
        }
        sem_post(&mutex);         // Exit critical section

        // Reading operation
        printf("Reader reads data: %d\n", data);

        sem_wait(&mutex);         // Enter critical section
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock); // Unblock writers if this is the last reader
        }
        sem_post(&mutex);         // Exit critical section

        i++;
    }
    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&writeBlock);   // Wait for access to the shared data

        // Writing operation
        data++;
        printf("Writer writes data: %d\n", data);

        sem_post(&writeBlock);   // Release access to the shared data
        i++;
    }
    return NULL;
}

int main() {
    pthread_t readerThreads[5], writerThreads[5]; // Create 5 reader and 5 writer threads

    sem_init(&mutex, 0, 1);       // Mutex for readersCount
    sem_init(&writeBlock, 0, 1);  // Semaphore to block writers when readers are present

    // Create reader and writer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readerThreads[i], NULL, reader, NULL);
        pthread_create(&writerThreads[i], NULL, writer, NULL);
    }

    // Join all threads
    for (int i = 0; i < 5; i++) {
        pthread_join(readerThreads[i], NULL);
        pthread_join(writerThreads[i], NULL);
    }

    sem_destroy(&mutex);       // Destroy mutex
    sem_destroy(&writeBlock);  // Destroy writeBlock semaphore

    return 0;
}
