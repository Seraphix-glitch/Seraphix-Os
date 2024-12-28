#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("Executing the ls command using execlp():\n");
    execlp("ls", "ls", "-l", NULL);
    perror("execlp failed");
    return 1;
}
