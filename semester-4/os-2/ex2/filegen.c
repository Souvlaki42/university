#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_NAME "vectors.bin"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Proper use: generator <vector length>\n");
    return 1;
  }

  int vector_length = atoi(argv[1]);

  FILE *fptr = fopen(FILE_NAME, "wb");

  if (fptr == NULL)
  {
    printf("Failed to create file.\n");
    return 1;
  }

  // seed random generator
  srand(time(NULL));

  int *vector1 = malloc(sizeof(int) * vector_length);
  int *vector2 = malloc(sizeof(int) * vector_length);

  // generate random values
  for (int i = 0; i < vector_length; i++)
  {
    vector1[i] = rand() % 100;
    vector2[i] = rand() % 100;
  }

  // write vectors to binary file
  fwrite(vector1, sizeof(int), vector_length, fptr);
  fwrite(vector2, sizeof(int), vector_length, fptr);

  fclose(fptr);

  // optional: print vectors
  printf("Vector 1:\n");
  for (int i = 0; i < vector_length; i++)
  {
    printf("%d ", vector1[i]);
  }

  printf("\n\nVector 2:\n");
  for (int i = 0; i < vector_length; i++)
  {
    printf("%d ", vector2[i]);
  }

  printf("\n\nBinary file '%s' generated successfully.\n", FILE_NAME);

  free(vector1);
  free(vector2);

  return 0;
}
