#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "shell.h"
#define BUFFSIZE 128

void ioCopy(int IN, int OUT) // no error reporting
{
    int n;
    char buf[BUFFSIZE];
    while ((n = read(IN, buf, BUFFSIZE)) > 0)
    {
        if (write(OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");
}

void socp(char *fonte, char *destino)
{
    int file_input = open(fonte, O_RDONLY);
    if (file_input == -1)
    {
        perror("Erro a abrir ficheiro\n");
    }

    int file_output = creat(destino, S_IRUSR | S_IWUSR);
    if (file_output == -1)
    {
        perror("Erro a criar ficheiro");
    }
    else
    {
        ioCopy(file_input, file_output);
    }
}