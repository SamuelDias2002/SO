#include "soio.h"
#include<unistd.h>
#include<stdio.h>

int main()
{

    SOFILE *fp;
    int linhas = 0;
    char c;
    write(2, "Test1 Test Program\n", 19);

    //TEST
    fp = sofopen("NonFile", 'r');
    if (fp == NULL)
        write(2, "File Cant be Opened\n", 20);
    else
        return 1;

    //TEST - close null pointer
    sofclose(fp);

    //TEST
    fp = sofopen("test.txt", 'r');
    if (fp != NULL)
    {
        write(2, "File Opened OK\n", 15);
        sofclose(fp);
    }
    else
        return 1;

    //TEST
    fp = sofopen("main.c", 'r');

    if (NULL != fp)
    {
        while ((c = sofgetc(fp)) != EOF)
        {
            if (linhas == 3)
            {
                sofflush(fp);
                continue;
            }
            if (c == '\n')
                linhas++;
            write(1, &c, 1);
        }
    }
    write(1, "\n", 1);
    sofclose(fp);
}
