.PHONY: all clear cmodularize fmodularize ccallf fcallc

# C
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -I. -I./c/ -I./fortran

# Fortran
FT = gfortran 

all: fcallc ccallf clear

cmodularize:	
	$(CC) -c ./c/matrix_initialization.c -o cmatrix_initialization.o -I.
	$(CC) -c ./c/monte_carlo.c -o cmonte_carlo.o -I.
	mv *.o ./modules/

fmodularize:	
	$(FT) -c ./fortran/matrix_initialization.f90 -o fmatrix_initialization.o 
	$(FT) -c ./fortran/monte_carlo.f90 -o fmonte_carlo.o
	mv *.o ./modules/

ccallf:
	$(FT) -c ./fortran/monte_carlo.f90 -ffree-form -o fmonte_carlo.o -I. 
	mv *.o ./modules/
	$(CC) ./modules/fmonte_carlo.o ./c/test.c $(CFLAGS) -lgfortran -o ./bin/ccallf
	- ./bin/ccallf

fcallc:
	$(CC) -c ./c/monte_carlo.c -o cmonte_carlo.o -I. -D FORTRAN
	$(FT) -c ./fortran/matrix_initialization.f90 -ffree-form -o fmatrix_initialization.o 
	- mv *.o ./modules/
	$(FT) ./modules/fmatrix_initialization.o ./modules/cmonte_carlo.o -o ./bin/fcallc
	- ./bin/fcallc

clear: 
	rm -f *.o exec exe ./bin/* ./modules/*.o

