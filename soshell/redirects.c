#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)

// redirects.c
// redirects are handled in reverse order: i) 2> ii) > OU > iii)<
int redirects(int numargs, char *args[])
{
  if (numargs < 3)
    return numargs; // Guard the following section

  // i redirect do 2>
  if (strcmp(args[numargs - 2], "2>") == 0)
  {
    int file = creat(args[numargs - 1], FILE_MODE);
    if (file < 0)
    {
      perror(NULL);
      return -1; /*indicar um erro*/
    }
    dup2(file, STDERR_FILENO);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
    close(file);
  }
  if (numargs < 3)
    return numargs; // Guard the following section

  // ii redirect stdout >
  if (strcmp(args[numargs - 2], ">") == 0)
  {
    int file1 = creat(args[numargs - 1], FILE_MODE);
    if (file1 < 0)
    {
      perror(NULL);
      return -1; /*indicar um erro*/
    }
    dup2(file1, STDOUT_FILENO);
    close(file1);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
  }
  else
  {
    // verificar caso de append (>>)
    // tratar do >> open : O_WRONLY | O_APPEND
    if (strcmp(args[numargs - 2], ">>") == 0)
    {
      int file2 = open(args[numargs - 1], O_WRONLY | O_APPEND);
      if (file2 < 0)
      {
        perror(NULL);
        return -1; /*indica um erro*/
      }
      dup2(file2, STDOUT_FILENO);
      close(file2);
      args[numargs - 2] = NULL;
      numargs = numargs - 2;
    }
  }
  if (numargs < 3)
    return numargs; // Guard the following section

  // iii tratar do < open : O_RDONLY
  if (strcmp(args[numargs - 2], "<") == 0)
  {
    int file3 = open(args[numargs - 1], O_RDONLY);
    if (file3 < 0)
    {
      perror(NULL);
      return -1; /*indicar um erro*/
    }
    dup2(file3, STDIN_FILENO);
    close(file3);
    args[numargs - 2] = NULL;
    numargs = numargs - 2;
  }

  return numargs;
}