#include <stdio.h>
#include <stdlib.h>

struct processStructure
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
} ps[100];

void inputProcesses(int n);
void calculateTimes(int n);
void printDetails(int n);
void calculateMetrics(int n);
int compare(const void *p1, const void *p2);

int main()
{
    printf("Name- Aditya Pandey , Section-A2 , Roll No - 08");
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);

    inputProcesses(n);
    qsort((void *)ps, n, sizeof(struct processStructure), compare);
    calculateTimes(n);
    printDetails(n);
    calculateMetrics(n);
    return 0;
}

void inputProcesses(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time of the process[%d] : ", i + 1);
        scanf("%d", &ps[i].at);
        printf("Enter the burst time of the process[%d] : ", i + 1);
        scanf("%d", &ps[i].bt);
    }
}

int compare(const void *p1, const void *p2)
{
    int a = ((struct processStructure *)p1)->at;
    int b = ((struct processStructure *)p2)->at;

    if (a < b)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void calculateTimes(int n)
{
    int totalBurstTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            ps[i].ct = ps[i].at + ps[i].bt; 
        }
        else if (ps[i - 1].ct <= ps[i].at)
        {
            ps[i].ct = ps[i].at + ps[i].bt;
        }
        else
        {
            ps[i].ct = ps[i - 1].ct + ps[i].bt;
        }

        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].wt;
        totalBurstTime += ps[i].bt;
    }
}

void printDetails(int n)
{
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].st, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
}
float findMaxCompletionTime(int n)
{
    float max = 0;
    for (int i = 0; i < n; i++)
    {
        if (ps[i].ct > max)
        {
            max = ps[i].ct;
        }
    }
    return max;
}
float calculateThroughput(int n, float maxCompletionTime)
{
    return n / maxCompletionTime;
}
float calculateCPUUtilization(int totalBurstTime, float maxCompletionTime)
{
    return (totalBurstTime / maxCompletionTime) * 100;
}
void calculateMetrics(int n)
{
    float swt = 0, stat = 0, awt = 0, atat = 0;
    int sbt = 0;
    float maxCompletionTime = findMaxCompletionTime(n);

    for (int i = 0; i < n; i++)
    {
        swt += ps[i].wt;
        stat += ps[i].tat;
        sbt += ps[i].bt;
        ps[i].st = ps[i].rt + ps[i].at;
    }

    awt = swt / n;
    atat = stat / n;

    float cpu_utilization = calculateCPUUtilization(sbt, maxCompletionTime);
    float throughput = calculateThroughput(n, maxCompletionTime);

    printf("\nSum of Turnaround Time: %.2f\nAverage Turnaround Time: %.2f", stat, atat);
    printf("\nSum of Waiting Time: %.2f\nAverage Waiting Time: %.2f", swt, awt);
    printf("\nCPU Utilization: %.2f%%", cpu_utilization);
    printf("\nThroughput: %.2f\n", throughput);
}
