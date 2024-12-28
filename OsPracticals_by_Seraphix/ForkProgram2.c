#include <stdio.h>
#include <unistd.h>

int main()
{
    int id = fork();
    printf("%d \n", id);
    if (id == 0)
    {
        printf("Child Process: \n");
        fflush(stdout);
        printf("PId : %d \n", getpid());
        fflush(stdout);
        printf("Parent PId: %d \n", getppid());
        fflush(stdout);
    }
    else
    {
        wait();
        printf("Parent Process : \n");
        fflush(stdout);
        printf("PId :  %d \n", getpid());
        fflush(stdout);
        printf("child Pid : %d \n", id);
        fflush(stdout);
    }
    return 0;
}