#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define FILE_MODE ( S_IRUSR | S_IWUSR )

int main(void)
{
 int fd;
 char nome[]="cat";
 char *args[2];
 args[0] = nome;
 args[1] = NULL;
 fd=open("input.txt",O_RDONLY);
 if (fd<0) { fprintf(stderr,"open error"); return (1);}
 
 //close (STDIN_FILENO) //followed by dup(fd); is equivalent to dup2()
 dup2(fd, STDIN_FILENO);
 close (fd);
 fd=creat("output.txt",FILE_MODE);
 if (fd<0) { fprintf(stderr,"creat error"); return (1);} 
 dup2(fd, STDOUT_FILENO);
 close (fd);
 execvp(nome,args);
 return(0);
}