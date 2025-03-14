#include <stdio.h>

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main(void)
{
  int x = 3, y = 5;

  printf("Give me a number: ");
  scanf("%d", &x);

  printf("Give me another number: ");
  scanf("%d", &y);

  printf("x = %d, y = %d\n", x, y);

  swap(&x, &y);

  printf("x = %d, y = %d\n", x, y);

  return 0;
}