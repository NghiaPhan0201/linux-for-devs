#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "../include/chat_app.h"

int validate_ip(const char *ip) {
    regex_t regex;
    if (regcomp(&regex, "^([0-9]{1,3}\\.){3}[0-9]{1,3}$", REG_EXTENDED) != 0) {
        return 0;
    }
    if (regexec(&regex, ip, 0, NULL, 0) != 0) {
        regfree(&regex);
        return 0;
    }
    regfree(&regex);

    int parts[4];
    sscanf(ip, "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]);
    for (int i = 0; i < 4; i++) {
        if (parts[i] < 0 || parts[i] > 255) return 0;
    }
    return 1;
}

void trim(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == ' ')) {
        str[--len] = '\0';
    }
    int start = 0;
    while (str[start] == ' ') start++;
    if (start > 0) memmove(str, str + start, len - start + 1);
}