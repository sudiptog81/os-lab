/**
 * Write a program (using fork() and/or exec() commands)
 * where before terminating, the parent waits for the 
 * child to finish its task.
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
  pid_t pidFork = fork();

  if (pidFork < 0)
    fprintf(stderr, "Error in fork()\n");
  else if (pidFork > 0)
  {
    wait(NULL);
    printf("PARENT: Child Exited\n");
  }
  else
  {
    printf("CHILD: Parent Process ID: %d\n", getppid());
    printf("CHILD: Process ID: %d\n", getpid());
    exit(0);
  }

  return 0;
}
