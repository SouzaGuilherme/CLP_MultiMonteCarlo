#include "matrix_initialization.h"

void geraMatrizRand(int **matriz, int n){
	srand( (unsigned)time(NULL) );
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			matriz[i][j] = rand()%100;
	}
};

void matrizRespostaAleatoria(int **matX, int n){
	srand( (unsigned)time(NULL) );
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			matX[i][j] = rand()%19603;
	}
};

void matrizXAleatoria(int **matX, int n){
	srand( (unsigned)time(NULL) );
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			matX[i][j] = rand()%2;
	}	
}
