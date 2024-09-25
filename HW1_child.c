//
// Created by rcmpl on 25.09.2024.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Not enough arguments\n");
        exit(-1);
    }

    int fd = atoi(argv[1]);

    ssize_t sz = write(fd, "Hello, parent!", 15);

    if(sz != 15) {
        printf("Couldn't write all string\n");
        exit(-1);
    }

    if(close(fd) < 0) {
        printf("Couldn't close file\n");
        exit(-1);
    }

    printf("Written to fd successfully\n");
}