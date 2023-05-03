#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>



int main() {

    pid_t pid1, pid2, pid3;



    pid1 = getpid();

    printf("P1 process id: %d, parent id: %d\n", pid1, getppid());



    pid2 = fork();

    if (pid2 == 0) {

        pid2 = getpid();

        printf("P2 process id: %d, parent id: %d\n", pid2, getppid());



        pid3 = fork();

        if (pid3 == 0) {

            pid3 = getpid();

            printf("P3 process id: %d, parent id: %d\n", pid3, getppid());

        }

    }



    return 0;

}
