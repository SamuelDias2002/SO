#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void streamCopy ( FILE * entrada, FILE * saida);
void alteraCharControlo ( FILE * entrada, FILE * saida );
void mostraNumLinha ( FILE * entrada, FILE * saida );


int main( int argc, char *argv[] ){
 
  if ( 1 == argc ) 
    streamCopy (stdin, stdout); 
  else {
    FILE *fptr1;

    int start=1;
    if(argv[1][0] == '-'){
      start = 2; 
    }

    for(int i=start; i< argc; i++){
      fptr1 = fopen(argv[i], "r");
      if (fptr1 == NULL){
        printf("Cannot open file %s \n", argv[i]);
        exit(0);
      }

      if(start==2){
        if(strcmp(argv[1], "-T") == 0)
          alteraCharControlo(fptr1, stdout);
        else if(strcmp(argv[1], "-n") == 0)
          mostraNumLinha(fptr1, stdout);
      }
      else
        streamCopy(fptr1, stdout);
      fclose(fptr1);
    }
  }

 return 0;
}


void streamCopy ( FILE * entrada, FILE * saida ){
 int ch; 
 while ( (ch=fgetc(entrada)) != EOF ){
 fputc( ch, saida);
 }
}

void alteraCharControlo ( FILE * entrada, FILE * saida ){
 int ch; 
 while ( (ch=fgetc(entrada)) != EOF ){
  if( ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) || (ch >= '0' && ch <= '9'))
    fputc(ch, saida);
  else
    fputs("^I", saida);
  }
}

void mostraNumLinha ( FILE * entrada, FILE * saida ){
 int ch; 
 int linha=1;
 fpos_t position;
 printf("%-10d", 0);
 while ((ch=fgetc(entrada)) != EOF ){
   if(ch == 10){
     fgetpos(entrada, &position);
     if((fgetc(entrada)) == EOF ){
       fprintf(saida, "\n");
     }
     else{
        fprintf(saida, "\n%-10d", linha);
        fsetpos(entrada, &position);
     }
     linha++;
   }
   else
    fputc( ch, saida);
 }
}
