#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_STRING_LEN 100

// Data structure to pass arguments to thread function
struct ThreadArgs {
    char* string;
};

// Thread function to find length of string
void* find_string_length(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*) arg;
    int length = strlen(args->string);
    printf("Length of string: %d\n", length);
    pthread_exit(NULL);
}

int main() {
    // Input string
    char string[MAX_STRING_LEN] = "Hello, world!";

    // Create thread arguments
    struct ThreadArgs args;
    args.string = string;

    // Create thread and pass arguments
    pthread_t thread;
    pthread_create(&thread, NULL, find_string_length, (void*) &args);

    // Wait for thread to finish
    pthread_join(thread, NULL);

    return 0;
}
