#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t s1, s2, s3;

void *msg_a(void *input)
{
  (void)input;
  for (;;)
  {
    sem_wait(&s1);
    printf("What A ");
    fflush(stdout);
    sem_post(&s2);
  }

  return (NULL);
}

void *msg_b(void *input)
{
  (void)input;
  for (;;)
  {
    sem_wait(&s2);
    printf("Wonderful ");
    fflush(stdout);
    sem_post(&s3);
  }

  return (NULL);
}

void *msg_c(void *input)
{
  (void)input;
  for (;;)
  {
    sem_wait(&s3);
    printf("World! ");
    fflush(stdout);
    sem_post(&s1);
  }

  return (NULL);
}

int main(void)
{
  pthread_t t1, t2, t3;

  if (sem_init(&s1, 0, 1) != 0)
  {
    printf("Failed to init semaphore 1\n");
    return 1;
  }

  if (sem_init(&s2, 0, 0) != 0)
  {
    printf("Failed to init semaphore 2\n");
    return 1;
  }

  if (sem_init(&s3, 0, 0) != 0)
  {
    printf("Failed to init semaphore 3\n");
    return 1;
  }

  if (pthread_create(&t1, NULL, msg_a, NULL) != 0)
  {
    printf("Failed to create thread 1\n");
    return 1;
  }

  if (pthread_create(&t2, NULL, msg_b, NULL) != 0)
  {
    printf("Failed to create thread 2\n");
    return 1;
  }

  if (pthread_create(&t3, NULL, msg_c, NULL) != 0)
  {
    printf("Failed to create thread 3\n");
    return 1;
  }

  if (pthread_join(t1, NULL) != 0)
  {
    printf("Failed to join thread 1\n");
    return 1;
  }

  if (pthread_join(t2, NULL) != 0)
  {
    printf("Failed to join thread 2\n");
    return 1;
  }

  if (pthread_join(t3, NULL) != 0)
  {
    printf("Failed to join thread 3\n");

    return 1;
  }

  if (sem_destroy(&s1) != 0)
  {
    printf("Failed to destroy semaphore 1\n");
    return 1;
  }

  if (sem_destroy(&s2) != 0)
  {
    printf("Failed to destroy semaphore 2\n");
    return 1;
  }

  if (sem_destroy(&s3) != 0)
  {
    printf("Failed to destroy semaphore 3\n");
    return 1;
  }

  return 0;
}
