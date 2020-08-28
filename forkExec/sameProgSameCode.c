/**
 * Write a program (using fork() and/or exec() commands)
 * where parent and child execute the same program, same
 * code.
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t pidFork = fork();

  if (pidFork < 0)
    fprintf(stderr, "Error in fork()");
  else
    printf("Process ID: %d\n", getpid());

  return 0;
}
