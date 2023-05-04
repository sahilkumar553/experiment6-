#include <stdio.h>
#include <pthread.h>

void *add_numbers(void *args) {
    int a = ((int*)args)[0];
    int b = ((int*)args)[1];
    printf("Thread started\n");
    int result = a + b;
    printf("Result: %d\n", result);
    printf("Thread finished\n");
    return NULL;
}

int main() {
    pthread_t thread;
    int args[] = {5, 10};
    pthread_create(&thread, NULL, add_numbers, args);
    pthread_join(thread, NULL);
    return 0;
}
