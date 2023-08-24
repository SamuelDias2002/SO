/*
 *  soio.c
 *
 *  Created by Paul Crocker on 3/11/07.
 *  Copyright 2007 UBI. All rights reserved.
 *
 */
#include "soio.h"
#include<stdio.h>

SOFILE *sofopen (const char *nome, const int mode)
{
  SOFILE *novo = NULL;
  int fd;

  if (mode == 'r')
    fd = open (nome, O_RDONLY, 0);
  else if(mode == 'w')
    fd = open (nome, O_RDWR, 0);
  else if(mode == 'a')
    fd = open (nome, O_APPEND, 0);
  else
    exit (1);			//agora apenas para leitura !

  if (-1 == fd)
    return NULL;		//caso erro

  //char fdc ='0'+fd;  //ok if fd<=9
  //write(2,"FD ",3); write(2,&fdc,1);  write(2,"\n",1);

  novo = (SOFILE *) malloc (sizeof (SOFILE));
  novo->buf = (char *) malloc (MAXBUFFSIZE);
  novo->fd = fd;
  novo->index = 0;
  novo->size = 0;
  novo->modo = mode;
  return novo;
}

int sofclose (SOFILE * fp)
{
  if(fp != NULL){
    if (close(fp->fd) == -1) {
      return -1;  
    }
    free(fp->buf);
    free(fp);
  }
  return 0;
}

int sofgetc (SOFILE * fp)
{				
  char letra;

  fp->size = read(fp->fd, &letra, sizeof(char));

  if (fp->size == -1) {
    return -1;
  }
  else if(fp->size == 0){
    return EOF;
  }
  else{
    fp->buf[fp->index] = letra;
    fp->index++;
    
    return letra;
  }
}

int sofflush (SOFILE * fp)
{
  if (fp == NULL)
  {
    return -1;
  }
  fp->index = 0;
  fp->size = 0;

  return 0;
}


int sofputc(SOFILE * fp, int c){
  fp->buf[fp->index++] = c; 
  fp->size++;
  if(fp->index == fp->size){
    if(fp->modo == 'w'){
      write(fp->fd, fp->buf, fp->size);
      sofflush(fp);
    }
  }
  return 0;
}

