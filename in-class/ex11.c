#include <stdio.h>

int main(void) {
  int num, sum = 0;
  printf("Give a number: ");
  scanf("%d", &num);
  int num_original = num;
  while (num % 10 != 0) {
    sum += num % 10;
    num /= 10;
  }
  printf("Sum of %d is %d\n", num_original, sum);
}
