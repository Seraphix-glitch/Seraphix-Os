#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct process_struct
{
    int pid;
    int bt;
    int at;
    int ct;
    int wt;
    int tat;
    int rt;
    int start_time;
} ps[100];
int totalIdleTime = 0;
int findMax(int a, int b);
int findMin(int a, int b);
void inputProcesses(int n);
void calculateTimes(int n);
void printResults(int n);
void calculateMetrics(int n);

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    inputProcesses(n);
    calculateTimes(n);
    printResults(n);
    calculateMetrics(n);
    return 0;
}

int findMax(int a, int b)
{
    return (a > b) ? a : b;
}

int findMin(int a, int b)
{
    return (a < b) ? a : b;
}

void inputProcesses(int n)
{
    for (int i = 0; i < n; i++)
    {
        ps[i].pid = i + 1;
        printf("Enter the process %d arrival Time: ", i + 1);
        scanf("%d", &ps[i].at);
        printf("Enter the process %d burst Time: ", i + 1);
        scanf("%d", &ps[i].bt);
    }
}

void calculateTimes(int n)
{
    bool isCompleted[100] = {false};
    int currentTime = 0, completed = 0, prev = 0;

    while (completed != n)
    {
        int minIndex = -1;
        int minimumBurstTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= currentTime && !isCompleted[i])
            {
                if (ps[i].bt < minimumBurstTime)
                {
                    minimumBurstTime = ps[i].bt;
                    minIndex = i;
                }
                else if (ps[i].bt == minimumBurstTime && ps[i].at < ps[minIndex].at)
                {
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1)
        {
            currentTime++;
        }
        else
        {
            ps[minIndex].start_time = currentTime;
            ps[minIndex].ct = ps[minIndex].start_time + ps[minIndex].bt;
            ps[minIndex].tat = ps[minIndex].ct - ps[minIndex].at;
            ps[minIndex].wt = ps[minIndex].tat - ps[minIndex].bt;
            ps[minIndex].rt = ps[minIndex].wt;

            completed++;
            isCompleted[minIndex] = true;
            currentTime = ps[minIndex].ct;
        }
    }
}

void printResults(int n)
{
    printf("\nProcess No.\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
}

void calculateMetrics(int n)
{
    int sumTat = 0, sumWt = 0, sumRt = 0;
    int maxCompletionTime = INT_MIN, minArrivalTime = INT_MAX;
    float cpuUtilization, throughput;

    for (int i = 0; i < n; i++)
    {
        sumTat += ps[i].tat;
        sumWt += ps[i].wt;
        sumRt += ps[i].rt;

        maxCompletionTime = findMax(maxCompletionTime, ps[i].ct);
        minArrivalTime = findMin(minArrivalTime, ps[i].at);
    }

    int lengthCycle = maxCompletionTime - minArrivalTime;

    cpuUtilization = (float)(lengthCycle - totalIdleTime) / lengthCycle;
    throughput = (float)n / lengthCycle;

    printf("\nAverage Turnaround Time = %.2f", (float)sumTat / n);
    printf("\nAverage Waiting Time = %.2f", (float)sumWt / n);
    printf("\nAverage Response Time = %.2f", (float)sumRt / n);
    printf("\nThroughput = %.2f", throughput);
    printf("\nCPU Utilization (Percentage) = %.2f%%", cpuUtilization * 100);
}