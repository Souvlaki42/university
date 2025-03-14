#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10

int main(void)
{
  int i, A, B, C, F;
  float m, s, sum, var, grade[N];

  for (i = 0, sum = 0.0; i < N; i++)
  {
    printf("\nPlease enter grade[%d]: ", i);
    scanf("%f", &grade[i]);
    sum += grade[i];
  }

  m = sum / N; /* mean of student grades */

  for (i = 0, var = 0.0; i < N; i++)
    var += (grade[i] - m) * (grade[i] - m);
  var = var / N; /* variance of student grades */
  s = sqrt(var); /* standard deviation of student grades */

  for (i = 0, A = B = C = F = 0; i < N; i++)
    if (grade[i] >= m + s)
      A++;
    else if (grade[i] >= m)
      B++;
    else if (grade[i] >= m - s)
      C++;
    else
      F++;

  printf("\n\n");
  printf("Mean: %.1f - Standard Deviation: %.1f\n\n", m, s);
  printf("A: %d (%.f%%)\n", A, 100.0 * A / N);
  printf("B: %d (%.f%%)\n", B, 100.0 * B / N);
  printf("C: %d (%.f%%)\n", C, 100.0 * C / N);
  printf("F: %d (%.f%%)\n", F, 100.0 * F / N);

  system("pause");
  return 0;
}
