#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

sem_t choptstick[5];

void *philos(void *n);
void eat(int ph);

int main()
{
    int i, n[5];
    pthread_t T[5];
    for (int i = 0; i < 5; i++)
    {
        sem_init(&choptstick[i], 0, 1);
    }
    for (int i = 0; i < 5; i++)
    {
        n[i] = i;
        pthread_create(&T[i], null, philos, (void *)&n[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(T[i], NULL);
    }
    return 0;
}

void philos(void *n)
{
    int ph = *(int *)n;
    printf("Philospher want  to eat %d \n", ph);
    sem_wait(&choptstick[ph]);
    printf("Left chopstick picked up by %d\n", ph);
    sem_wait(&choptstick[(ph + i) % 5]);
    printf("right chopstick picked up by %d\n", ph);
    eat(ph);
    sleep(2);
    printf("Philosopher %d has finished eating\n", ph);
    sem_post(&choptstick[(ph + 1) % 5]);
    sem_post(&choptstick[ph]);
}
void eat(int ph)
{
    printf("Philosopher %d is eating\n", ph);
}