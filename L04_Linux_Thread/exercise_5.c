#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;
pthread_rwlock_t rwlock;

void* reader(void* arg) {
    int id = *(int*)arg;
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %d: Data = %d\n", id, data);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("Writer %d: Incremented data to %d\n", id, data);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    pthread_rwlock_init(&rwlock, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    printf("Final data value: %d\n", data);
    pthread_rwlock_destroy(&rwlock);
    return 0;
}