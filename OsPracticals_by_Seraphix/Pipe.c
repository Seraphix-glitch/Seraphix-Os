#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    char write_msg[] = "message from child to parent";
    char read_msg[100];
    pipe(pipefd);
    int pid = fork();
    if (pid == 0)
    {
        write(pipefd[1], write_msg, strlen(write_msg) + 1);
    }
    else
    {
        read(pipefd[0], read_msg, sizeof(read_msg));
        printf("Parent recieved : %s \n", read_msg);
    }
    return 0;
}