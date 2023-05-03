#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *dir_name = "example_dir";
    char *file_name = "example_file.txt";
    char *file_path = "example_dir/example_file.txt";
    int fd;
    DIR *dirp;
    struct dirent *dirent_ptr;

    // Create directory
    if (mkdir(dir_name, 0777) != 0) {
        perror("mkdir");
        exit(1);
    }
    printf("Created directory '%s'\n", dir_name);

    // Create file inside directory
    fd = open(file_path, O_CREAT | O_RDWR, 0777);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("Created file '%s'\n", file_path);
    close(fd);

    // List contents of directory
    dirp = opendir(dir_name);
    if (dirp == NULL) {
        perror("opendir");
        exit(1);
    }
    printf("Contents of directory '%s':\n", dir_name);
    while ((dirent_ptr = readdir(dirp)) != NULL) {
        printf("  %s\n", dirent_ptr->d_name);
    }
    closedir(dirp);

    return 0;
}
