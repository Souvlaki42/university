#include <stdio.h>

int main(void) {
    float x, y, max, min;
    printf("Give number x: ");
    scanf("%f", &x);
    printf("Give number y: ");
    scanf("%f", &y);
    if (x == y) {
        printf("The two inputs are identical.\n");
        return 0;
    }

    if (x > y) {
        max = x;
        min = y;
    } else {
        max = y;
        min = x;
    }

    printf("The biggest number is %.2f and the smallest is %.2f\n", max, min);
    return 0;
  }
