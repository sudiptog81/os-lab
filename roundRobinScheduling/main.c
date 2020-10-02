/**
 * Write a program to implement Round Robin scheduling algorithm.
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <stdio.h>
#include <stdlib.h>

struct process
{
  int pid;
  double burstTime;
  double arrivalTime;
  double waitingTime;
  double turnAroundTime;
};

void computeWaitingTime(struct process *processes, int processCount, int quantum)
{
  double remainingTime[processCount];
  for (int i = 0; i < processCount; i++)
    remainingTime[i] = processes[i].burstTime;
  double time = 0.0;
  while (1)
  {
    int done = 1;
    for (int i = 0; i < processCount; i++)
    {
      if (remainingTime[i] > 0)
      {
        done = 0;
        if (remainingTime[i] > quantum)
        {
          time += quantum;
          remainingTime[i] -= quantum;
        }
        else
        {
          time += remainingTime[i];
          processes[i].waitingTime += time - processes[i].arrivalTime - processes[i].burstTime;
          remainingTime[i] = 0;
        }
      }
    }
    if (done == 1)
      break;
  }
  return;
}

void computeTurnAroundTime(struct process *processes, int processCount)
{
  for (int i = 0; i < processCount; i++)
    processes[i].turnAroundTime =
        processes[i].burstTime +
        processes[i].waitingTime -
        processes[i].arrivalTime;
  return;
}

void printAverageTimes(struct process *processes, int processCount, int quantum, char *unit)
{
  double totalWaitingTime = 0.0;
  double totalTurnAroundTime = 0.0;
  computeWaitingTime(processes, processCount, quantum);
  computeTurnAroundTime(processes, processCount);
  printf("Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");
  printf("--------------------------------------------------------");
  printf("-------------------------\n");
  for (int i = 0; i < processCount; i++)
  {
    totalWaitingTime += processes[i].waitingTime;
    totalTurnAroundTime += processes[i].turnAroundTime;
    printf("%d\t\t%.2lf%s\t\t%.2lf%s\t\t%.2lf%s\t\t%.2lf%s\n", processes[i].pid,
           processes[i].burstTime, unit, processes[i].arrivalTime, unit,
           processes[i].waitingTime, unit, processes[i].turnAroundTime, unit);
  }
  printf("\nAverage Waiting Time = %.2lf%s", totalWaitingTime / processCount,
         unit);
  printf("\nAverage Turn-Around time = %.2lf%s\n",
         totalTurnAroundTime / processCount, unit);
  return;
}

int main(void)
{
  double quantum;
  int processCount;
  char unit[4] = {'\0'};

  printf("Enter Time Unit: ");
  fgets(unit, 3, stdin);

  printf("Enter Time Quantum: ");
  scanf("%lf", &quantum);

  printf("Enter Number of Processes: ");
  scanf("%i", &processCount);

  struct process processes[processCount];

  for (int i = 0; i < processCount; i++)
  {
    processes[i].pid = i + 1;
    printf("Burst Time for Process %i: ", i + 1);
    scanf("%lf", &processes[i].burstTime);
    printf("Arrival Time for Process %i: ", i + 1);
    scanf("%lf", &processes[i].arrivalTime);
  }

  printf("\n");

  printAverageTimes(processes, processCount, quantum, unit);

  return 0;
}