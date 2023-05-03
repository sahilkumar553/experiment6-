#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n, i, j;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("Child %d created\n", getpid());
            // Child process
            for (j = 0; j < 1000000000; j++) ; // simulate some work
            exit(0);
        }
    }

    // Parent process
    for (i = 0; i < n-1; i++) {
        wait(NULL);
    }

    printf("All child processes created\n");

    return 0;
}
