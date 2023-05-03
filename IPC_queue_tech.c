#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define a message structure
struct message {
    long type;
    char text[100];
};

int main() {
    // Generate a unique key for the message queue
    key_t key = ftok(".", 'a');

    // Create a message queue and obtain a message queue identifier
    int mq_id = msgget(key, 0666 | IPC_CREAT);

    if (mq_id == -1) {
        perror("msgget");
        exit(1);
    }

    // Create a message buffer to hold incoming messages
    struct message buffer;

    // Fork a child process to send a message
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process sending message...\n");

        // Fill the message buffer with data
        buffer.type = 1;
        strcpy(buffer.text, "Hello from the child process!");

        // Send the message to the message queue
        if (msgsnd(mq_id, &buffer, sizeof(buffer.text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Message sent.\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process waiting for message...\n");

        // Wait for a message to arrive in the message queue
        if (msgrcv(mq_id, &buffer, sizeof(buffer.text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Message received: %s\n", buffer.text);
        exit(0);
    }
}
