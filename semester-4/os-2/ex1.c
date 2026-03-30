#include <stdio.h>
#include <unistd.h>

pid_t fork_log(int id) {
  pid_t pid = fork();
  if (pid == 0)
    printf("I'm P%d: pid=%d, parent_pid=%d\n", id, getpid(), getppid());
  return pid;
}

int main() {
  pid_t pid1 = -1, pid2 = -1, pid3 = -1, pid4 = -1, pid5 = -1, pid6 = -1;
  printf("I'm P0: pid=%d, parent_pid=%d\n", getpid(), getppid());

  pid1 = fork_log(1);
  if (pid1 > 0) {
    pid2 = fork_log(2);

    if (pid2 == 0) {
      pid4 = fork_log(4);
      if (pid4 == 0)
        return 0;
      pid5 = fork_log(5);
      if (pid5 == 0)
        return 0;
      pid6 = fork_log(6);
      if (pid6 == 0)
        return 0;
      return 0;
    }
  }

  if (pid1 == 0) {
    pid3 = fork_log(3);
    return 0;
  }

  return 0;
}
