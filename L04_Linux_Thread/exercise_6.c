#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 1000000
#define THREADS 4
int array[SIZE];
long long total_sum = 0;
pthread_mutex_t mutex;

void* sum_part(void* arg) {
    int part = *(int*)arg;
    int start = part * (SIZE / THREADS);
    int end = (part + 1) * (SIZE / THREADS);
    long long local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += array[i];
    }

    pthread_mutex_lock(&mutex);
    total_sum += local_sum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[THREADS];
    int part_ids[THREADS];

    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
    }

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREADS; i++) {
        part_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_part, &part_ids[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total sum of array: %lld\n", total_sum);
    pthread_mutex_destroy(&mutex);
    return 0;
}