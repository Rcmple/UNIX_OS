#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    int     fd;
    ssize_t  size;

    char    res_str[14];
    char    name[] = "aaa.fifo";

    (void)umask(0);

    if (mkfifo(name, 0666) < 0) {
        if(errno == EEXIST) {
            printf("FIFO already exists\n");
        } else {
            printf("Can\'t open FIFO for reading\n");
            exit(-1);
        }
    }
    if((fd = open(name, O_RDONLY)) < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = read(fd, res_str, 14);

    if (size < 0) {
        printf("Can\'t read string from FIFO\n");
        exit(-1);
    }

    if (close(fd) < 0) {
        printf("Can\'t close FIFO\n"); exit(-1);
    }

    printf("res_str from child: %s\n", res_str);
    return 0;
}
