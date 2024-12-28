#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int child1, child2;
    child1 = fork();

    if (child1 == 0)
    {
        printf("First child process (PID: %d): Listing files.\n", getpid());
        execl("/bin/ls", "ls", "-la", NULL);
        exit(1);
    }
    else if (child1 > 0)
    {
        printf("Parent process (PID: %d): Waiting for the first child to complete...\n", getpid());
        wait(NULL);
        printf("First child completed, now creating the second child...\n");

        child2 = fork();

        if (child2 == 0)
        {
            printf("Second child process (PID: %d): Running...\n", getpid());
            sleep(5);
            printf("Second child process (PID: %d): Completed work.\n", getpid());
        }
        else if (child2 > 0)
        {
            printf("Parent process (PID: %d): Exiting before second child finishes...\n", getpid());
            exit(0);
        }
        else
        {
            perror("fork failed");
            exit(1);
        }
    }
    else
    {
        perror("fork failed");
        exit(1);
    }

    return 0;
}