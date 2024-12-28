#include <stdio.h>
#include <stdlib.h>

void bestfit(int blockSize[], int blocks, int processSize[], int process)
{
    int allocated[process];
    for (int i = 0; i < process; i++)
    {
        allocated[i] = -1;
    }
    for (int i = 0; i < process; i++)
    {
        int bestIndex = -1;
        for (int j = 0; j < blocks; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex])
                {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1)
        {
            allocated[i] = bestIndex;
            blockSize[i] -= processSize[i];
        }
    }
    printf("Best Allocation\n");
    for (int i = 0; i < process; i++)
    {
        if (allocated[i] != -1)
        {
            printf("The block allocated to process %d is %d\n", i + 1, allocated[i] + 1);
        }
        else
        {
            printf("Process don't get allocated\n");
        }
    }
}

int main()
{
    int b, p;
    printf("Enter the number of blocks\n");
    scanf("%d", &b);
    int arr[b];
    int blocksize[b];
    printf("Enter the sizeof blocks\n");
    for (int i = 0; i < b; i++)
    {
        scanf("%d", &blocksize[i]);
    }
    printf("Enter the no of processes\n");
    scanf("%d", &p);
    int processSize[p];
    printf("Enter the total process\n");
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &processSize[i]);
    }
    bestfit(blocksize, b, processSize, p);
    return 0;
}