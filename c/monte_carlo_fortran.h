#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define constRepeat 1000000

void multiMatrizes_(int *matriz1, int *matriz2, int *iTemporario, int *jTemporario, int *n);
void montecarlo_(int *a, int *b, int *n);
void matrizXAleatoria_(int *matrix, int *n);

#endif // ! MONTE_CARLO_H 
