#include <stdio.h>

int sum(int num)
{
  int sum = 0;
  while (num > 0)
  {
    sum += num % 10;
    num /= 10;
  }
  return sum;
}

int main(void)
{
  int num;
  printf("Give a number: ");
  scanf("%d", &num);

  printf("Sum of %d is %d\n", num, sum(num));

  return 0;
}
