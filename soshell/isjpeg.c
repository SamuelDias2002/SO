#include "shell.h"
#include <stdio.h>

int isjpeg(int file)
{
  unsigned char b[4];
  read(file, b, 4);
  lseek(file, 0, SEEK_SET);
  if (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && b[3] == 0xe0)
    return 1;
  return 0;
}