#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SOCKET "/tmp/numsok"
#define CONNECTION_QUEUE_LENGTH 5

double calculateAverage(int *msgs, int length)
{
  double average = 0;

  for (int i = 0; i < length; i++)
  {
    average += (int)msgs[i];
  }
  average = average / length;

  return average;
}

void *serve(void *input)
{
  int client = *(int *)input;
  int length, *msgs;
  double average;
  char response[BUFFER_SIZE];

  free(input);

  for (;;)
  {
    if (read(client, &length, sizeof(int)) <= 0)
      break;

    msgs = malloc(sizeof(int) * length);

    if (read(client, msgs, sizeof(int) * length) < 0)
    {
      printf("Failed to read array data\n");
      free(msgs);
      break;
    }

    average = calculateAverage(msgs, length);
    if (average >= 50)
    {
      sprintf(response, "Check failed");
    }
    else
    {
      sprintf(response, "Sequence OK (Average is %.2f)", average);
    }

    write(client, response, strlen(response) + 1);

    free(msgs);
  }

  printf("Client %d exitted\n", client);
  close(client);

  return NULL;
}

int main(void)
{
  int sock, gets, accepted;
  struct sockaddr_un addr;
  pthread_t c_thread;

  unlink(SOCKET);

  addr.sun_family = AF_LOCAL;
  strncpy(addr.sun_path, SOCKET, sizeof(addr.sun_path));

  sock = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (sock == -1)
  {
    printf("Failed to create socket\n");
    return -1;
  }

  gets = bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
  if (gets == -1)
  {
    printf("Failed to bind socket\n");
    return -1;
  }

  listen(sock, CONNECTION_QUEUE_LENGTH);

  for (;;)
  {
    accepted = accept(sock, NULL, NULL);
    if (accepted == -1)
    {
      printf("Failed to accept socket\n");
    }
    else
    {
      printf("Client accepted at %d\n", accepted);
      int *client = malloc(sizeof(int));
      *client = accepted;
      pthread_create(&c_thread, NULL, serve, (void *)client);
      pthread_detach(c_thread);
    }
  }
}
