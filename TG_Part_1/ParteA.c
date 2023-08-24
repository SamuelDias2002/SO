#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 101

int main(int argc, char *argv[])
{

    int file_input = open(argv[1], O_RDONLY);

    if (file_input < 0)
        return 1;

    char buffer[BUFFER_SIZE];
    int buffer_length = 0;
    char instrucao;
    int qtd;

    while (scanf(" %c %d", &instrucao, &qtd) == 2)
    {

        switch (instrucao)
        {
        case 'i':
            lseek(file_input, qtd, SEEK_SET);
            break;
        case 'f':
            lseek(file_input, -qtd, SEEK_END);
            break;
        case '+':
            lseek(file_input, qtd, SEEK_CUR);
            break;
        case '-':
            lseek(file_input, -qtd, SEEK_CUR);
            break;
        case 'r':
            if (qtd > 0 && buffer_length + qtd <= BUFFER_SIZE)
            {
                read(file_input, buffer + buffer_length, qtd);
                buffer_length += qtd;
            }
            break;
        case 'l':
            buffer_length = 0;
            break;
        case 's':
            write(STDOUT_FILENO, buffer, buffer_length);
            write(STDOUT_FILENO, "\n", 1);
            return 0;
        }
    }

    return 0;
}
