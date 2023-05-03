#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void copyFile(char *sourcePath, char *destPath) {
    int src_fd, dest_fd, readCount;
    char buf[1024];

    // Open the source file for reading
    src_fd = open(sourcePath, O_RDONLY);
    if (src_fd == -1) {
        printf("Failed to open file: %s\n", sourcePath);
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing
    dest_fd = open(destPath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        printf("Failed to create file: %s\n", destPath);
        exit(EXIT_FAILURE);
    }

    // Copy the contents of the source file to the destination file
    while ((readCount = read(src_fd, buf, sizeof(buf))) > 0) {
        write(dest_fd, buf, readCount);
    }

    // Close the source and destination files
    close(src_fd);
    close(dest_fd);
}

void copyDirectory(char *sourcePath, char *destPath) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char srcFilePath[1024], destFilePath[1024];

    // Create the destination directory
    mkdir(destPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    // Open the source directory for reading
    dir = opendir(sourcePath);
    if (dir == NULL) {
        printf("Failed to open directory: %s\n", sourcePath);
        exit(EXIT_FAILURE);
    }

    // Loop through all entries in the source directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            // Build the source and destination file paths
            sprintf(srcFilePath, "%s/%s", sourcePath, entry->d_name);
            sprintf(destFilePath, "%s/%s", destPath, entry->d_name);

            // Copy the file
            copyFile(srcFilePath, destFilePath);
        } else if (entry->d_type == DT_DIR) { // Directory
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Build the source and destination directory paths
            sprintf(srcFilePath, "%s/%s", sourcePath, entry->d_name);
            sprintf(destFilePath, "%s/%s", destPath, entry->d_name);

            // Recursively copy the directory
            copyDirectory(srcFilePath, destFilePath);
        }
    }

    // Close the source directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    char *sourcePath, *destPath;

    if (argc != 3) {
        printf("Usage: %s source_directory destination_directory\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sourcePath = argv[1];
    destPath = argv[2];

    // Copy the directory
    copyDirectory(sourcePath, destPath);

    printf("Directory copied successfully from %s to %s\n", sourcePath, destPath);

    return 0;
}
