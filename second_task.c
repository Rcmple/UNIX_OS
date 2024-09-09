#include <stdio.h>
#include <unistd.h>
#include <math.h>

int main(int agrc, char **argv) {
    double a;
    scanf("%lf", &a);
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
    return 0;
}