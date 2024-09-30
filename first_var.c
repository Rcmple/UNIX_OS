//
// Created by rcmpl on 29.09.2024.
//
#define _GNU_SOURCE
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd[2];

    if(pipe2(fd, O_NONBLOCK) == -1) {
        perror("pipe2");
        return 1;
    }

    int cnt_of_bytes = 0;
    int stop = 0;

    while(!stop) {
        if(write(fd[1], "c", 1) > 0) {
            cnt_of_bytes++;
        } else {
            stop = 1;
        }
    }

    if(close(fd[0]) < 0) {
        printf("Error with closing fd[0]\n");
        exit(-1);
    }

    if(close(fd[1]) < 0) {
        printf("Error with closing fd[1]\n");
        exit(-1);
    }

    printf("Count of bytes: %d\n", cnt_of_bytes);
}
