#include <stdio.h>

int main(void)
{
  int x, y, z;
  x = 3;
  y = 5;
  z = x + y;

  printf("%d + %d = %d\n", x, y, z);
  printf("%d - %d = %d\n", x, y, x - y);

  return 0;
}
