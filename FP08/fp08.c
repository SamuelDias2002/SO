#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define wait1                                   \
  {                                             \
    double z1;                                  \
    for (z1 = 0; z1 < 10000; z1 = z1 + 0.00003) \
      ;                                         \
  } // ajustar conforme o seu PC
#define BUFFER_SIZE 10
typedef struct
{
  int valor;
} item;
item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int counter = 0;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void *Producer(void *arg)
{
  int val = 1, k = 0;
  item nextProduced;
  while (k++ < 50)
  {
    while (counter == BUFFER_SIZE)
      wait1; /* do nothing */
    nextProduced.valor = val++;
    buffer[in] = nextProduced;
    in = (in + 1) % BUFFER_SIZE;
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
  }
  return (NULL);
}

void *Consumer(void *arg)
{
  item nextConsumed;
  int k = 0;
  while (k++ < 50)
  {
    while (counter == 0)
      wait1; /* do nothing */
    nextConsumed = buffer[out];
    pthread_mutex_lock(&mutex2);
    out = (out + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex2);
    printf("Valor=%d : %d\n", nextConsumed.valor, counter);
    pthread_mutex_lock(&mutex1);
    counter--;
    pthread_mutex_unlock(&mutex1);
  }
  return (NULL);
}

int main()
{
  pthread_t pid, cid, cid2;
  pthread_create(&pid, NULL, Producer, NULL);
  pthread_create(&cid, NULL, Consumer, NULL);
  pthread_create(&cid2, NULL, Consumer, NULL);
  pthread_join(pid, NULL);
  pthread_join(cid, NULL);
}