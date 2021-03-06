#include "monte_carlo.h"

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

void multiMatrizes(int **matriz1, int **matriz2, int iTemporario, int jTemporario, int n){
	int k, **matrizAUX;
	matrizAUX = (int **) malloc(n*sizeof(int*));
	for (int i = 0; i < n; ++i)
		matrizAUX[i] = (int *) malloc(n*sizeof(int));
    for (k = 0; k < n; ++k) {
		// printf("K: %d\tI %d\tJ %d\tN %d\n", k, iTemporario, jTemporario, n);
        matrizAUX[iTemporario][jTemporario] += (matriz1[iTemporario][k] * matriz2[k][jTemporario]); 
    }
    matriz1[iTemporario][jTemporario] = matrizAUX[iTemporario][jTemporario];

    for (int i = 0; i < n; ++i) free(matrizAUX[i]);
   	free(matrizAUX);
}

void montecarlo_(int *a, int *b, int *n){
	// GAMBI START
	int ** matriz1, ** matriz2;
	matriz1 = (int **) malloc(*n * sizeof(int*));
	matriz2 = (int **) malloc(*n * sizeof(int*));

	for (int i = 0; i < *n; ++i) {
		matriz1[i] = malloc(*n * sizeof(int));
		matriz2[i] = malloc(*n * sizeof(int));
	}
	// GAMBI END

	for (int i = 0; i < *n; ++i)
		for (int j = 0; j < *n; ++j) 
		{
			matriz1[i][j] = a[i * (*n) + j];
			matriz2[i][j] = b[i * (*n) + j];
		}
	int **matX, **matrizAleatoriaResposta;
	int i = 0, j = 0, posicaoTrue = 0, matrizFail = 0;
	i = 0;
	j = 0;

	// Aloco Memoria para a matX
	matX = (int **) malloc(*n * sizeof(int*));
	if (matX == NULL){
		printf("Erro ao Alocar matX.\n");
		exit(1);
	}
	for (i = 0; i < *n; ++i)
		matX[i] = (int *) malloc(*n*sizeof(int));

	// Aloco memoria para matrizAleatoriaRespota
	matrizAleatoriaResposta = (int **) malloc(*n*sizeof(int*));
	if (matrizAleatoriaResposta == NULL){
		printf("Erro ao Alocar matrizAleatoriaRespota.\n");
		exit(1);
	}
	for (i = 0; i < *n; ++i)
		matrizAleatoriaResposta[i] = (int *) malloc(*n*sizeof(int));
		
	// Gero a matriz randomica de Zeros e Uns
	matrizXAleatoria(matX, *n);
	matrizRespostaAleatoria(matrizAleatoriaResposta, *n);

	// Pegando 50% das posições das matrizes e verificando se batem
	int posicoesI[*n];
	int posicoesJ[*n];
	for (i = 0; i < *n; ++i){
		srand( (unsigned)time(NULL) );
		posicoesI[i] = rand()% (*n);
		posicoesJ[i] = rand()% (*n);
	}
	int iTemporario, jTemporario;
	do{
		for (i = 0; i < *n; ++i){
			iTemporario = posicoesI[i];
			jTemporario = posicoesJ[i];
			// Multiplico a posição caida atraves do rand
			if (matrizFail == 0){
				multiMatrizes(matriz1, matriz2, iTemporario, jTemporario, *n);
				multiMatrizes(matriz1, matX, iTemporario, jTemporario, *n);
			}			
			multiMatrizes(matrizAleatoriaResposta, matX, iTemporario, jTemporario, *n); 
			// Lembrando a Matriz1 contem resposta de 50% da multiplicação
			if (matriz1[iTemporario][jTemporario] == matrizAleatoriaResposta[iTemporario][jTemporario]){
				// Posivel matriz solução
				posicaoTrue += 1;
				// printf("Posição true %d\n", posicaoTrue);
			}else{
				// Troco a matriz aleatoria
				matrizRespostaAleatoria(matrizAleatoriaResposta, *n);
				matrizFail += 1;
				posicaoTrue = 0;
				// printf("%d\n", matrizFail);
				break;
			}
		}
	}while(posicaoTrue != *n && matrizFail != constRepeat);


	puts("Matriz A");
	for (i = 0; i < *n; ++i){
		printf("\n");
		for (j = 0; j < *n; ++j)
			printf("%d ", matriz1[i][j]);
	}
	printf("\n");

	puts("Matriz B");
	for (i = 0; i < *n; ++i){
		printf("\n");
		for (j = 0; j < *n; ++j)
			printf("%d ", matriz2[i][j]);
	}
	printf("\n\n");

	// Teste de Print Somente
	puts("Matrix aleatoria resposta");
	for (i = 0; i < *n; ++i){
		printf("\n");
		for (j = 0; j < *n; ++j)
			printf("%d ", matrizAleatoriaResposta[i][j]);
	}
	printf("\n");


	// Libera matX
	for (i = 0; i < *n; ++i)
		free(matX[i]);
	free(matX);
	// Libera matrizAleatoriaResposta
	for (i = 0; i < *n; ++i)
		free(matrizAleatoriaResposta[i]);
	free(matrizAleatoriaResposta);
}
