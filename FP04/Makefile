# Makefile for substituiting the high level standard library
#
# type 
# make main OR make mainstd or make test or male all (para compilar tudo)
#
# define the compiler as a variable
CC = cc -Wall

all : libsoio.so main mainstd test1  fputcTeste

soio.o: soio.c soio.h
	$(CC) -c soio.c -o soio.o

main.o: main.c soio.h
	$(CC) -c main.c

fputcTeste.o: fputcTeste.c soio.h
	$(CC) -c fputcTeste.c

mainstd.o: mainstd.c
	$(CC) -c mainstd.c

test1.o: test1.c soio.h
	$(CC) -c test1.c

soio.o: soio.c soio.h
	$(CC) -fpic -c soio.c

libsoio.so: soio.o
	$(CC) -shared -fPIC -o libsoio.so soio.o

main: main.o soio.o soio.h
	$(CC) -o main main.o soio.o libsoio.so

fputcTeste: fputcTeste.o soio.o soio.h
	$(CC) -o fputcTeste fputcTeste.o soio.o libsoio.so

test1: test1.o soio.o soio.h
	$(CC) -o test1 test1.o soio.o libsoio.so

mainstd: mainstd.o 
	$(CC) -o mainstd mainstd.o libsoio.so

#para remover todos os ficheiros executaveis e temporarios : type
#make clean

clean :
	rm -f *.o *~ main test1 mainstd fputcTeste

