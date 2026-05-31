#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080

void handle(int connfd) {
  char buff[MAX];

  for (;;) {
    bzero(buff, MAX);

    read(connfd, buff, sizeof(buff));
    // print buffer which contains the client contents
    printf("Received: %s", buff);

    // and send that buffer to client
    write(connfd, buff, sizeof(buff));

    // if msg contains "exit" then server exit and chat ended.
    if (strncmp(buff, "exit", 4) == 0) {
      printf("Server exitted\n");
      break;
    }
  }
}

int main() {
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Socket creation failed\n");
    return 1;
  }

  printf("Socket successfully created\n");

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
    printf("Socket bind failed\n");
    return 1;
  }

  printf("Socket successfully binded\n");

  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed\n");
    return 1;
  }

  printf("Server listening at port %d\n", PORT);

  unsigned int len = sizeof(cli);

  connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
  if (connfd < 0) {
    printf("Server accept failed\n");
    return 1;
  }

  printf("Server accepted the client\n");

  handle(connfd);

  close(sockfd);
}
