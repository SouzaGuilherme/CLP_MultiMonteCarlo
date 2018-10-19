#include <stdio.h>
#include <stdlib.h>
#define constRepeat 1000

int* geraMatrizRand(int *matriz, int n); // Paralelizo a criação das 3 matrizes
int monteCarlo(int *matriz1, int *matriz2, int n); // Paralelizo a multiplicação das matriz
int* matrizXAleatoria(int *matX, int n);

int main(){
	int n;
	int *matriz1, *matriz2; // Que seria a matriz A,B e C
	int winer;
	printf("Digite o tamanho das matrizes\n");

	scanf("%d", &n);
	
	matriz1 = malloc((n*n)*sizeof(int));
	if (matriz1 == NULL){
		printf("Memoria nao alocada\n");
		exit(1);
	}
	matriz1 = geraMatrizRand(matriz1, n);

	matriz2 = malloc((n*n)*sizeof(int));
	if (matriz2 == NULL){
		printf("Memoria nao alocada\n");
		exit(1);
	}
	matriz2 = geraMatrizRand(matriz2, n);

	winer = monteCarlo(matriz1, matriz2, n);
	printf("Pronto\n");
	free(matriz1);
	free(matriz2);
	return 0;
};

int* geraMatrizRand(int *matriz, int n){
	for (int i = 0; i < (n*n); ++i){
		*(matriz+i) = rand()%100;
	}

	return matriz; 
}

int* geraMatrizResult(int *matriz, int n){
	for (int i = 0; i < (n*n); ++i){
		*(matriz+i) = rand()%1000;
	}

	return matriz; 
}

int monteCarlo(int *matriz1, int *matriz2, int n){
	int *matriz3, *matX, *Bx, *ABx, *Cx;
	int numberTrue =0, numberRepeatMatX=0, numberRepeatMatC=0;

	matriz3 = malloc((n*n)*sizeof(int));
	if (matriz3 == NULL){
		printf("Memoria nao alocada\n");
		exit(1);
	}
	matriz3 = geraMatrizResult(matriz3, n);
	matX = malloc((n*n)*sizeof(int));
	if (matX == NULL)
		printf("Erro ao alocar matriz X\n");
	matX = matrizXAleatoria(matX, n);
	
	do{
		Bx = malloc((n*n)*sizeof(int));
		if (Bx == NULL)
			printf("Erro ao alocar matriz Bx\n");	
		// Multiplico Bx
		for (int i = 0; i < (n*n); ++i){
			for (int j = 0; j < n; ++j){
				*(Bx+i) += (*matriz2+(j*(n)))*(*matX+(j*(n)));
			}
		}
		
		ABx = malloc((n*n)*sizeof(int));
		if (ABx == NULL)
			printf("Erro ao alocar matriz X\n");	
		// Multiplico A(Bx)
		for (int i = 0; i < n*n; ++i){
			for (int j = 0; j < n*n; ++j){
				*(ABx+i) += (*matriz1+(j*(n)))*(*Bx+(j*(n)));
			}
		}

		Cx = malloc((n*n)*sizeof(int));
		if (Cx == NULL)
			printf("Erro ao alocar matriz X\n");
		// Multiplico Cx
		for (int i = 0; i < n*n; ++i){
			for (int j = 0; j < n*n; ++j){
				*(Cx+i) += (*matriz3+(j*(n)))*(*matX+(j*(n)));
			}
		}

		// Verifico agora sea probabilidade
		for (int i = 0; i < (n*n); ++i){
			if((ABx+i) == (Cx+i)){
				numberTrue += 1;
			}else{
				break;
			}
		}	
		// printf("numberTrue: %d  -- n*n: %d \n",numberTrue, (n*n));
		if (numberTrue == (n*n)){
			// printf("Sucesso\n");
			// Gero outro X para verificar
			matX = matrizXAleatoria(matX, n);
			numberRepeatMatX += 1;

		}else{
			// printf("Fracasso\n");
			matriz3 = geraMatrizRand(matriz3, n);
			numberRepeatMatC += 1;
			numberRepeatMatX = 0;
		}
		
		// printf("RepeatMatx-%d  --  RepeatMatc-%d\n", numberRepeatMatX, numberRepeatMatC);
		free(Bx);
		free(ABx);
		free(Cx);

	}while((numberRepeatMatX != constRepeat) && ( numberRepeatMatC != constRepeat));

	int barraN = 0;
	if (numberRepeatMatX == constRepeat ){
		printf("Multiplicação de AB\n");
		for (int i = 0; i < (n*n); ++i){
			printf(" %d ", *(matriz3+i));
			barraN += 1;
			if (barraN == n){
				printf("\n");
				barraN = 0;
			}
		}
	}else{
		printf("Não deu Negão!\n");
	}
	free(matX);
	free(Bx);
	free(ABx);
	free(Cx);
	free(matriz3);

	return 0;
};

int* matrizXAleatoria(int *matX, int n){
	for (int i = 0; i < (n*n); ++i){
		*(matX+i) = rand()%2;
	}
	return matX;
};