#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>



int main() {

    pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7;



    // Create P1 process

    pid1 = getpid();

    printf("Process P1 created with id %d and parent id %d\n", pid1, getppid());



    // Create P2 process

    pid2 = fork();

    if (pid2 == 0) {

        pid3 = fork();

        if (pid3 == 0) {

            pid4 = fork();

            if (pid4 == 0) {

                printf("Process P4 created with id %d and parent id %d\n", getpid(), getppid());

                sleep(10);  // simulate orphan process

                exit(0);

            } else {

                wait(NULL);  // wait for P4 to terminate

                printf("Process P3 created with id %d and parent id %d\n", getpid(), getppid());

                exit(0);

            }

        } else {

            wait(NULL);  // wait for P3 to terminate

            printf("Process P2 created with id %d and parent id %d\n", getpid(), getppid());

            exit(0);

        }

    }



    // Create P5 process

    pid5 = fork();

    if (pid5 == 0) {

        pid6 = fork();

        if (pid6 == 0) {

            pid7 = fork();

            if (pid7 == 0) {

                printf("Process P7 created with id %d and parent id %d\n", getpid(), getppid());

                exit(0);

            } else {

                sleep(5);  // simulate zombie process

                printf("Process P6 created with id %d and parent id %d\n", getpid(), getppid());

                exit(0);

            }

        } else {

            wait(NULL);  // wait for P6 to terminate

            printf("Process P5 created with id %d and parent id %d\n", getpid(), getppid());

            exit(0);

        }

    }



    wait(NULL);  // wait for P2 and P5 to terminate

    printf("Process P1 exiting\n");

    exit(0);

}
