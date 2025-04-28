#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main(void)
{
  srand(time(NULL));

  printf("Random numbers: ");
  int A[N];

  for (int i = 0; i < N; i++)
  {
    A[i] = rand() % 49 + 1;
  }

  for (int i = 0; i < N; i++)
  {
    printf("%d ", A[i]);
  }

  return 0;
}