//main.c
#include "soio.h"
#include <unistd.h>
#include <stdio.h>

int main(){
  SOFILE * fp; char c;
  
  fp = sofopen("fputc.txt", 'w');

  sofputc(fp, 'o');
  sofputc(fp, 'l');
  sofputc(fp, 'K');

  sofclose(fp);

  fp = sofopen("fputc.txt", 'w');
  while ((c = sofgetc(fp)) !=EOF ){
    write(1, &c, 1 );
  }
  sofclose(fp);


  return 0;
}
