//
// Created by rcmpl on 29.09.2024.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("Not enough arguments\n");
        exit(-1);
    }
    char get_str[15];
    int fd = atoi(argv[1]);

    ssize_t sz = read(fd, get_str, 15);

    if(sz != 15) {
        printf("Can't read from pipe\n");
        exit(-1);
    }

    if(close(fd) < 0) {
        printf("Can't close reading side of pipe\n");
        exit(-1);
    }

    printf("Read from pipe: %s\n", get_str);
    return 0;
}
