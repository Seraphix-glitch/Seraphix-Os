#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define low 0
#define high 199

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, seektime = 0, temp1 = 0, temp2 = 0, head;
    printf("Enter the total request\n");
    scanf("%d", &n);

    int arr1[n], arr2[n];
    int seq[n + 3]; 

    printf("Enter the head\n");
    scanf("%d", &head);

    printf("Enter the requests\n");
    for (int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        if (temp >= head)
        {
            arr1[temp1++] = temp;
        }
        else
        {
            arr2[temp2++] = temp;
        }
    }

    qsort(arr1, temp1, sizeof(int), compare);
    qsort(arr2, temp2, sizeof(int), compare);

    seq[0] = head;
    int index = 1;
\
    for (int i = 0; i < temp1; i++)
    {
        seq[index++] = arr1[i];
    }

    seq[index++] = high;

    for (int i = temp2 - 1; i >= 0; i--)
    {
        seq[index++] = arr2[i];
    }

    for (int i = 0; i < index - 1; i++)
    {
        int diff = abs(seq[i + 1] - seq[i]);
        seektime += diff;
    }

    printf("Total seek time: %d\n", seektime);

    return 0;
}
