#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 1000

int numbers[MAX_NUMBERS];
int num_count = 0;
double average = 0;
int max = 0;
int min = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calc_average(void *arg) {
    int sum = 0;
    for (int i = 0; i < num_count; i++) {
        sum += numbers[i];
    }
    average = (double)sum / num_count;
    pthread_exit(NULL);
}

void *calc_max(void *arg) {
    max = numbers[0];
    for (int i = 1; i < num_count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    pthread_exit(NULL);
}

void *calc_min(void *arg) {
    min = numbers[0];
    for (int i = 1; i < num_count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];

    printf("Enter up to %d numbers (enter -1 to stop):\n", MAX_NUMBERS);

    int num = 0;
    while (num != -1 && num_count < MAX_NUMBERS) {
        scanf("%d", &num);
        if (num != -1) {
            numbers[num_count++] = num;
        }
    }

    pthread_create(&threads[0], NULL, calc_average, NULL);
    pthread_create(&threads[1], NULL, calc_max, NULL);
    pthread_create(&threads[2], NULL, calc_min, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Average: %.2f\n", average);
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);

    return 0;
}
