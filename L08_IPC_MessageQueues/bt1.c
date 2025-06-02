#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>

#define QUEUE_NAME "/simple_queue"
#define MAX_SIZE 1024
#define MSG "Hello from parent"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];
    pid_t pid;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        if (mq_send(mq, MSG, strlen(MSG) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
    } else {
        if (mq_receive(mq, buffer, MAX_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        printf("Child received: %s\n", buffer);
    }

    if (pid > 0) {
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
    } else {
        mq_close(mq);
    }

    return 0;
}