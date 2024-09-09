#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t cur_proc = fork();
    if(cur_proc == -1) {
        printf("Error with process");
    } else if(cur_proc == 0) {
        printf("Ребенок:\n PID: %d\n PPID: %d\n", getpid(), getppid());
    } else {
        printf("Родитель:\n PID: %d\n PPID: %d %d\n", getpid(), getppid(), cur_proc);
    }
}

