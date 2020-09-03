/**
 * Write a program to implement SJF scheduling algorithm.
 *
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct process {
  int pid;
  double burstTime;
  double arrivalTime;
  double waitingTime;
  double turnAroundTime;
};

void computeWaitingTime(struct process *processes, int processCount) {
  double remainingTime[processCount];

  for (int i = 0; i < processCount; i++)
    remainingTime[i] = processes[i].burstTime;

  double check = 0;
  double min = INT_MAX;
  double completionTime, time = 0;
  int complete = 0, shortest = 0;

  while (complete != processCount) {
    for (int j = 0; j < processCount; j++) {
      if ((processes[j].arrivalTime <= time) && (remainingTime[j] < min) &&
          remainingTime[j] > 0) {
        min = remainingTime[j];
        shortest = j;
        check = 1;
      }
    }

    if (check == 0) {
      time++;
      continue;
    }

    remainingTime[shortest]--;

    min = remainingTime[shortest];
    if (min == 0)
      min = INT_MAX;

    if (remainingTime[shortest] == 0) {
      complete++;
      check = 0;
      completionTime = time + 1;

      processes[shortest].waitingTime = completionTime -
                                        processes[shortest].burstTime -
                                        processes[shortest].arrivalTime;

      if (processes[shortest].burstTime < 0)
        processes[shortest].burstTime = 0;
    }

    time++;
  }
}

void computeTurnAroundTime(struct process *processes, int processCount) {
  for (int i = 0; i < processCount; i++)
    processes[i].turnAroundTime =
        processes[i].burstTime + processes[i].waitingTime;
}

void printAverageTimes(struct process *processes, int processCount,
                       char *unit) {
  double totalWaitingTime = 0.0;
  double totalTurnAroundTime = 0.0;
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