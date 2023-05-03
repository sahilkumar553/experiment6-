#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>



int main() {

    pid_t pid1, pid2, pid3, pid4, pid5;



    pid1 = getpid();

    printf("P1 process id: %d, parent id: %d\n", pid1, getppid());



    pid2 = fork();

    if (pid2 == 0) {

        pid2 = getpid();

        printf("P2 process id: %d, parent id: %d\n", pid2, getppid());



        pid4 = fork();

        if (pid4 == 0) {

            pid4 = getpid();

            printf("P4 process id: %d, parent id: %d\n", pid4, getppid());

            sleep(10); // simulate orphan process

            printf("P4 process id: %d is now orphaned\n", pid4);

        } else {

            pid5 = fork();

            if (pid5 == 0) {

                pid5 = getpid();

                printf("P5 process id: %d, parent id: %d\n", pid5, getppid());

                exit(0); // simulate zombie process

            }

        }



        waitpid(pid4, NULL, 0); // wait for orphan process to finish

        waitpid(pid5, NULL, 0); // wait for zombie process to finish

    } else {

        pid3 = fork();

        if (pid3 == 0) {

            pid3 = getpid();

            printf("P3 process id: %d, parent id: %d\n", pid3, getppid());

        }

    }



    return 0;

}
