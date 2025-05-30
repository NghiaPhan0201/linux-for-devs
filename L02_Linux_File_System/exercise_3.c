#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main() {
    char *filename = "sample.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    char data[] = "This is a sample text for testing.\n";
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);

    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file info");
        return 1;
    }

    printf("File name: %s\n", filename);

    printf("File type: ");
    if (S_ISREG(file_stat.st_mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Symbolic link\n");
    } else {
        printf("Other\n");
    }

    char time_str[26];
    ctime_r(&file_stat.st_mtime, time_str);
    time_str[24] = '\0';
    printf("Last modified: %s\n", time_str);

    printf("File size: %ld bytes\n", (long)file_stat.st_size);

    return 0;
}