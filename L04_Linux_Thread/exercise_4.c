#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 100
int array[SIZE];
int even_count = 0, odd_count = 0;

void* count_even(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        if (array[i] % 2 == 0) {
            even_count++;
        }
    }
    return NULL;
}

void* count_odd(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        if (array[i] % 2 != 0) {
            odd_count++;
        }
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 100 + 1;
    }

    pthread_create(&t1, NULL, count_even, NULL);
    pthread_create(&t2, NULL, count_odd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Number of even numbers: %d\n", even_count);
    printf("Number of odd numbers: %d\n", odd_count);
    return 0;
}