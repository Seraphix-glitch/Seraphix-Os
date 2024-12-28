#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mutex, full, empty;
int buffersize = 5;
int x = 0;

void producer()
{
    sem_wait(&empty);
    sem_wait(&mutex);
    x++;
    printf("Producer produced x : %d\n", x);
    sem_post(&mutex);
    sem_post(&full);
}

void consumer()
{
    sem_wait(&full);
    sem_wait(&mutex);
    printf("Producer consumed x : %d\n",x);
    x--;
    sem_post(&mutex);
    sem_post(&empty);
}

int main()
{
    int n;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, buffersize);
    sem_init(&full, 0, 0);
    while (1)
    {
        printf("\n1 for producer , 2 for consumer , 3 for exit\n");
        printf("Enter you choice\n");
        scanf("%d", &n);
        switch (n)  
        {
        case 1:
            if (sem_trywait(&empty) == 0)
            {
                sem_post(&empty);
                producer();
            }
            else
            {
                printf("Buffer is full\n");
            }
            break;
        case 2:
            if (sem_trywait(&full) == 0)
            {
                sem_post(&full);
                consumer();
            }
            else
            {
                printf("buffer is empty\n");
            }
            break;
        case 3:
            printf("Exiting\n");
            exit(0);
        default:
            printf("invalid choice \n");
            break;
        }
    }
    return 0;
}