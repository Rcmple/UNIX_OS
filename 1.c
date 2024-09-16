#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Вы не ввели число из которого нужно извлечь корень\n");
        return 0;
    }
    double a;
    a  = atof(argv[1]);
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
