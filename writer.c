//
// Created by rcmpl on 30.09.2024.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char* cur_file = "writer.c";
    int fd = open(cur_file, O_RDONLY);
    if (fd < 0) {
        printf("Can't open file\n");
        exit(-1);
    }

    int shmid;
    key_t key;

    size_t sz = lseek(fd, 0, SEEK_END);
    (void)lseek(fd, SEEK_SET, 0);
    char* buf;

    if ((key = ftok(cur_file, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, sz, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Can't create shared memory\n");
            exit(-1);
        } else {
            if ((shmid = shmget(key, sz, 0)) < 0) {
                printf("Can't find shared memory\n");
                exit(-1);
            }
        }
    }

    if((buf = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    (void)read(fd, buf, sz + 1);

    if(close(fd) < 0) {
        printf("Can't close file\n");
        exit(-1);
    }
}
