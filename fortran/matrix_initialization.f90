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
    subroutine geraMatrizRand(matrix, n)
    implicit none
        integer :: n, i, j
        integer :: matrix (n, n)
        real :: x
        do i = 1, n
            do j = 1, n
                call RANDOM_NUMBER(x)
                matrix(i, j) = FLOOR(x * 100)
            end do
        end do
    !    srand( (unsigned)time(NULL) );
    !    for (int i = 0; i < n; ++i){
    !        for (int j = 0; j < n; ++j)
    !            matriz[i][j] = rand()%100;
    !    }
    end subroutine geraMatrizRand

!   subroutine matrizRespostaAleatoria()
!   implicit none
!       integer :: n, i, j
!       integer, dimension(n, n) :: matrix
!       do i = 1, n
!           do j = 1, n
!               call RANDOM_NUMBER(x)
!               matrix(i, j) = MOD(x, 19603)
!           end do
!       end do
!   !    srand( (unsigned)time(NULL) );
!   !    for (int i = 0; i < n; ++i){
!   !        for (int j = 0; j < n; ++j)
!   !            matX[i][j] = rand()%19603;
!   !    }
!   end subroutine matrizRespostaAleatoria
!
!   subroutine matrizXAleatoria()
!   implicit none
!       integer :: n, i, j
!       integer, dimension(n, n) :: matrix
!       do i = 1, n
!           do j = 1, n
!               call RANDOM_NUMBER(x)
!               matrix(i, j) = MOD(x, 2)
!           end do
!       end do
!   !    srand( (unsigned)time(NULL) );
!   !    for (int i = 0; i < n; ++i){
!   !        for (int j = 0; j < n; ++j)
!   !            matX[i][j] = rand()%2;
!   !    }	
!   end subroutine matrizXAleatoria

end module

program main
use global
use matrix_initialization
implicit none
    
    ! Codigo aqui
    integer :: i, j, mat_size
    integer, allocatable, dimension(:, :) :: mat_a, mat_b
    
    print *, "Dimensao da matrix"
    read (*, *) mat_size

    allocate (mat_a(mat_size, mat_size))
    allocate (mat_b(mat_size, mat_size))

    call geraMatrizRand (mat_a, mat_size)
    call geraMatrizRand (mat_b, mat_size)

    print *, "Size: ", mat_size

    call monteCarlo (mat_a, mat_b, mat_size)
    
    deallocate (mat_a)
    deallocate (mat_b)
    stop
end program main
