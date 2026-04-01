#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t fork_log(int id) {
  pid_t pid = fork();
  if (pid < 0)
    perror("fork() failed");
  if (pid == 0)
    printf("I'm P%d: pid=%d, parent_pid=%d\n", id, getpid(), getppid());
  return pid;
}

int main() {
  pid_t pid1, pid2, pid3, pid4, pid5, pid6, wpid;
  int status;

  printf("I'm P0: pid=%d, parent_pid=%d\n", getpid(), getppid());

  pid1 = fork_log(1);
  if (pid1 > 0) {
    pid2 = fork_log(2);

    if (pid2 > 0) {
      while ((wpid = waitpid(pid1, &status, 0)) > 0)
        ;
      printf("Child process exitted with status: %d\n", status);
      execl("/bin/cat", "cat", __FILE__, NULL);
    }

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
