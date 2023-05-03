#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int file_descriptor, bytes_read;

    // Open the file for writing
    file_descriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (file_descriptor == -1) {
        perror("open");
        exit(1);
    }

    // Read input from the console until user enters '$'
    while (1) {
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);

        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }

        // Write input to file
        if (write(file_descriptor, buffer, bytes_read) == -1) {
            perror("write");
            exit(1);
        }

        // Exit loop if user enters '$'
        if (buffer[0] == '$') {
            break;
        }
    }

    // Close the file
    if (close(file_descriptor) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
