#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SOCKET "/tmp/numsok"

int main(void)
{
  struct sockaddr_un addr;
  int sock, length, *msgs;
  char response[BUFFER_SIZE];

  addr.sun_family = AF_LOCAL;
  strncpy(addr.sun_path, SOCKET, sizeof(addr.sun_path) - 1);

  sock = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (sock == -1)
  {
    printf("Failed to create socket\n");
    return 1;
  }

  if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0)
  {
    close(sock);
    printf("Failed to connect to socket\n");
    return 1;
  }

  while (1)
  {
    printf("Give array length (pass 0 to exit): ");
    scanf("%d", &length);
    if (length == 0)
    {
      printf("Exitting\n");
      close(sock);
      return 0;
    }

    msgs = (int *)malloc(sizeof(int) * length);

    printf("Give number array: ");
    for (int i = 0; i < length; i++)
    {
      scanf("%d", &msgs[i]);
    }

    if (write(sock, &length, sizeof(int)) < 0)
    {
      printf("Failed to write array size\n");
    }

    if (write(sock, msgs, sizeof(int) * length) < 0)
    {
      printf("Failed to write array data\n");
    }

    if (read(sock, response, BUFFER_SIZE) < 0)
    {
      printf("Failed to read server response\n");
    }
    else
    {
      printf("Server responded with \"%s\"\n", response);
    }
  }
}
