//
// Created by rcmpl on 14.10.2024.
//
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main()
{
    int N;
    scanf("%d", &N);
    size_t size;
    int fd[2], result, semid;
    char pathname[] = "1.c";
    struct sembuf mybuf;
    key_t key;

    if((key = ftok(pathname, 0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get semid\n");
        exit(-1);
    }

    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else {
        while(N--) {
            if(result > 0) {
                char  res_str_par[15];
                size = write(fd[1], "Hello, child!", 14);
                if(size != 14){
                    printf("Can\'t write all string to pipe\n");
                    exit(-1);
                }
                mybuf.sem_op = 2;
                mybuf.sem_flg = 0;
                mybuf.sem_num = 0;
                if(semop(semid, &mybuf, 1) < 0){
                    printf("Can\'t wait for condition\n");
                    exit(-1);
                }
                mybuf.sem_op = 0;
                mybuf.sem_flg = 0;
                mybuf.sem_num = 0;
                if(semop(semid, &mybuf, 1) < 0){
                    printf("Can\'t wait for condition\n");
                    exit(-1);
                }
                size = read(fd[0], res_str_par, 15);

                if(size != 15) {
                    printf("Can\'t read string from pipe\n");
                    exit(-1);
                }
                printf("Parent: %s\n", res_str_par);
            } else {
                char res_str_child[14];
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;
                mybuf.sem_num = 0;
                if(semop(semid, &mybuf, 1) < 0){
                    printf("Can\'t wait for condition\n");
                    exit(-1);
                }
                size = read(fd[0], res_str_child, 14);
                if(size != 14) {
                    printf("Can\'t read string from pipe\n");
                    exit(-1);
                }
                printf("Child: %s\n", res_str_child);

                size = write(fd[1], "Hello, parent!", 15);
                if(size != 15){
                    printf("Can\'t write all string to pipe\n");
                    exit(-1);
                }
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;
                mybuf.sem_num = 0;
                if(semop(semid, &mybuf, 1) < 0){
                    printf("Can\'t wait for condition\n");
                    exit(-1);
                }
            }
        }
    }
    return 0;
}
