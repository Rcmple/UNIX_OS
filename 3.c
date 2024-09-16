#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char* argv[], char *envp[]) {
    (void) execle("/bin/gcc", "/bin/gcc", "3.c", 0, envp);
    printf("Ошибка при старте программы\n");
}
