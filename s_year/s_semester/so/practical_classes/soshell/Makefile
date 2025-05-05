#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: compiler, compiler flags, libraries to link, names of the object files for the executable.
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o execute.o parse.o socopy.o socalc.o sotypes.o redirect.o

#Alvo por defeito é o primeiro
all :  soshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
socopy.o : shell.h socopy.c 
	$(CC) $(FLAGS) socopy.c
socalc.o : shell.h socalc.c 
	$(CC) $(FLAGS) socalc.c
sotypes.o : shell.h sotypes.c
	$(CC) $(FLAGS) sotypes.c
redirect.o: shell.h redirect.c
	$(CC) $(FLAGS) redirect.c
soshell : $(OBS)
	$(CC)  -o soshell  $(OBS) $(LIBS)
clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Remover: Ficheiros executáveis, objetos e temporários."
