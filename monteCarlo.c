#include <stdio.h>
#include <stdlib.h>
#define constRepeat 1000

void geraMatrizRand(int **matriz, int n); // Paralelizo a criação das 3 matrizes
int** monteCarlo(int **matriz1, int **matriz2, int n);
void matrizXAleatoria(int **matX, int n);
void matrizRespostaAleatoria(int **matX, int n);
int** multiMatrizes(int **matriz1, int **matriz2, int n);

int main(){
	int n, i, j;
	int **matriz1, **matriz2;
	printf("Dgite o tamanho da Matriz: ");
	scanf("%d", &n);
	
	// Alocação da matriz 1
	matriz1 = (int **) malloc(n*sizeof(int*));
	if (matriz1 == NULL){
		printf("Erro ao alocar matriz1.\n");
		exit(1);
	}
	for (i = 0; i < n; ++i)
		matriz1[i] = (int *) malloc(n*sizeof(int));
	
	// ALocação da Matriz 2
	matriz2 = (int **) malloc(n*sizeof(int*));
	if (matriz2 == NULL){
		printf("Erro ao alocar matriz2\n");
		exit(1);
	}
	for (i = 0; i < n; ++i)
		matriz2[i] = (int *) malloc(n*sizeof(int));
	
	// Gero mas matrizes randomicas
	geraMatrizRand(matriz1, n);
	geraMatrizRand(matriz2, n);

	// Teste de Print Somente
	for (i = 0; i < n; ++i){
		printf("\n");
		for (j = 0; j < n; ++j)
			printf("%d ", matriz1[i][j]);
	}
	printf("\n");
	for (i = 0; i < n; ++i){
		printf("\n");
		for (j = 0; j < n; ++j)
			printf("%d ", matriz2[i][j]);
	}
	printf("\n");

	// Libero a memoria alocada para cada matriz
	for (i = 0; i < n; ++i)
		free(matriz1[i]);
	free(matriz1);

	for (i = 0; i < n; ++i)
		free(matriz2[i]);	
	free(matriz2);
	return 0;
};

void geraMatrizRand(int **matriz, int n){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			matriz[i][j] = rand()%100;
	}
};

void matrizRespostaAleatoria(int **matX, int n){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			matX[i][j] = rand()%19603;
	}
};

void matrizXAleatoria(int **matX, int n){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			matX[i][j] = rand()%2;
	}	
}

int** monteCarlo(int **matriz1, int **matriz2, int n){
	int **matX, **matrizAleatoriaResposta;
	int i, j, posicaoTrue, matrizFail;
	// Aloco Memoria para a matX
	matX = (int **) malloc(n*sizeof(int*));
	if (matX == NULL){
		printf("Erro ao Alocar matX.\n");
		exit(1);
	}
	for (i = 0; i < n; ++i)
		matX[i] = (int *) malloc(n*sizeof(int));

	// Aloco memoria para matrizAleatoriaRespota
	matrizAleatoriaResposta = (int **) malloc(n*sizeof(int*));
	if (matrizAleatoriaResposta == NULL){
		printf("Erro ao Alocar matrizAleatoriaRespota.\n");
		exit(1);
	}
	for (i = 0; i < n; ++i)
		matrizAleatoriaResposta[i] = (int *) malloc(n*sizeof(int));
		
	// Gero a matriz randomica de Zeros e Uns
	matrizXAleatoria(matX, n);
	matrizRespostaAleatoria(matrizAleatoriaResposta, n);

	// Multiplicando as Matrizes
	int randLinha = rand()%n;
	/* 	ACHO QUE ISSO DEVE ACONTECER DENTRO DO DO DO-WHILE POIS DESSA
		FORMA PEGO A POSIÇÃO MULTIPLICO E JA COMPARO COM A RESULTADO SEM
		PRECISAR FAZER UM SEGUNDA VERIFICAÇÃO, FAÇO TUDO NO MESMO MOMENTO
		DESSA FORMA GARANDO A RANDOMICIDADE NAS POSIÇÕES DE 50% DA MATRIZ   */
	matriz1 = multiMatrizes(matriz1, matriz2, n);
	matriz1 = multiMatrizes(matriz1, matX, n);	
	matrizAleatoriaResposta = multiMatrizes(matrizAleatoriaResposta, matX, n);

	// Pegando 50% das posições das matrizes e verificando se batem
	do{
		for (i = 0; i < (n-(n/2)); ++i){
			int iTemporario = rand()%n;
			int jTemporario = rand()%n;

			// Multiplico a posição caida atraves do rand
			multiMatrizes(matriz1, matriz2, iTemporario, jTemporario);
			multiMatrizes(matriz1, matX, iTemporario, jTemporario);
			multiMatrizes(matrizAleatoriaResposta, matX, iTemporario, jTemporario); 
			// Lembrando a Matriz1 contem resposta de 50% da multiplicação
			if (matriz1[iTemporario][jTemporario] == matrizAleatoriaResposta[iTemporario][jTemporario])
				// Posivel matriz solução
				posicaoTrue += 1;
			else{
				// Troco a matriz aleatoria
				matrizRespostaAleatoria(matrizAleatoriaResposta, n);
				matrizFail += 1;
				posicaoTrue = 0;
				break;
			}
		}
	}while(posicaoTrue != (n/2) || matrizFail != constRepeat);
	

	// Libera matX
	for (i = 0; i < n; ++i)
		free(matX[i]);
	free(matX);
	// Libera matrizAleatoriaResposta
	for (i = 0; i < n; ++i)
		free(matrizAleatoriaResposta[i]);
	free(matrizAleatoriaResposta);
};

void multiMatrizes(int **matriz1, int **matriz2, int iFinal, int jFinal){
	int i, j, k;
	for (i = iFinal; i < (iFinal+1); ++i) {
      for (j = jFinal; j < (jFinal+1); ++j) {
        for (k = 0; k < n; ++k) {
          matriz1[i][j] = matriz1[i][j] + (matriz1[i][k] * matriz2[k][j]); 

        }

      }
    
    }
    return matriz1;
};
