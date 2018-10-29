/* Inicialização matrix em C
 * Chamada da implementação do calculo em fortran
 * Gera Executavel
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// Apenas a assinatura das funções implementadas em fortran
#include "monte_carlo_fortran.h"

int main() 
{
	srand(time(0));
	int n, i, j;
	int *matriz1, *matriz2;
	printf("Digite o tamanho da Matriz: ");
	scanf("%d", &n);
	
	// Alocação da matriz 1
	matriz1 =  malloc(n*n*sizeof(int));
	matriz2 =  malloc(n*n*sizeof(int));

	// Gero mas matrizes randomicas
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			matriz1[i*n + j] = rand() % 100;
			matriz2[i*n + j] = rand() % 100;
		}
	}

	montecarlo_(matriz1, matriz2, &n);

	free(matriz1);
	free(matriz2);
	return 0;
}
