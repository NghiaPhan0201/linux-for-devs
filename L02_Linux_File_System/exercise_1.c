#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("testfile.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error seeking file");
        close(fd);
        return 1;
    }

    char data[] = "Hello, this is a test!\n";
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    close(fd);
    printf("Data has been written. Check the file content.\n");
    return 0;
}
