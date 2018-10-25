.PHONY: all c fortran clear

# C
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm

# Fortran
FT = gfortran 

all: c fortran clear

c:	
	$(CC) ./c/monteCarlo.c $(CFLAGS) -o ./bin/cmontecarlo
	- ./bin/cmontecarlo

fortran: 
	$(FT) ./fortran/monte_carlo.f -o ./bin/fmontecarlo
	- ./bin/fmontecarlo

# Tests
testc: 
	$(CC) ./c/testeMonteCarloMultiMat.c $(CFLAGS) 

testfortran: 
	$(FT) ./fortran/monte_carlo_test.f -o ./bin/fmontecarlotest
	- ./bin/fmontecarlotest

clear: 
	- rm -f *.o exec exe ./bin/*
