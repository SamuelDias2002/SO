//mainstd.c
#include <stdio.h>
#include <unistd.h>
int main(){
 FILE * fp; char c;
 fp = fopen("test.txt","r");
 printf ("Primeiro Caracter %c\n", fgetc(fp));
 
 
 while ( (c = fgetc(fp)) !=EOF )
 write( 1, &c, 1 );
 fclose(fp);
}