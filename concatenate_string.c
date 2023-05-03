#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_STRINGS 10
#define MAX_STRING_LEN 100

// Data structure to pass arguments to thread function
struct ThreadArgs {
    char** strings;
    int num_strings;
};

// Thread function to concatenate strings
void* concat_strings(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*) arg;
    char* result = (char*) malloc(MAX_STRINGS * MAX_STRING_LEN * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < args->num_strings; i++) {
        strcat(result, args->strings[i]);
    }
    printf("Concatenated string: %s\n", result);
    free(result);
    pthread_exit(NULL);
}

int main() {
    // Input strings
    char* strings[MAX_STRINGS] = {"Hello, ", "world!", " How are ", "you?"};
    int num_strings = 4;

    // Create thread arguments
    struct ThreadArgs args;
    args.strings = strings;
    args.num_strings = num_strings;

    // Create thread and pass arguments
    pthread_t thread;
    pthread_create(&thread, NULL, concat_strings, (void*) &args);

    // Wait for thread to finish
    pthread_join(thread, NULL);

    return 0;
}
