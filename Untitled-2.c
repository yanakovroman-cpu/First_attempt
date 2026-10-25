#include <stdio.h>

int main(void)
{
    double a, b, c, d, e, f;
    scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);
    double delta = a * e - d * b;
    double delta_x = c * e - f * b;
    double delta_y = a * f - d * c;
    
    // if (delta) {
    //     double x = delta_x / delta, y = delta_y / delta;
    //     printf("x = %.2lf\ny = %.2lf", x, y);
    // }
    // else {
    //     if (delta_x == 0 && delta_y == 0) {
    //         printf("There are infinitely many solutions.\n");
    //     }
    //     else {
    //         printf("There are no solutions.\n");
    //         }
    //     }
    

    int res = delta == 0, res_x = delta_x == 0, res_y = delta_y == 0;
    switch (res) {
        case 0:
                double x = delta_x / delta, y = delta_y / delta;
                printf("x = %lf\ny = %lf", x, y);
                break;
        case 1:
                switch (res_x + res_y) {
                    case 2:
                            printf("There are infinitely many solutions.\n");
                            break;
                    default:
                            printf("There are no solutions.\n");
                            break;
                }
                break;
    }
    return 0;
    }