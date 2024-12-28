#include <stdio.h>

int main()
{
    int n = 12, framecount = 3, pagefault = 0, currentTime = 0;
    int seq[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};

    int temp[framecount];
    int timeStamp[framecount];

    for (int i = 0; i < framecount; i++)
    {
        temp[i] = -1;
        timeStamp[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int flag = 0;

        for (int j = 0; j < framecount; j++)
        {
            if (seq[i] == temp[j])
            {
                flag = 1;
                timeStamp[j] = currentTime;
                break;
            }
        }

        if (!flag)
        {
            int lruIndex = 0;
            for (int j = 0; j < framecount; j++)
            {
                if (timeStamp[j] < timeStamp[lruIndex])
                {
                    lruIndex = j;
                }
            }

            temp[lruIndex] = seq[i];
            timeStamp[lruIndex] = currentTime;
            pagefault++;
        }
        printf("Frames after request %d: ", seq[i]);
        for (int j = 0; j < framecount; j++)
        {
            if (temp[j] != -1)
            {
                printf("%d ", temp[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");

        currentTime++;
    }

    printf("\nTotal number of page faults: %d\n", pagefault);

    return 0;
}
