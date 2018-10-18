#include <stdio.h>
#include <stdlib.h>

int* geraMatrizRand(int n); // Paralelizo a criação das 3 matrizes
int monteCarlo(int *matriz1, int *matriz2, int *matriz3, int n); // Paralelizo a multiplicação das matriz

int main(){
	int n;
	int *matriz1, *matriz2, *matriz3; // Que seria a matriz A,B e C
	int winer;
	printf("Digite o tamanho das matrizes\n");
	scanf("%d\n", &n);
	matriz1 = geraMatrizRand(n);
	matriz2 = geraMatrizRand(n);
	matriz3 = geraMatrizRand(n);
	winer = monteCarlo(matriz1, matriz2, matriz3, n);
	return 0;
};

int* geraMatrizRand(int n){
	int *matriz;

	matriz = malloc((n*n)*sizeof(int));
	
	if (matriz == NULL){
		printf("Memoria nao alocada\n");
		exit(1);
	}
	
	for (int i = 0; i < (n*n); ++i){
		*(matriz+i) = rand();
	}

	return matriz; 
}

int monteCarlo(int *matriz1, int *matriz2, int *matriz3, int n){
	int *matX, *Bx, *ABx, *Cx;
	// Preciso de A(Bx), Cx, e escolher aleatóriamente a matrix X

	// Gera a matrix Xe{0,1}^n
	matX = malloc((n*n)*sizeof(int));
	if (matX == NULL){
		printf("Erro ao alocar matriz X\n");
	}

	for (int i = 0; i < (n*n); ++i){
		*(matX+i) = rand()%2;
	}
	// CONTINUA AMANHA ...
	Bx = malloc((n*n)*sizeof(int));
	if (Bx == NULL){
		printf("Erro ao alocar matriz X\n");
	}	
	// Multiplico Bx
	for (int i = 0; i < (n*n); ++i){
		for (int j = 0; j < (n*n); ++j){
			
		}
	}
	
	return 0;
};