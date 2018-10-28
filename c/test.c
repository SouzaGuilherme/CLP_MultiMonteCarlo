/* Inicialização matrix em C
 * Chamada da implementação do calculo em fortran
 * Gera Executavel
 */
#include "matrix_initialization.h"
// Apenas a assinatura das funções implementadas em fortran
#include "monte_carlo.h"

int main() 
{
	int n, i, j;
	int **matriz1, **matriz2;
	printf("Digite o tamanho da Matriz: ");
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

	// CHamo o metodo MonteCarlo
	monteCarlo(matriz1, matriz2, n);

	// Libero a memoria alocada para cada matriz
	for (i = 0; i < n; ++i)
		free(matriz1[i]);
	free(matriz1);

	for (i = 0; i < n; ++i)
		free(matriz2[i]);	
	free(matriz2);
	return 0;
}
