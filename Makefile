.PHONY: all c fortran clear

# C
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -I. -I./c/ -I./fortran

# Fortran
FT = gfortran 

all: c fortran clear

c:	
	# $(CC) -c ./c/matrix_initialization.c -I. -o ./modules/matrix_initialization.o
	# $(CC) -c ./c/monte_carlo.c -I. -o ./modules/monte_carlo.o
	$(CC) -c ./c/matrix_initialization.c ./c/monte_carlo.c -I. 
	mv *.o ./modules/
	$(CC) ./modules/*.o ./c/test.c $(CFLAGS) -o ./bin/cmontecarlo -I.
	- ./bin/cmontecarlo

fortran: 
	$(FT) ./fortran/fortranMonteCarlo.f90 -o ./bin/fmontecarlo
	- ./bin/fmontecarlo

modularize:
	$(FT) -c ./fortran/matrix_initialization.f90 ./fortran/monte_carlo.f90
	$(CC) -c ./c/matrix_initialization.c ./c/monte_carlo.c

# Tests
testc: 
	$(CC) ./c/testeMonteCarloMultiMat.c $(CFLAGS) 

testfortran: 
	$(FT) ./fortran/monte_carlo_test.f -o ./bin/fmontecarlotest
	- ./bin/fmontecarlotest

clear: 
	rm -f *.o exec exe ./bin/* ./modules/*.o

