#include <stdio.h>

#define N 10

void change(int *);
void display(int *);

int main(void)
{
  int A[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  change(A);
  putchar('\n');

  display(A);
  putchar('\n');

  return 0;
}

void display(int *A)
{
  for (int i = 0; i < N; i++)
  {
    printf("%d ", A[i]);
  }
}

void change(int *A)
{
  for (int i = 0; i < N; i++)
  {
    printf("%d ", A[i]);
    A[i] = A[i] * A[i];
  }
}