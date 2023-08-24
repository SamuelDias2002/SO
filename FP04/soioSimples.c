/*
 *  soio.c
 *
 *  Created by Paul Crocker on 3/11/07.
 *  Copyright 2007 UBI. All rights reserved.
 *
 */
#include "soio.h"

SOFILE *sofopen(const char *nome, const char *mode)
{
  SOFILE *novo = NULL;
  int fd;

  if (mode[0] == 'r')
    fd = open(nome, O_RDONLY, 0);
  else
    exit(1); // agora apenas para leitura !

  if (-1 == fd)
    return NULL; // caso erro

  char fdc = '0' + fd; // ok if fd<=9
  write(2, "FD ", 3);
  write(2, &fdc, 1);
  write(2, "\n", 1);

  novo = (SOFILE *)malloc(sizeof(SOFILE));
  novo->buf = (char *)malloc(MAXBUFFSIZE);
  novo->fd = fd;
  novo->index = 0;
  novo->size = 0;
  return novo;
}

// Funções não implementadas

int sofclose(SOFILE *fp)
{
  int n;
  if (fp != NULL)
  {
    n = close(fp->fd);
    if (n < 0)
    {
      return -1;
    }
    free(fp->buf);
    free(fp);
  }
  else
  {
    return -1;
  }
}

int sofgetc(SOFILE *fp)
{
  if (fp != NULL)
  {
    if (fp->index == fp->size)
    {

      int number_of_bytes = read(fp->fd, fp->buf, MAXBUFFSIZE);

      if (number_of_bytes == 0)
      {
        return EOF;
      }

      fp->size = number_of_bytes;
      fp->index = 0;
    }
  }
  else {
    return -1;
  }
  return fp->buf[(fp->index)++];
}

int sofflush(SOFILE *fp)
{
  if (fp == NULL)
  {
    return -1;
  }
  fp->index = 0;
  fp->size = 0;
  return 0;
}
