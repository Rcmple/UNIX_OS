//
// Created by rcmpl on 29.09.2024.
//
#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd[2];

    if(pipe(fd) == -1) {
        printf("Cant open pipe\n");
        exit(-1);
    }

    ssize_t sz = fcntl(fd[1], F_GETPIPE_SZ);

    if(close(fd[0]) < 0) {
        printf("Error with closing fd[0]\n");
        exit(-1);
    }

    if(close(fd[1]) < 0) {
        printf("Error with closing fd[1]\n");
        exit(-1);
    }

    printf("Size of pipe: %zu\n", sz);
}
