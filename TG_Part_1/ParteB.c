#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define BUFFER_SIZE 101
#define FILE_MODE (O_WRONLY | O_CREAT | O_APPEND)

void writeRandomLettersToFile(const char *filename, int numLetters)
{
    int fd = open(filename, FILE_MODE);

    if (fd < 0)
    {
        printf("Erro ao abrir %s\n", filename);
        return;
    }

    char letter;
    srand(time(NULL));

    for (int i = 0; i < numLetters; i++)
    {
        letter = 'a' + (rand() % 26); // Gera número random entre 0 e 26 e soma ao valor ASCII de a

        if (write(fd, &letter, 1) < 0)
        {
            perror("Erro ao escrever\n");
            close(fd);
            return;
        }

        fsync(fd); 
        // Sincroniza o ficheiro com o que foi escrito durante o if
        // https://man7.org/linux/man-pages/man2/fsync.2.html
    }

    close(fd);
}

void print_instructions(const char *string1, const char *string2)
{
    int len1 = strlen(string1);
    int len2 = strlen(string2);

    if (len2 > len1)
        return; //void

    const char *ptr = strstr(string1, string2); // Compara strings e da return a 1ª instancia
    if (ptr == NULL)
    {
        printf("A string original não está contida na string encriptada\n");
        return;
    }

    int offset = ptr - string1; // Posição incial
    int remaining = len1 - offset - len2; // Resto

    printf("i %d\n", offset);
    printf("r %d\n", len2);

    if (remaining > 0)
    {
        printf("+ %d\n", remaining); 
        // Observa o resto e imprime o valor que deve ser acompanhado por +
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <.bin> <string>", argv[0]);
        return 1;
    }

    int file_input = open(argv[1], O_RDONLY);

    if (file_input < 0)
    {
        printf("Erro ao abrir <.bin>\n");
        return 1;
    }

    int file_output = open(argv[2], FILE_MODE);

    if (file_output < 0)
    {
        printf("Erro ao abrir <string>\n");
        close(file_input);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int len;

    while ((len = read(file_input, buffer, BUFFER_SIZE - 1)) > 0)
    {
        writeRandomLettersToFile(argv[2], 5);

        for (int i = 0; i < len; i++)
        {
            if (buffer[i] == ' ')
            {
                writeRandomLettersToFile(argv[2], 10);
            }
            else
            {
                write(file_output, &buffer[i], 1);
            }
            
        }

        writeRandomLettersToFile(argv[2], 5);
        printf("Encriptação concluída com sucesso\n");
    }

    if (len < 0)
    {
        perror("Erro ao ler <.bin>\n");
        close(file_input);
        close(file_output);
        return 1;
    }

    if (lseek(file_output, 0, SEEK_SET) < 0 || lseek(file_input, 0, SEEK_SET) < 0)
    {
        perror("Erro ao mover o indicador de posição\n");
        close(file_input);
        close(file_output);
        return 1;
    }

    close(file_input);
    close(file_output);

    int fi = open(argv[2], O_RDONLY);

    char str[BUFFER_SIZE];
    int str_len = read(fi, str, BUFFER_SIZE - 1);

    if (str_len < 0)
    {
        perror("Erro ao abrir ficheiro\n");
        close(fi);
        return 1;
    }

    str[str_len] = '\0';

    char *sub_str = strtok(buffer, " ");
    int i = 1;

    while (sub_str != NULL)
    {

        print_instructions(str, sub_str);
        sub_str = strtok(NULL, " "); // devolve um ponteiro para a próxima palavra na string apontada por endereço de origem
        i++;
    }
    printf("s 0\n");
    close(fi);

    return 0;
}
