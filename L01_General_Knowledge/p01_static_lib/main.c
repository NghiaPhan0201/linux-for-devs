#include <stdio.h>
#include "calc.h"

int main(void)
{
    int a = 20;
    int b = 5;

    printf("Add: %d + %d = %d\n", a, b, add(a, b));
    printf("Sub: %d - %d = %d\n", a, b, sub(a, b));
    printf("Mul: %d * %d = %d\n", a, b, mul(a, b));
    printf("Div: %d / %d = %.2f\n", a, b, divide(a, b));

    return 0;
}
