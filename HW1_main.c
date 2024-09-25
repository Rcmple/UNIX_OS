#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd[2], res_of_fork;

    if(pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    res_of_fork = fork();
    if(res_of_fork < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if(res_of_fork > 0) {
        printf("Im in parent");
        if(close(fd[1]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        char fd_to_string[15];
        snprintf(fd_to_string, sizeof(fd_to_string), "%d", fd[0]);
        execlp("./reader", "reader", fd_to_string, NULL);

        printf("Something wrong with execlp in parent's process\n");
    } else {
        printf("Im in child");
        if(close(fd[0]) < 0) {
            printf("child: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        char fd_to_string[15];
        snprintf(fd_to_string, sizeof(fd_to_string), "%d", fd[1]);
        execlp("./writer", "writer", fd_to_string, NULL);

        printf("Something wrong with execlp in child's process\n");
    }
    return 0;
}
