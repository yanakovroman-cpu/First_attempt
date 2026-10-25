#include <stdio.h>
#include <locale.h>
#include <limits.h>

int main(void) {
    int a, b;
    a = getchar();
    b = getchar();
    printf("%d %d", a, b);
    return 0;
}