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
    end subroutine geraMatrizRand

end module

program main
use global
use matrix_initialization
implicit none
    
    integer :: i, j, mat_size
    integer, allocatable, dimension(:, :) :: mat_a, mat_b
    
    print *, "Dimensao da matrix"
    read (*, *) mat_size

    allocate (mat_a(mat_size, mat_size))
    allocate (mat_b(mat_size, mat_size))

    call geraMatrizRand (mat_a, mat_size)
    call geraMatrizRand (mat_b, mat_size)

    call monteCarlo (mat_a, mat_b, mat_size)
    
    deallocate (mat_a)
    deallocate (mat_b)
    stop
end program main
