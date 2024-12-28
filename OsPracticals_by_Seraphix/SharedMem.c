#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    int shm_id = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
    char *sharedMem = (char *)shmat(shm_id, null, 0);

    int pid = fork();
    if (pid == 0)
    {
        strcpy(sharedMem, "this is the msg");
    }
    else
    {
        sleep(1);
        printf("Parent recieved: %s\n", sharedMem);
    }
    return 0;
}