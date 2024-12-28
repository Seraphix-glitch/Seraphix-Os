#include <stdio.h>
#include <stdlib.h>
#define high 199
#define low 0

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, seektime = 0, head, i, j, diff, temp1 = 0, temp2 = 0;
    printf("Enter the number of sequence\n");
    scanf("%d", &n);
    int seq[n + 3], queue1[n], queue2[n];
    printf("Enter the position of head\n");
    scanf("%d", &head);
    printf("Enter the sequence\n");
    for (int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        if (temp >= head)
        {
            queue1[temp1++] = temp;
        }
        else
        {
            queue2[temp2++] = temp;
        }
    }
    qsort(queue1, temp1, sizeof(int), compare);
    qsort(queue2, temp2, sizeof(int), compare);
    seq[0] = head;
    int index = 1;
    for (int i = 0; i < temp1; i++)
    {
        seq[index++] = queue1[i];
    }
    seq[index++] = high;
    seq[index++] = low;
    for (int i = 0; i < temp2; i++)
    {
        seq[index++] = queue2[i];
    }
    for (int i = 0; i < index - 1; i++)
    {
        diff = abs(seq[i + 1] - seq[i]);
        seektime += diff;
        printf("%d ", seq[i]);
    }
    printf("%d \n", seq[index - 1]);
    printf("Total seek time is : %d\n", seektime);
    return 0;
}