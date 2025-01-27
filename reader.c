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


int main() {
    int shmid;
    char cur_file[] = "writer.c";
    key_t key;

    if ((key = ftok(cur_file, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, 0, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Can't create shared memory\n");
            exit(-1);
        } else {
            if ((shmid = shmget(key, 0, 0)) < 0) {
                printf("Can't find shared memory\n");
                exit(-1);
            }
        }
    }
    char* buf;
    if((buf = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    printf("writer.c code:%s\n", buf);

    if(shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Can't delete shared memory\n");
        exit(-1);
    }
}
