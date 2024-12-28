#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct
{
    int id;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    int isSystemProcess;
} Process;

void inputProcesses(Process processes[], int n);
void sortProcesses(Process processes[], int n);
void calculateWaitingAndTurnaroundTimes(Process processes[], int n);
void printGanttChart(Process processes[], int n);
float calculateAverageWaitingTime(Process processes[], int n);
float calculateAverageTurnaroundTime(Process processes[], int n);

int main()
{
    int n;
    Process processes[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    inputProcesses(processes, n);

    sortProcesses(processes, n);

    calculateWaitingAndTurnaroundTimes(processes, n);

    printGanttChart(processes, n);

    float averageWaitingTime = calculateAverageWaitingTime(processes, n);
    float averageTurnaroundTime = calculateAverageTurnaroundTime(processes, n);
    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);

    return 0;
}

void inputProcesses(Process processes[], int n)
{
    printf("Enter burst times of the processes: ");
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i;
        scanf("%d", &processes[i].burstTime);
    }

    printf("Enter arrival times of the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processes[i].arrivalTime);
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].isSystemProcess = 0;
    }

    int systemProcessCount;
    printf("Enter total number of system processes: ");
    scanf("%d", &systemProcessCount);
    printf("Enter system process IDs: ");
    for (int i = 0; i < systemProcessCount; i++)
    {
        int systemProcessId;
        scanf("%d", &systemProcessId);
        processes[systemProcessId].isSystemProcess = 1;
    }
}

void sortProcesses(Process processes[], int n)
{
    Process temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((processes[j].isSystemProcess < processes[j + 1].isSystemProcess) ||
                (processes[j].isSystemProcess == processes[j + 1].isSystemProcess &&
                 processes[j].arrivalTime > processes[j + 1].arrivalTime))
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculateWaitingAndTurnaroundTimes(Process processes[], int n)
{
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        currentTime += processes[i].burstTime; 
    }
}

void printGanttChart(Process processes[], int n)
{
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", processes[i].id);
    }
    printf("\n");
}

float calculateAverageWaitingTime(Process processes[], int n)
{
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
    }
    return (float)totalWaitingTime / n;
}

float calculateAverageTurnaroundTime(Process processes[], int n)
{
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    return (float)totalTurnaroundTime / n;
}
