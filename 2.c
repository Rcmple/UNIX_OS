#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char* argv[], char* envp[]) {
    int ind = 0;
    double a;
    ind = 0;
    int flag = 0;
    while(envp[ind]) {
        if(strstr(envp[ind], "NUM=")) {
            a = atof(envp[ind] + 4);
            flag = 1;
            break;
        }
        ind++;
    }
    if(!flag) {
        printf("Вы не задали число из которого нужно извлекать корень\n");
        return 0;
    }
    if(a >= 0) {
        double eps = 0.000001;
        double prev;
        double cur = 100;
        do {
            prev = cur;
            cur = 0.5 * (prev + a / prev);
        } while(fabs(cur - prev) >= eps);
        printf("%lf\n", cur);
    } else{
        printf("Вы вводите отрицательное число\n");
    }
}
