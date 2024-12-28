#include <stdio.h>

int main()
{
    int n, frames, pagefault = 0;
    printf("Enter the number of frames available: ");
    scanf("%d", &frames);
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int seq[n];
    printf("Enter the sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &seq[i]);
    }

    int temp[frames];
    for (int i = 0; i < frames; i++)
    {
        temp[i] = -1;
    }

    int currentIndex = 0;

    for (int i = 0; i < n; i++)
    {
        int flag = 0;

        for (int j = 0; j < frames; j++)
        {
            if (seq[i] == temp[j])
            {
                flag = 1;
                break;
            }
        }

        if (!flag)
        {
            temp[currentIndex] = seq[i];
            currentIndex = (currentIndex + 1) % frames;
            pagefault++;
        }

        printf("Frame content after request %d: ", seq[i]);
        for (int j = 0; j < frames; j++)
        {
            if (temp[j] != -1)
                printf("%d ", temp[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pagefault);
    return 0;
}
