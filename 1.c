#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[14];
    ssize_t sz;
    if((fd = open("myfile", O_RDONLY)) < 0)
    {
        printf("Cannot open file\n");
        exit(-1);
    }

    sz = read(fd, buf, 14);

    if(sz != 14) {
        printf("Cannot read all string\n");
        exit(-1);
    }

    if(close(fd) < 0) {
        printf("Cannot close file\n");
        exit(-1);
    }

    printf("Read from file: %s\n", buf);
    return 0;
}
