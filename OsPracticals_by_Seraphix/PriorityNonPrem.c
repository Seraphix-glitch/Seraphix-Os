#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct processStructure
{
    int id;
    int bt;
    int at;
    int priority;
    int ct;
    int tat;
    int wt;
    int rt;
    int startTime;
} ps[100];

void inputProcess(int n);
int findMax(int a, int b);
int findMin(int a, int b);
void priorityScheduling(int n);
void calculateMetrics(int n);
void printProcesses(int n);

int main()
{
    int n;
    printf("Enter the total Processes: ");
    scanf("%d", &n);
    inputProcess(n);
    priorityScheduling(n);
    calculateMetrics(n);
    printProcesses(n);
    return 0;
}

void inputProcess(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter the AT of process[%d]: ", i + 1);
        scanf("%d", &ps[i].at);
        printf("Enter the BT of process[%d]: ", i + 1);
        scanf("%d", &ps[i].bt);
        printf("Enter the priority of process[%d]: ", i + 1);
        scanf("%d", &ps[i].priority);
        ps[i].id = i + 1;
    }
}

int findMax(int a, int b)
{
    return a > b ? a : b;
}

int findMin(int a, int b)
{
    return a < b ? a : b;
}

float cpuUtilization(int lengthCycle, int totalIdleTime)
{
    return (float)(lengthCycle - totalIdleTime) / lengthCycle;
}

void priorityScheduling(int n)
{
    bool isCompleted[100] = {false};
    int currentTime = 0, completed = 0, totalIdleTime = 0, prev = 0;

    while (completed != n)
    {
        int maxIndex = -1;
        int maximum = -1;

        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= currentTime && !isCompleted[i])
            {
                if (ps[i].priority > maximum)
                {
                    maximum = ps[i].priority;
                    maxIndex = i;
                }
                else if (ps[i].priority == maximum)
                {
                    if (ps[i].at < ps[maxIndex].at)
                    {
                        maxIndex = i;
                    }
                }
            }
        }

        if (maxIndex == -1)
        {
            currentTime++;
        }
        else
        {
            ps[maxIndex].startTime = currentTime;
            ps[maxIndex].ct = ps[maxIndex].startTime + ps[maxIndex].bt;
            ps[maxIndex].tat = ps[maxIndex].ct - ps[maxIndex].at;
            ps[maxIndex].wt = ps[maxIndex].tat - ps[maxIndex].bt;
            ps[maxIndex].rt = ps[maxIndex].startTime - ps[maxIndex].at;

            totalIdleTime += (completed == 0) ? 0 : (ps[maxIndex].startTime - prev);
            currentTime = ps[maxIndex].ct;
            prev = currentTime;
            isCompleted[maxIndex] = true;
            completed++;
        }
    }
}

void calculateMetrics(int n)
{
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    for (int i = 0; i < n; i++)
    {
        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;
    }

    printf("\nAverage TAT : %.2f", sum_tat / n);
    printf("\nAverage WT  : %.2f", sum_wt / n);
    printf("\nAverage RT  : %.2f\n", sum_rt / n);
}

void printProcesses(int n)
{
    printf("\nProcess Details:\n");
    printf("ID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\tStartTime\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].id, ps[i].at, ps[i].bt, ps[i].priority,
               ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt,
               ps[i].startTime);
    }
}
