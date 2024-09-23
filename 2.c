#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd1[2], fd2[2], res;

    ssize_t sz1, sz2;
    char  res_str1[15], res_str2[14];

    if (pipe(fd1) < 0) {
        printf("Can\'t open pipe 1\n");
        exit(-1);
    }

    if (pipe(fd2) < 0) {
        printf("Can\'t open pipe 2\n");
        exit(-1);
    }

    res = fork();

    if (res < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (res > 0) {

        /* Parent process */

        if (close(fd1[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }

        if (close(fd2[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        //parent writting to pipe
        sz1 = write(fd1[1], "Hello, child!", 14);

        if (sz1 != 14) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        if (close(fd1[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
        }

        //parent reading from pipe
        sz1 = read(fd2[0], res_str1, 15);

        if(sz1 != 15) {
            printf("Cannot read all string\n");
            exit(-1);
        }

        if (close(fd2[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        printf("Parent's string from child: %s\n", res_str1);

    } else {

        /* Child process */

        if (close(fd1[1]) < 0) {
            printf("Child: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        if (close(fd2[0]) < 0) {
            printf("Child: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        ///child is writting to pipe
        sz2 = write(fd2[1], "Hello, parent!", 15);

        if (sz2 != 15) {
            printf("Can\'t write string to pipe\n");
            exit(-1);
        }

        if (close(fd2[1]) < 0) {
            printf("Child: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        //child is reading from pipe
        sz2 = read(fd1[0], res_str2, 14);

        if (sz2 != 14) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        if (close(fd1[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n"); exit(-1);
        }

        printf("Child's string from parent: %s\n", res_str2);
    }

    return 0;
}
