#include <stdio.h>
#include <unistd.h>

int main(int agrc, char** argv) {
    printf("UID: %d GID: %d\n", getuid(), getgid());
    return 0;
}
