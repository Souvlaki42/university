#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int *a;
  int *b;
  int length;
  long *result;
} thread_data;

void *calculate_product(void *ptr)
{
  long product = 0;
  thread_data *input = (thread_data *)ptr;
  for (int i = 0; i < input->length; i++)
  {
    product +=
        input->a[i] * input->b[i];
  }
  *(input->result) = product;
  return (NULL);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: %s <vector_length> <thread_count>\n", argv[0]);
    return 1;
  }

  int vector_length = atoi(argv[1]);
  int thread_count = atoi(argv[2]);

  if (vector_length % thread_count != 0)
  {
    printf("Vector length %d must by divisible by thread count %d\n", vector_length, thread_count);
    return 1;
  }

  int *vector1 = malloc(sizeof(int) * vector_length);
  int *vector2 = malloc(sizeof(int) * vector_length);
  long *products = malloc(sizeof(long) * thread_count);
  pthread_t *thread_ids = malloc(sizeof(pthread_t) * thread_count);
  thread_data *thread = malloc(sizeof(thread_data) * thread_count);

  int calculations_per_thread = vector_length / thread_count;
  long total_product = 0;

  FILE *fptr = fopen("vectors.bin", "rb");
  if (fptr == NULL)
  {
    printf("Failed to open the file\n");
    return 1;
  }

  if ((int)fread(vector1, sizeof(int), vector_length, fptr) != vector_length)
  {
    printf("Failed to read first vector\n");
    return 1;
  }

  if ((int)fread(vector2, sizeof(int), vector_length, fptr) != vector_length)
  {
    printf("Failed to read second vector\n");
    return 1;
  }

  fclose(fptr);

  for (int i = 0; i < thread_count; i++)
  {

    thread[i].a = &vector1[i * calculations_per_thread];
    thread[i].b = &vector2[i * calculations_per_thread];
    thread[i].length = calculations_per_thread;
    thread[i].result = &products[i];

    if (pthread_create(&thread_ids[i], NULL, calculate_product,
                       (void *)&thread[i]) != 0)
    {
      printf("Failed to create thread %d\n", i);
      return 1;
    }
  }

  for (int i = 0; i < thread_count; i++)
  {

    if (pthread_join(thread_ids[i], NULL) != 0)
    {
      printf("Failed to join thread %d\n", i);
      return 1;
    }
    total_product += products[i];
  }

  printf("Total product is %ld\n", total_product);

  free(vector1);
  free(vector2);
  free(thread);
  free(products);
  free(thread_ids);
  return 0;
}
