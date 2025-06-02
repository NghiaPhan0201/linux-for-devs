#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>

#define QUEUE_SEND "/send_queue"
#define QUEUE_RECV "/recv_queue"
#define MAX_SIZE 1024
#define MSG "Hello from parent"

int main() {
    mqd_t mq_send, mq_recv;
    struct mq_attr attr;
    char buffer[MAX_SIZE];
    int count;
    pid_t pid;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq_send = mq_open(QUEUE_SEND, O_CREAT | O_RDWR, 0644, &attr);
    if (mq_send == (mqd_t)-1) {
        perror("mq_open send");
        exit(EXIT_FAILURE);
    }

    mq_recv = mq_open(QUEUE_RECV, O_CREAT | O_RDWR, 0644, &attr);
    if (mq_recv == (mqd_t)-1) {
        perror("mq_open recv");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        if (mq_send(mq_send, MSG, strlen(MSG) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

        if (mq_receive(mq_recv, buffer, MAX_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        sscanf(buffer, "%d", &count);
        printf("Parent received count: %d\n", count);
    } else {
        if (mq_receive(mq_send, buffer, MAX_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        count = strlen(buffer);
        snprintf(buffer, MAX_SIZE, "%d", count);
        if (mq_send(mq_recv, buffer, strlen(buffer) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
    }

    if (pid > 0) {
        mq_close(mq_send);
        mq_close(mq_recv);
        mq_unlink(QUEUE_SEND);
        mq_unlink(QUEUE_RECV);
    } else {
        mq_close(mq_send);
        mq_close(mq_recv);
    }

    return 0;
}