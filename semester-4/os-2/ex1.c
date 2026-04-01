#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t fork_log(int id) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork() failed");
    exit(2);
  }
  if (pid == 0)
    printf("I'm P%d: pid=%d, parent_pid=%d\n", id, getpid(), getppid());
  return pid;
}

int main() {
  printf("I'm P0: pid=%d, parent_pid=%d\n", getpid(), getppid());
  int status, children_count;

  printf("Give the number of children for process 2: ");
  scanf("%d", &children_count);
  printf("\n");

  pid_t pid1 = fork_log(1);
  if (pid1 > 0) {
    pid_t pid2 = fork_log(2);

    if (pid2 > 0) {
      while (waitpid(pid1, &status, 0) > 0)
        ;
      printf("Child process exitted with status: %d\n", status);
      execl("/bin/cat", "cat", __FILE__, NULL);
    }

    int children = 0;
    if (pid2 == 0) {
      while (children < children_count) {
        children++;
        pid_t pid = fork_log(3 + children);
        if (pid == 0)
          return 0;
      }

      int finished = 0;
      while (finished < 2) {
        pid_t pid = wait(&status);
        if (pid < 0)
          break;
        if (pid > 0) {
          finished++;
          printf("Child %d just finished!\n", pid);
        }
      }

      return 0;
    }
  }

  if (pid1 == 0) {
    int pipefd[2];
    char buff[21];

    if (pipe(pipefd) < 0) {
      perror("pipe() failed");
      return 2;
    }
    pid_t pid3 = fork_log(3);
    if (pid3 == 0) {
      if (write(pipefd[1], "hello from your child", 21) != 21) {
        perror("pipe write() failed");
        return 2;
      }
      return 0;
    }

    if (pid3 > 0) {
      while (waitpid(pid3, &status, 0) > 0)
        ;
      if (read(pipefd[0], buff, sizeof(buff)) <= 0) {
        perror("pipe read() failed");
        return 2;
      }

      printf("%s\n", buff);
    }
  }

  return 0;
}
