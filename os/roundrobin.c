#include <stdio.h>
#include <stdbool.h>

struct Process
{
  int id;
  int arrivalTime;
  int burstTime;
  int startTime;
  int finishTime;
  int waitingTime;
  int turnaroundTime;
};

int main()
{
  int numProcesses, quantum;

  printf("Enter the number of processes: ");
  scanf("%d", &numProcesses);

  struct Process processes[numProcesses];

  printf("Enter the quantum: ");
  scanf("%d", &quantum);

  printf("Enter the process numbers: ");
  for (int i = 0; i < numProcesses; i++)
  {
    scanf("%d", &(processes[i].id));
  }

  printf("Enter the Arrival time of processes: ");
  for (int i = 0; i < numProcesses; i++)
  {
    scanf("%d", &(processes[i].arrivalTime));
  }

  printf("Enter the Burst time of processes: ");
  for (int i = 0; i < numProcesses; i++)
  {
    scanf("%d", &(processes[i].burstTime));
  }

  int currentTime = 0;
  bool done = false;
  while (!done)
  {
    done = true; // Assume all processes are done
    for (int i = 0; i < numProcesses; i++)
    {
      if (processes[i].burstTime > 0)
      {
        done = false; // If any process is not done, set done to false
        int slice = (processes[i].burstTime < quantum) ? processes[i].burstTime : quantum;
        processes[i].burstTime -= slice;
        processes[i].startTime = currentTime;
        currentTime += slice;
        processes[i].finishTime = currentTime;
      }
    }
  }

  // Calculate waiting time and turnaround time
  for (int i = 0; i < numProcesses; i++)
  {
    processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
  }

  // Print the Gantt chart
  printf("\nGantt chart\n");
  printf("--------------------------------------------------------\n");
  for (int i = 0; i < numProcesses; i++)
  {
    printf("| P%d ", processes[i].id);
  }
  printf("|\n");
  printf("--------------------------------------------------------\n");

  // Print process details
  printf("\n| Process ID | Arrival Time | Burst Time | Start Time | Finish Time | Waiting Time | Turnaround Time |\n");
  for (int i = 0; i < numProcesses; i++)
  {
    printf("|     %2d     |      %3d      |     %3d    |     %3d     |      %3d      |      %3d      |        %3d       |\n",
           processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
           processes[i].startTime, processes[i].finishTime, processes[i].waitingTime,
           processes[i].turnaroundTime);
  }

  // Calculate and print average waiting time and turnaround time
  int totalWaitingTime = 0, totalTurnaroundTime = 0;
  for (int i = 0; i < numProcesses; i++)
  {
    totalWaitingTime += processes[i].waitingTime;
    totalTurnaroundTime += processes[i].turnaroundTime;
  }
  double avgWaitingTime = (double)totalWaitingTime / numProcesses;
  double avgTurnaroundTime = (double)totalTurnaroundTime / numProcesses;

  printf("\nAverage Waiting Time: %.2lf\n", avgWaitingTime);
  printf("Average Turnaround Time: %.2lf\n", avgTurnaroundTime);

  return 0;
}
