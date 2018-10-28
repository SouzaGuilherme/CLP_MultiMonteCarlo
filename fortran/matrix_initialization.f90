! Modulo para inicialização da matrix
! Fortran implementa inicialização de matriz
! e inclui calculo feito em c
! Gera executavel

module GLOBAL
    IMPLICIT none
    INTEGER :: seed
end module

! Precisa implementar
module matrix_initialization
implicit none

contains
    subroutine geraMatrizRand()
    !    srand( (unsigned)time(NULL) );
    !    for (int i = 0; i < n; ++i){
    !        for (int j = 0; j < n; ++j)
    !            matriz[i][j] = rand()%100;
    !    }
    end subroutine geraMatrizRand

    subroutine matrizRespostaAleatoria()
    !    srand( (unsigned)time(NULL) );
    !    for (int i = 0; i < n; ++i){
    !        for (int j = 0; j < n; ++j)
    !            matX[i][j] = rand()%19603;
    !    }
    end subroutine matrizRespostaAleatoria

    subroutine matrizXAleatoria()
    !    srand( (unsigned)time(NULL) );
    !    for (int i = 0; i < n; ++i){
    !        for (int j = 0; j < n; ++j)
    !            matX[i][j] = rand()%2;
    !    }	
    end subroutine matrizXAleatoria

end module

program main
use global
use matrix_initialization
implicit none
    
    ! Codigo aqui

end program main
