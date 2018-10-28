.PHONY: all c fortran clear cmodularize fmodularize ccallf fcallc

# C
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -I. -I./c/ -I./fortran

# Fortran
FT = gfortran 

all: c fortran clear

cmodularize:	
	$(CC) -c ./c/matrix_initialization.c -o cmatrix_initialization.o -I.
	$(CC) -c ./c/monte_carlo.c -o cmonte_carlo.o -I.
	mv *.o ./modules/

c:
	- make cmodularize
	$(CC) ./modules/cmatrix_initialization.o ./modules/cmonte_carlo.o ./c/test.c $(CFLAGS) -o ./bin/cmontecarlo
	- ./bin/cmontecarlo
	- make clear

fmodularize:	
	$(FT) -c ./fortran/matrix_initialization.f90 -o fmatrix_initialization.o 
	$(FT) -c ./fortran/monte_carlo.f90 -o fmonte_carlo.o
	mv *.o ./modules/

fortran:
	- make fmodularize
	$(FT) ./modules/fmatrix_initialization.o ./modules/fmonte_carlo.o ./fortran/test.f90 -o ./bin/fmontecarlo
	- ./bin/fmontecarlo
	- make clear

ccallf:
	$(FT) -c ./fortran/matrix_initialization.f90 -o fmatrix_initialization.o 
	$(CC) -c ./c/monte_carlo.c -o cmonte_carlo.o -I. -D FORTRAN
	mv *.o ./modules/
	$(CC) ./modules/fmatrix_initialization.o ./modules/cmonte_carlo.o ./c/test.c $(CFLAGS) -o ./bin/cmontecarlo
	- ./bin/cmontecarlo

fcallc:
	$(CC) -c ./c/matrix_initialization.c -o cmatrix_initialization.o
	$(FT) -c ./fortran/monte_carlo.f90 -o fmonte_carlo.o -I. 
	mv *.o ./modules/
	$(FT) ./modules/cmatrix_initialization.o ./modules/fmonte_carlo.o ./fortran/test.f90 $(CFLAGS) -o ./bin/fmontecarlo
	- ./bin/fmontecarlo

clear: 
	rm -f *.o exec exe ./bin/* ./modules/*.o

