#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    off_t input_size = lseek(input_fd, 0, SEEK_END);
    if (input_size == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    off_t output_size = input_size / 2;
    off_t output_offset = 0;

    int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    ssize_t nread;

    while ((nread = read(input_fd, buf, sizeof(buf))) > 0) {
        if (output_offset + nread > output_size) {
            nread = output_size - output_offset;
        }
        if (write(output_fd, buf, nread) != nread) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        output_offset += nread;
        if (output_offset == output_size) {
            break;
        }
    }

    if (nread == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (close(input_fd) == -1) {
        perror("close input");
        exit(EXIT_FAILURE);
    }

    if (close(output_fd) == -1) {
        perror("close output");
        exit(EXIT_FAILURE);
    }

    return 0;
}
