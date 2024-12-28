#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct processStruct
{
    int wt;
    int rt;
    int bt;
    int at;
    int ct;
    int tat;
    int pId;
    int remainingBt;
    int startTime;
} ps[100];

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

int findMin(int a, int b)
{
    return (a < b) ? a : b;
}

void inputProcesses(int n)
{
    for (int i = 0; i < n; i++)
    {
        ps[i].pId = i + 1;
        printf("Enter the arrival time of process[%d] : ", i + 1);
        scanf("%d", &ps[i].at);
        printf("Enter the burst time of process[%d]: ", i + 1);
        scanf("%d", &ps[i].bt);
        ps[i].remainingBt = ps[i].bt;
    }
}

void calculateTimes(int n)
{
    int currentTime = 0, completed = 0, prevTime = 0;
    int totalIdleTime = 0, isFirstProcess = true;
    int minimumRemainingTime = INT_MAX, minimumRemainingTimeIndex = -1;
    bool isStarted[100] = {false};

    while (completed != n)
    {
        minimumRemainingTimeIndex = -1;
        minimumRemainingTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= currentTime && ps[i].remainingBt > 0)
            {
                if (ps[i].remainingBt < minimumRemainingTime)
                {
                    minimumRemainingTime = ps[i].remainingBt;
                    minimumRemainingTimeIndex = i;
                }
                if (ps[i].remainingBt == minimumRemainingTime && ps[i].at < ps[minimumRemainingTimeIndex].at)
                {
                    minimumRemainingTimeIndex = i;
                }
            }
        }

        if (minimumRemainingTimeIndex == -1)
        {
            totalIdleTime++;
            currentTime++;
        }
        else
        {
            if (!isStarted[minimumRemainingTimeIndex])
            {
                ps[minimumRemainingTimeIndex].startTime = currentTime;
                ps[minimumRemainingTimeIndex].rt = ps[minimumRemainingTimeIndex].startTime - ps[minimumRemainingTimeIndex].at;
                isStarted[minimumRemainingTimeIndex] = true;
            }
            ps[minimumRemainingTimeIndex].remainingBt--;
            currentTime++;

            if (ps[minimumRemainingTimeIndex].remainingBt == 0)
            {
                ps[minimumRemainingTimeIndex].ct = currentTime;
                ps[minimumRemainingTimeIndex].tat = ps[minimumRemainingTimeIndex].ct - ps[minimumRemainingTimeIndex].at;
                ps[minimumRemainingTimeIndex].wt = ps[minimumRemainingTimeIndex].tat - ps[minimumRemainingTimeIndex].bt;
                completed++;
            }
        }
    }
}

void printResults(int n)
{
    printf("\nProcess No.\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pId, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
}

void calculateMetrics(int n)
{
    int sumTat = 0, sumWt = 0, sumRt = 0;
    for (int i = 0; i < n; i++)
    {
        sumTat += ps[i].tat;
        sumWt += ps[i].wt;
        sumRt += ps[i].rt;
    }

    printf("\nAverage Turnaround Time = %.2f", (float)sumTat / n);
    printf("\nAverage Waiting Time = %.2f", (float)sumWt / n);
    printf("\nAverage Response Time = %.2f", (float)sumRt / n);
}