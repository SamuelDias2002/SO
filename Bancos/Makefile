#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm -lpthread
OBS= bancos.o

#Alvo por defeito é o primeiro
all :  bancos

bancos.o : bancos.h bancos.c
	$(CC) $(FLAGS) bancos.c
bancos : $(OBS)
	$(CC)  -o bancos  $(OBS) $(LIBS)
clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"