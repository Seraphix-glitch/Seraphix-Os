#include <stdio.h>
#include <stdlib.h>

void worstfit(int blockSize[], int blocks, int processSize[], int process)
{
    int allocated[process];
    for (int i = 0; i < process; i++)
    {
        allocated[i] = -1;
    }
    for (int i = 0; i < process; i++)
    {
        int worstIndex = -1;
        for (int j = 0; j < blocks; j++)
        {
            if (blockSize[j] > processSize[i])
            {
                if (worstIndex == -1 || blockSize[j] >= blockSize[worstIndex])
                {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1)
        {
            allocated[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }
    printf("the worst fit allocation is \n");
    for (int i = 0; i < process; i++)
    {
        if (allocated[i] != -1)
        {
            printf("the block allocated to process %d is %d \n", i + 1, allocated[i] + 1);
        }
        else
        {
            printf("The process %d is not get allocated\n", i + 1);
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
    worstfit(blocksize, b, processSize, p);
    return 0;
}