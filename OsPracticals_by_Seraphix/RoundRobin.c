#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

struct process
{
    int id;
    int bt;
    int at;
    int ct;
    int tat;
    int rt;
    int wt;
    int startTime;
    int btRemaining;
} ps[100];

struct ganttChartEntry
{
    int pid;

} gant[100];

int gantCount = 0;

int findMax(int a, int b);
void inputProcess(int n);
void roundRobinScheduling(int n, int tq);
void calculateMetrics(int n);
void printResults(int n);
int comparatorAt(const void *a, const void *b);
int comparatorPid(const void *a, const void *b);
void addGanttChartEntry(int pid);
void printGanttChart(int ganttCount);

int main()
{
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("\nEnter the time quanta: ");
    scanf("%d", &tq);

    inputProcess(n);
    roundRobinScheduling(n, tq);
    calculateMetrics(n);
    printResults(n);
    printGanttChart(gantCount);
    return 0;
}

int findMax(int a, int b)
{
    return a > b ? a : b;
}

void inputProcess(int n)
{
    for (int i = 0; i < n; i++)
    {
        ps[i].id = i;
        printf("Enter the at for process[%d]: ", i + 1);
        scanf("%d", &ps[i].at);
        printf("Enter the bt for process[%d]: ", i + 1);
        scanf("%d", &ps[i].bt);
        ps[i].btRemaining = ps[i].bt;
    }
}

int comparatorAt(const void *a, const void *b)
{
    int x = ((struct process *)a)->at;
    int y = ((struct process *)b)->at;
    return (x < y) ? -1 : 1;
}

int comparatorPid(const void *a, const void *b)
{
    int x = ((struct process *)a)->id;
    int y = ((struct process *)b)->id;
    return (x < y) ? -1 : 1;
}

void roundRobinScheduling(int n, int tq)
{
    int front = -1, rear = -1;
    int queue[100], totalIdleTime = 0, completed = 0;
    int currentTime = 0, index, maxCompletionTime, lengthCycle;
    bool visisted[100] = {false}, isFirstProcess = true;

    qsort((void *)ps, n, sizeof(struct process), comparatorAt);

    front = rear = 0;
    queue[rear] = 0;
    visisted[0] = true;

    while (completed != n)
    {
        index = queue[front++];
        int startTime = currentTime;
        if (ps[index].btRemaining == ps[index].bt)
        {
            ps[index].startTime = findMax(currentTime, ps[index].at);
            totalIdleTime += (isFirstProcess) ? 0 : ps[index].startTime - currentTime;
            currentTime = ps[index].startTime;
            isFirstProcess = false;
        }
        if (ps[index].btRemaining - tq > 0)
        {
            ps[index].btRemaining -= tq;
            currentTime += tq;
        }
        else
        {
            currentTime += ps[index].btRemaining;
            ps[index].btRemaining = 0;
            completed++;
            ps[index].ct = currentTime;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].startTime - ps[index].at;
        }

        addGanttChartEntry(ps[index].id);

        for (int i = 1; i < n; i++)
        {
            if (ps[i].btRemaining > 0 && ps[i].at <= currentTime && !visisted[i])
            {
                queue[++rear] = i;
                visisted[i] = true;
            }
        }
        if (ps[index].btRemaining > 0)
        {
            queue[++rear] = index;
        }
        if (front > rear)
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].btRemaining > 0 && ps[i].at <= currentTime)
                {
                    queue[++rear] = i;
                    visisted[i] = true;
                    break;
                }
            }
        }
    }
    maxCompletionTime = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        maxCompletionTime = findMax(maxCompletionTime, ps[i].ct);
    }
    lengthCycle = maxCompletionTime - ps[0].at;
    float cpuUtilization = (float)(lengthCycle - totalIdleTime) / lengthCycle;
    printf("\n CPU UTILIZATION (PERCENTAGE) = %.2f%% \n", cpuUtilization * 100);
}

void calculateMetrics(int n)
{
    float sumTat = 0, sumWt = 0, sumRt = 0;

    for (int i = 0; i < n; i++)
    {
        sumTat += ps[i].tat;
        sumWt += ps[i].wt;
        sumRt += ps[i].rt;
    }

    printf("Average TAT : %.2f \n", sumTat / n);
    printf("Average wt : %.2f \n", sumWt / n);
    printf("Average rt : %.2f \n", sumRt / n);
}

void printResults(int n)
{
    qsort((void *)ps, n, sizeof(struct process), comparatorPid);

    printf("\nProcess No.\tAT\tBT\tStart Time\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               ps[i].id, ps[i].at, ps[i].bt, ps[i].startTime, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
}

void addGanttChartEntry(int pid)
{
    gant[gantCount].pid = pid;
    gantCount++;
}

void printGanttChart(int ganttCount)
{
    printf("\nGantt Chart: \n");
    for (int i = 0; i < ganttCount; i++)
    {
        printf("|  P%d  ", gant[i].pid);
    }
    printf("|\n");
}
