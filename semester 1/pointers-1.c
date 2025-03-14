#include <stdio.h>

#define N 10

int main(void)
{
  int A[N] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 9};

  for (int i = 0; i < N; i++)
  {
    printf("A[%d] = %d, %d\n", i, *(A + i), A[i]);
  }

  return 0;
}
