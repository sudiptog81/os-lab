/**
 * Write a program to implement non-preemptive priority
 * based scheduling algorithm.
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <stdio.h>
#include <stdlib.h>

struct process
{
  int pid;
  double priority;
  double burstTime;
  double arrivalTime;
  double waitingTime;
  double turnAroundTime;
};

int comparisonDesc(const void *a, const void *b)
{
  return ((struct process *)a)->priority < ((struct process *)b)->priority;
}

int comparisonAsc(const void *a, const void *b)
{
  return ((struct process *)a)->pid > ((struct process *)b)->pid;
}

void computeWaitingTime(struct process *processes, int processCount)
{
  qsort(processes, processCount, sizeof(struct process), comparisonDesc);
  processes[0].waitingTime = 0;
  for (int i = 0; i < processCount - 1; i++)
    processes[i + 1].waitingTime =
        processes[i].burstTime +
        processes[i].waitingTime -
        processes[i].arrivalTime;
  return;
}

void computeTurnAroundTime(struct process *processes, int processCount)
{
  for (int i = 0; i < processCount; i++)
    processes[i].turnAroundTime =
        processes[i].burstTime +
        processes[i].waitingTime -
        processes[i].arrivalTime;
  qsort(processes, processCount, sizeof(struct process), comparisonAsc);
  return;
}

void printAverageTimes(struct process *processes, int processCount, char *unit)
{
  double totalWaitingTime = 0.0;
  double totalTurnAroundTime = 0.0;
  computeWaitingTime(processes, processCount);
  computeTurnAroundTime(processes, processCount);
  printf("Process ID\tPriority\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");
  printf("--------------------------------------------------------");
  printf("-----------------------------------------\n");
  for (int i = 0; i < processCount; i++)
  {
    totalWaitingTime += processes[i].waitingTime;
    totalTurnAroundTime += processes[i].turnAroundTime;
    printf("%d\t\t%.2lf\t\t%.2lf%s\t\t%.2lf%s\t\t%.2lf%s\t\t%.2lf%s\n",
           processes[i].pid, processes[i].priority,
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
  int processCount;
  char unit[4] = {'\0'};

  printf("Enter Time Unit: ");
  fgets(unit, 3, stdin);

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
    printf("Priority for Process %i: ", i + 1);
    scanf("%lf", &processes[i].priority);
  }

  printf("\n");

  printAverageTimes(processes, processCount, unit);

  return 0;
}