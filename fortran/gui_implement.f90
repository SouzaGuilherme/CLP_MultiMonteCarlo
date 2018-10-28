! Modulo GLOBAL
MODULE global
    IMPLICIT none
    INTEGER :: seed
END MODULE

! Este seria o programa principal, assim como a main do Code .C
PROGRAM main
    USE global
    IMPLICIT none
    INTEGER :: tamanhoDaMatriz, i, j
    INTEGER, ALLOCATABLE, DIMENSION(:,:) :: matriz2
    !Valor inicial para funcao RAND()
    seed = 0
    !leitura do tamanho das Matrizes
    ! write(*,*) "Digite o tamanho da matriz desejada: "
    write(*,'(A)', advance='no') "Digite a dimensão da matriz:"
    read(*,*) tamanhoDaMatriz
    write(*,*) "Tamanho da Matriz digitado:", tamanhoDaMatriz
    ! INTEGER, DIMENSION(tamanhoDaMatriz, tamanhoDaMatriz) :: matriz
    ALLOCATE(matriz2(tamanhoDaMatriz, tamanhoDaMatriz))
    CALL valueRandomMatriz(matriz2, tamanhoDaMatriz)
    CALL printa(matriz2, tamanhoDaMatriz)
    DEALLOCATE(matriz2)
    STOP
END PROGRAM main

!SubRotina que imprime os valores da matriz
SUBROUTINE printa(matriz, tamanhoDaMatriz)
    IMPLICIT none
    INTEGER :: tamanhoDaMatriz, i, j
    INTEGER :: matriz(tamanhoDaMatriz, tamanhoDaMatriz)
    do i=1, tamanhoDaMatriz
        do j=1, tamanhoDaMatriz
            !PQ ISSO AQUI NAO FUNCIONA
            !write(*, '(f)', advance='no'), matriz(i,j)
            print *, matriz(i, j)
        end do
        print *
    end do
END SUBROUTINE

!SubRotina que gera valores aleaatórios para Matrizes
SUBROUTINE valueRandomMatriz(matriz, tamanhoDaMatriz)
    USE global
    IMPLICIT none
    INTEGER :: tamanhoDaMatriz, i, j, valueRandon
    INTEGER :: matriz(tamanhoDaMatriz, tamanhoDaMatriz)
    do i=1, tamanhoDaMatriz
        do j=1, tamanhoDaMatriz
            valueRandon = ran(seed)
            !matriz(i, j) = mod(valueRandon, 100)
            call random_seed(valueRandon)
            matriz(i,j) = valueRandon
            call Sleep(1)
        end do
    end do
END SUBROUTINE
