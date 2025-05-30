#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s filename num-bytes [r/w] \"content\"\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    char mode = argv[3][0];
    char *content = argv[4];

    int fd;
    if (mode == 'w') {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening file for writing");
            return 1;
        }

        int bytes_to_write = num_bytes < strlen(content) ? num_bytes : strlen(content);
        if (write(fd, content, bytes_to_write) == -1) {
            perror("Error writing to file");
            close(fd);
            return 1;
        }
        printf("Wrote %d bytes to %s\n", bytes_to_write, filename);
    } else if (mode == 'r') {
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Error opening file for reading");
            return 1;
        }

        char buffer[1024];
        int bytes_read = read(fd, buffer, num_bytes);
        if (bytes_read == -1) {
            perror("Error reading from file");
            close(fd);
            return 1;
        }

        buffer[bytes_read] = '\0';
        printf("Read %d bytes from %s: %s\n", bytes_read, filename, buffer);
    } else {
        fprintf(stderr, "Invalid mode. Use 'r' for read or 'w' for write.\n");
        return 1;
    }

    close(fd);
    return 0;
}