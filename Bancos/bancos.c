#include "bancos.h"

// escolhe um nome para o tipo de dados

typedef struct
{
    int idAtm;
    int idCliente;
    float valor;
} movimento;

// Max numero de clientes e threads
#define MAXCLI 20
#define MAXT 10

/* variaveis partilhadas pelos threads */
int NT;
int NC;
float saldos[MAXCLI];
int cnt;
pthread_mutex_t lock1;
pthread_mutex_t lock2;
int *id;

void *relatorio(void *args);
void *multibanco(void *args);

int main(int argc, char *argv[])
{
    int i;
    pthread_t rel, atm[MAXT];

    printf("\n\nIntroduza o numero de ATM's (ate 10) e numero de clientes (ate 20):  ");
    scanf("%d%d", &NT, &NC);

    printf("Data in.bin. Voce Escolheu:  Threads= %d Clientes=%d\n\n", NT, NC);
    getchar(); // engolir /n

    // Initializar os saldos dos clientes
    for (i = 0; i < NC; i++)
        saldos[i] = 0.0;

    // Initializar um contador para travar thread do relatorio
    cnt = -NT;

    pthread_create(&rel, NULL, relatorio, NULL);

    // criar threads multibanco .. passar argumento

    for (i = 0; i < NT; i++)
    {
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&atm[i], NULL, multibanco, id);
    }

    pthread_exit(NULL);

    return 0;
}

void *multibanco(void *args)
{
    int *id = (int *)args;
    movimento mult;
    int fd;
    fd = open("in.bin", O_RDONLY);
    while (read(fd, &mult, sizeof mult) > 0)
    {
        if (mult.idAtm == *id && mult.idCliente < NC)
        {
            float velhoSaldo;
            pthread_mutex_lock(&lock1);
            velhoSaldo = saldos[mult.idCliente];
            pause;
            saldos[mult.idCliente] = velhoSaldo + mult.valor;
            pthread_mutex_unlock(&lock1);
        }
    }
    pthread_mutex_lock(&lock2);
    cnt++;
    pthread_mutex_unlock(&lock2);
    return NULL;
}

void *relatorio(void *args)
{
    printf("relatorio do dia:\n");
    printf("cliente Numero   Saldo:\n");
    while (cnt != 0)
        ;
    for (int i = 0; i < NC; i++)
    {
        printf("%d\t%f\n", i, saldos[i]);
    }

    return NULL;
}
