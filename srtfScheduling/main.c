/**
 * Write a program to implement SRTF scheduling algorithm.
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

void sortByArrivalTime(struct process *processes, int processCount) {
  struct process temp;
  int i, j, n = processCount;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (processes[i].arrivalTime < processes[j].arrivalTime) {
        temp = processes[j];
        processes[j] = processes[i];
        processes[i] = temp;
      }
}

void sortForSJF(struct process *processes, int processCount) {
  struct process temp;
  double min, startTime = 0.0;
  int i, j, k = 1, n = processCount;
  for (j = 0; j < n; j++) {
    startTime += processes[j].burstTime;
    min = processes[k].burstTime;
    for (i = k; i < n; i++)
      if (startTime >= processes[i].arrivalTime &&
          processes[i].burstTime < min) {
        temp = processes[k];
        processes[k] = processes[i];
        processes[i] = temp;
      }
    k++;
  }
}

void sortByPID(struct process *processes, int processCount) {
  struct process temp;
  int i, j, n = processCount;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (processes[i].pid < processes[j].pid) {
        temp = processes[j];
        processes[j] = processes[i];
        processes[i] = temp;
      }
}

void computeWaitingTime(struct process *processes, int processCount) {
  double startTime = 0.0;
  processes[0].waitingTime = 0;
  for (int i = 1; i < processCount; i++) {
    startTime += processes[i - 1].burstTime;
    processes[i].waitingTime = startTime - processes[i].arrivalTime;
  }
}

void computeTurnAroundTime(struct process *processes, int processCount) {
  for (int i = 0; i < processCount; i++)
    processes[i].turnAroundTime =
        processes[i].burstTime + processes[i].waitingTime;
}

void printAverageTimes(struct process *processes, int processCount,
                       char *unit) {
  double end;
  int smallest, count = 0;
  double totalWaitingTime = 0.0;
  double totalTurnAroundTime = 0.0;
  struct process temp[processCount + 1];

  //   sortByArrivalTime(processes, processCount);
  //   sortForSJF(processes, processCount);
  //   computeWaitingTime(processes, processCount);
  //   computeTurnAroundTime(processes, processCount);
  //   sortByPID(processes, processCount);

  for (int i = 0; i < processCount; i++)
    temp[i] = processes[i];

  smallest = processCount + 1;
  temp[smallest].burstTime = 999;
  for (double time = 0; count != processCount; time++) {
    printf("%lf %d", time, count);
    for (int i = 0; i < processCount; i++) {
      if (processes[i].arrivalTime <= time &&
          processes[i].burstTime < temp[smallest].burstTime &&
          processes[i].burstTime > 0) {
        smallest = i;
      }
    }
    temp[smallest].burstTime--;
    if (temp[smallest].burstTime == 0) {
      count++;
      end = time + 1;
      processes[count].waitingTime +=
          end - processes[smallest].arrivalTime - temp[smallest].burstTime;
      processes[count].turnAroundTime += end - processes[smallest].arrivalTime;
    }
  }

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