/**
 * Write a program to implement FCFS scheduling algorithm.
 *
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct process {
  int pid;
  double burstTime;
  double arrivalTime;
  double waitingTime;
  double turnAroundTime;
};

void computeWaitingTime(struct process *processes, int processCount) {
  double completionTime = 0.0;
  processes[0].waitingTime = 0.0;
  for (int i = 1; i < processCount; i++) {
    completionTime += processes[i - 1].burstTime;
    processes[i].waitingTime = completionTime - processes[i].arrivalTime;
  }
  return;
}

void computeTurnAroundTime(struct process *processes, int processCount) {
  for (int i = 0; i < processCount; i++)
    processes[i].turnAroundTime =
        processes[i].burstTime + processes[i].waitingTime;
  return;
}

void printAverageTimes(struct process *processes, int processCount,
                       char *unit) {
  double totalWaitingTime = 0.0;
  double totalTurnAroundTime = 0.0;
  double completionTimes[MAX_SIZE] = {0.0};
  computeWaitingTime(processes, processCount);
  computeTurnAroundTime(processes, processCount);
  printf(
      "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");
  printf("--------------------------------------------------------");
  printf("-------------------------\n");
  for (int i = 0; i < processCount; i++) {
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

int main(void) {
  int processCount;
  char unit[4] = {'\0'};

  printf("Enter Time Unit: ");
  fgets(unit, 3, stdin);

  printf("Enter Number of Processes: ");
  scanf("%i", &processCount);

  struct process processes[processCount];

  for (int i = 0; i < processCount; i++) {
    processes[i].pid = i + 1;
    printf("Burst Time for Process %i: ", i + 1);
    scanf("%lf", &processes[i].burstTime);
    printf("Arrival Time for Process %i: ", i + 1);
    scanf("%lf", &processes[i].arrivalTime);
  }

  printf("\n");

  printAverageTimes(processes, processCount, unit);

  return 0;
}