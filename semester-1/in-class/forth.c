#include <stdio.h>

int main(void) {
    float a, b, u;
    printf("Give base a: ");
    scanf("%f", &a);
    printf("Give base b: ");
    scanf("%f", &b);
    printf("Give height: ");
    scanf("%f", &u);
    if (a <= 0 || b <= 0 || u <= 0) {
        printf("One or more of your input values are incorrect. Try again!\n");
        return 1;
    }
    printf("Shape with base a %.2f, base b %.2f and height %.3f has area %.4f.\n", a, b, u, 0.5 * (a+b) * u);
    return 0;
  }
