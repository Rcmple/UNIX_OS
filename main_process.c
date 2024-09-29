//
// Created by rcmpl on 29.09.2024.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd[2], res;
    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    res = fork();

    if (res < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (res > 0) {

        /* Parent process */
        if (close(fd[1]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
        }

        char to_str_fd[15];
        snprintf(to_str_fd, 15, "%d", fd[0]);
        execlp("./parent", "parent", to_str_fd, NULL);

        printf("Something went wrong in parent\n");
    } else {

        /* Child process */

        if (close(fd[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n"); exit(-1);
        }

        char to_str_fd[15];
        snprintf(to_str_fd, 15, "%d", fd[1]);
        execlp("./child", "child", to_str_fd, NULL);

        printf("Something went wrong in child\n");
    }

    return 0;
}
