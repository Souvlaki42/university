#include <stdio.h>

int main(void) {
  int rows, number = 1;
  printf("Give a number of rows: ");
  scanf("%d", &input);
  for (int i = 1; i <= input; i++)
    for (int y = 1; y <= i; y++) {
      printf("%4d ", y);
  return 0;
}
