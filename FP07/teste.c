#include <stdio.h>
#include <pthread.h>

void *ola(void *args)
{
  int id = *(int *)args;
  printf(" Olá da Thread Numero %d\n", id);
  return NULL;
}

int main()
{
  pthread_t ts[5];
  int ids[5] = {0, 1, 2, 3, 4};
  for (int i = 0; i < 5; i++)
    pthread_create(&ts[i], NULL, ola, (int *)&ids[i]);

  for (int i = 0; i < 5; i++)
    pthread_join(ts[i], NULL);
}