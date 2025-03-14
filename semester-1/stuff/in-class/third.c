#include <stdio.h>

#define PI 3.14159

int main(void) {
    float r;
    printf("Give radius: ");
    scanf("%f", &r);
    printf("Circle with radius %.2f with cicumferance %.3f and area %.4f\n", r, 2*PI*r, PI*r*r);
    return 0;
  }
