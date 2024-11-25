#include <stdio.h>

void printDiscount(float value, float discount) {
    printf("You purchased %.2f euros but, you have a discount of %.2f euros so, you'll need to pay only %.2f euros\n", value, discount, value - discount);
}

int main(void) {
    float value;
    printf("Give purchase value: ");
    scanf("%f", &value);
    if (value <= 0) {
         printf("You never bought anything!\n");
         return 1;
    } else if (value < 100) {
         printf("You purchase %f euros and you need to pay all of them!\n", value);
         return 0;
    } else if (value < 200) {
        printDiscount(value, value * 0.05);
        return 0;
    } else if (value < 300) {
        printDiscount(value, value * 0.1);
        return 0;
    } else if (value < 400) {
        printDiscount(value, value * 0.15);
        return 0;
    } else {
        printDiscount(value, value * 0.2);
        return 0;
    }
  }
