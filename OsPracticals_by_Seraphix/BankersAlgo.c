#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int max[10];
    int allocated[10];
    int need[10];
} processInfo;

int noOfProcess, noOfResource;

void inputProcesses(processInfo process[], int available[]);
void displayProcessInfo(processInfo process[]);
bool applySafetyAlgorithm(processInfo process[], int available[], int safeSequence[]);
bool isSafeState(processInfo process[], int available[], int safeSequence[]);

int main()
{
    printf("Enter No of Processes: ");
    scanf("%d", &noOfProcess);
    printf("\nEnter the No of Resource Instance in Systems: ");
    scanf("%d", &noOfResource);

    int available[noOfResource];
    int safeSequence[noOfProcess];

    processInfo process[noOfProcess];

    inputProcesses(process, available);

    displayProcessInfo(process);

    if (isSafeState(process, available, safeSequence))
    {
        printf("\nSystem is in safe state.\nSafe Sequence is: ");
        for (int i = 0; i < noOfProcess; i++)
        {
            printf("P[%d] ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("\nDeadlock detected\n");
    }

    return 0;
}

void inputProcesses(processInfo process[], int available[])
{
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("\nEnter process[%d] info\n", i);
        printf("Enter the max Need: ");
        for (int j = 0; j < noOfResource; j++)
        {
            scanf("%d", &process[i].max[j]);
        }
        printf("Enter the allocated resource of the process: ");
        for (int j = 0; j < noOfResource; j++)
        {
            scanf("%d", &process[i].allocated[j]);
            process[i].need[j] = process[i].max[j] - process[i].allocated[j];
        }
    }

    printf("Enter the available Resources: ");
    for (int i = 0; i < noOfResource; i++)
    {
        scanf("%d", &available[i]);
    }
}

void displayProcessInfo(processInfo process[])
{
    printf("\nPid\tMaximum\t\tAllocated\tNeed\n");
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("P[%d]\t", i);
        for (int j = 0; j < noOfResource; j++)
        {
            printf("%d ", process[i].max[j]);
        }
        printf("\t\t");
        for (int j = 0; j < noOfResource; j++)
        {
            printf("%d ", process[i].allocated[j]);
        }
        printf("\t\t");
        for (int j = 0; j < noOfResource; j++)
        {
            printf("%d ", process[i].need[j]);
        }
        printf("\n");
    }
}

bool isSafeState(processInfo process[], int available[], int safeSequence[])
{
    return applySafetyAlgorithm(process, available, safeSequence);
}

bool applySafetyAlgorithm(processInfo process[], int available[], int safeSequence[])
{
    bool finish[noOfProcess];
    int work[noOfResource];

    for (int i = 0; i < noOfResource; i++)
    {
        work[i] = available[i];
    }
    for (int i = 0; i < noOfProcess; i++)
    {
        finish[i] = false;
    }

    int countSafeSequence = 0;
    bool proceed = true;

    while (proceed)
    {
        proceed = false;
        int selectedProcess = -1;

        for (int i = 0; i < noOfProcess; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < noOfResource; j++)
                {
                    if (process[i].need[j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate && (selectedProcess == -1 || process[i].need[0] < process[selectedProcess].need[0]))
                {
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess != -1)
        {
            for (int j = 0; j < noOfResource; j++)
            {
                work[j] += process[selectedProcess].allocated[j];
            }
            finish[selectedProcess] = true;
            safeSequence[countSafeSequence++] = selectedProcess;
            proceed = true;
        }
    }

    for (int i = 0; i < noOfProcess; i++)
    {
        if (!finish[i])
        {
            return false;
        }
    }
    return true;
}
