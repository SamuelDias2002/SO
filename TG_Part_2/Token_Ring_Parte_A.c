/*
 Realizado por:
    Mateus Aleixo, nº47700
	Pedro Lourenço, nº48213
	Samuel Dias, nº48184

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Uso: tokenring <n> <p> <t> <max>\n");
        return 1;
    }

    // Número de processos
    int n = atoi(argv[1]);

    // Probabilidade de bloqueio
    float p = atof(argv[2]);

    // Tempo de bloqueio em segundos
    int t = atoi(argv[3]);

    // Valor máximo da token
    int max = atoi(argv[4]);

    int i;
    int pipes[n][2];
    char pipe_name[10];

    // Criação dos pipes nomeados
    for (i = 0; i < n; i++)
    {
        sprintf(pipe_name, "pipe%dto%d", i + 1, (i + 2) > n ? 1 : i + 2);
        mkfifo(pipe_name, 0666);
        pipes[i][0] = open(pipe_name, O_RDONLY | O_NONBLOCK);
        pipes[i][1] = open(pipe_name, O_WRONLY);
    }

    // Criação dos processos
    for (i = 0; i < n; i++)
    {
        if (fork() == 0)
        {
            srand(getpid());

            int value = 0;
            int token_received = 0;

            while (1)
            {
                // Leitura do token
                if (token_received)
                {
                    read(pipes[i][0], &value, sizeof(int));
                    printf ("teste\n");
                    token_received = 0;
                }

                if (value > max)
                {
                    break;
                }

                // Incremento do valor do token
                value++;

                // Verificação do valor máximo do token
                if (value >= max)
                {
                    break;
                }

                // Envio do token para o próximo processo
                write(pipes[(i + 1) % n][1], &value, sizeof(int));
                token_received++;

                // Verificação da probabilidade de bloqueio
                float rand_value = (float)rand() / RAND_MAX;
                if (rand_value < p)
                {
                    printf("[p%d] blocked on token (val = %d)\n", i + 1, value);
                    sleep(t);
                }
            }

            // Fechamento dos pipes
            for (i = 0; i < n; i++)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            exit(0);
        }
    }

    // Fechamento dos pipes pai
    for (i = 0; i < n; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Aguardar a conclusão dos processos filhos
    for (i = 0; i < n; i++)
    {
        wait(NULL);
    }

    return 0;
}
