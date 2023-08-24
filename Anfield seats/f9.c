    #include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <semaphore.h>

volatile int bilDisp = 45522;
volatile int Vendas[10] = {0};
volatile atomic_flag lock;
int semente;
int metodo;
pthread_mutex_t mutex;
sem_t s;

void trancarTS(int id)
{
    while (atomic_flag_test_and_set(&lock))
        ;
}
void libertarTS(int id)
{
    atomic_flag_clear(&lock);
}

void *funcao(void *args)
{
    int id = *(int *)args;
    srand(semente + id);

    if (1 == metodo)
    {
        pthread_mutex_lock(&mutex);
    }
    if (2 == metodo)
    {
        sem_wait(&s);
    }
    if (3 == metodo)
    {
        trancarTS(id);
    }

    int j = 0;
    for (j; j <= 1500; j++)
    {
        int b = 1 + rand() % 4;

        if (bilDisp >= b)
        {
            bilDisp = bilDisp - b;
            Vendas[id] += b;
        }
    }
    if (1 == metodo)
    {
        pthread_mutex_unlock(&mutex);
    }
    if (2 == metodo)
    {
        sem_post(&s);
    }
    if (3 == metodo)
    {
        libertarTS(id);
    }
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Erro\n");
    }
    sem_init(&s, 0, 1);
    int TotalVendas = 0;
    int capacity = 0;
    semente = atoi(argv[1]);
    metodo = atoi(argv[2]);

    pthread_t threads[10];
    int i, id[10];

    for (i = 0; i < 10; i++)
    {
        id[i] = i;
    }

    for (i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, funcao, &id[i]);
    }

    for (i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
        TotalVendas += Vendas[i];
    }
    capacity = bilDisp + TotalVendas;
    // printf("Capacidade Calculada %d (45522?)\n", capacity);

    return 0;
}
