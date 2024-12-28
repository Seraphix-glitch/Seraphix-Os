#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct msg
{
    long msg_type;
    char msg[100];
};

int main()
{
    struct msg message;
    int msgId = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    int t_pid = fork();
    if (pid == 0)
    {
        message.msg_type = 1;
        strcpy(message.msg, "Message from child");
        msgsnd(msgId, &message, sizeof(message), 0);
    }
    else
    {
        msgrcv(msgId, &message, sizeof(message), 1, 0);
        printf("Parent recieved: %s\n", message.msg);
    }

    return 0;
}