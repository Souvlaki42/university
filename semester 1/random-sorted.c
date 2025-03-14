#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main(void)
{
  srand(time(NULL));

  printf("Random numbers: ");
  int A[N];

  A[0] = rand() % 1000;
  for (int i = 1; i < N; i++)
  {
    do
      A[i] = rand() % 1000;
    while (A[i - 1] > A[i]);
  }

  for (int i = 0; i < N; i++)
  {
    printf("%d ", A[i]);
  }

  return 0;
}