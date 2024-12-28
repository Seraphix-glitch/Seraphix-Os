#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
int tq = 2;
struct process
{
    int id;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int rt;
    int priority;
    int st;
    int btRem;
} ps[100];

void inputProcess(int n);
void calculateMetrics(int n);
void PremPriority(int n);
int findMax(int a, int b);
int findMin(int a, int b);

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    inputProcess(n);
    PremPriority(n);
    calculateMetrics(n);
    return 0;
}

void inputProcess(int n)
{
    for (int i = 0; i < n; i++)
    {
        ps[i].id = i;
        printf("Enter the burst time of process[%d]: ", i + 1);
        scanf("%d", &ps[i].bt);
        printf("Enter the arrival time of process[%d]: ", i + 1);
        scanf("%d", &ps[i].at);
        printf("Enter priority for process[%d]: ", i + 1);
        scanf("%d", &ps[i].priority);
        ps[i].btRem = ps[i].bt;
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

void PremPriority(int n)
{
    bool isCompleted[100] = {false}, isFirstProcess = true;
    int currentTime = 0, completed = 0, prev = 0;
    while (completed != n)
    {
        int minIndex = -1;
        int minPriority = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= currentTime && !isCompleted[i])
            {
                if (ps[i].priority < minPriority)
                {
                    minPriority = ps[i].priority;
                    minIndex = i;
                }
                else if (ps[i].priority == minPriority)
                {
                    if (ps[i].at < ps[minIndex].at)
                    {
                        minIndex = i;
                    }
                }
            }
        }

        if (minIndex == -1)
        {
            currentTime++;
        }
        else
        {
            if (ps[minIndex].btRem == ps[minIndex].bt)
            {
                ps[minIndex].st = currentTime;
            }

            if (ps[minIndex].btRem <= tq)
            {
                currentTime += ps[minIndex].btRem;
                ps[minIndex].btRem = 0;
                ps[minIndex].ct = currentTime;
                ps[minIndex].wt = ps[minIndex].tat - ps[minIndex].bt;
                ps[minIndex].rt = ps[minIndex].st - ps[minIndex].at;
                ps[minIndex].tat = ps[minIndex].ct - ps[minIndex].at;
                prev = currentTime;
                isCompleted[minIndex] = true;
                completed++;
            }
            else
            {
                currentTime = currentTime + tq;
                isFirstProcess = false;
                ps[minIndex].btRem -= tq;
            }
        }
    }
}

void calculateMetrics(int n)
{
    float sumTat = 0, sumWt = 0, sumRt = 0;

    printf("\nProcess No.\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        sumTat += ps[i].tat;
        sumWt += ps[i].wt;
        sumRt += ps[i].rt;

        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               ps[i].id + 1, ps[i].at, ps[i].bt, ps[i].priority, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }

    printf("\nAverage TAT : %.2f", sumTat / n);
    printf("\nAverage WT  : %.2f", sumWt / n);
    printf("\nAverage RT  : %.2f\n", sumRt / n);
}
