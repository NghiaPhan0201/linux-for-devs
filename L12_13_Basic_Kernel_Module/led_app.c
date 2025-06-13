#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/led_device"

int main(int argc, char *argv[])
{
    int fd;
    char *command;

    // Kiểm tra đối số dòng lệnh
    if (argc != 2 || (strcmp(argv[1], "on") != 0 && strcmp(argv[1], "off") != 0)) {
        fprintf(stderr, "Usage: %s <on|off>\n", argv[0]);
        return 1;
    }

    command = argv[1];

    // Mở device file
    fd = open(DEVICE_PATH, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    // Ghi lệnh vào device
    if (write(fd, command, strlen(command)) < 0) {
        perror("Failed to write to device");
        close(fd);
        return 1;
    }

    printf("Command '%s' sent to device\n", command);
    close(fd);
    return 0;
}