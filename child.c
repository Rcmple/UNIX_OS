#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main()
{
    int     fd;
    ssize_t  size;
    char    name[] = "aaa.fifo";

    (void)umask(0);

    if (mkfifo(name, 0666) < 0) {
        if(errno == EEXIST) {
            printf("FIFO already exists\n");
        } else {
            printf("Can\'t open FIFO for reading++++\n");
            exit(-1);
        }
    }

    if ((fd = open(name, O_WRONLY)) < 0) {
        printf("Can\'t open FIFO for writting\n");
        exit(-1);
    }

    size = write(fd, "Hello, world!", 14);

    if (size != 14) {
        printf("Can\'t write all string to FIFO\n");
        exit(-1);
    }

    if (close(fd) < 0) {
        printf("Can\'t close FIFO\n");
        exit(-1);
    }

    printf("Success\n");
    return 0;
}
