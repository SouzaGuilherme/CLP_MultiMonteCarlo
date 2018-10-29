
subroutine matrizrespostaaleatoria(matrix, n)
implicit none
    integer :: n, i, j
    integer :: matrix (n, n)
    real :: x
    do i = 1, n
        do j = 1, n
            call RANDOM_NUMBER(x)
            matrix(i, j) = FLOOR(x * 19603)
        end do
    end do
end subroutine matrizrespostaaleatoria

subroutine matrizXAleatoria(matrix, n)
implicit none
    integer :: n, i, j
    integer :: matrix (n, n)
    real :: x
    do i = 1, n
        do j = 1, n
            call RANDOM_NUMBER(x)
            matrix(i, j) = FLOOR(x * 2)
        end do
    end do
end subroutine matrizXAleatoria


SUBROUTINE multiMatrizes(matriz1, matriz2, iTemporario, jTemporario, n)
    implicit none
    INTEGER :: k, iTemporario, jTemporario, n, matrizT
    INTEGER, DIMENSION(n, n) :: matriz1, matriz2
    INTEGER, DIMENSION( :, : ), ALLOCATABLE :: matrizAUX
    ALLOCATE(matrizAUX(n, n))
    IF ( ALLOCATED (matrizAUX) ) THEN
        print *, "A has been allocated"
    ELSE
        print *, "A has not been allocated"    
    END IF


    DO k = 1, n
        matrizT = matriz1(iTemporario, k)  * matriz2(k ,jTemporario)
        matrizAUX(iTemporario, jTemporario) = matrizAUX(iTemporario, jTemporario) + matrizT
    END DO
    matriz1(iTemporario,jTemporario) = matrizAUX(iTemporario,jTemporario)
        
    DEALLOCATE(matrizAUX)
END SUBROUTINE multiMatrizes





SUBROUTINE monteCarlo(matriz1, matriz2, n)
    implicit none
    INTEGER :: i = 0, j = 0, posicaoTrue = 0, matrizFail = 0, n, iTemporario, jTemporario, seed, constRepeat
    INTEGER, DIMENSION( :, : ), ALLOCATABLE :: matX, matrizAleatoriaResposta, matriz1, matriz2
    INTEGER, DIMENSION(n) :: posicoesI, posicoesJ
    
    ALLOCATE(matX(n, n))
    ALLOCATE(matrizAleatoriaResposta(n,n))   

    !Gero a matriz randomica de Zeros e Uns
    CALL matrizXAleatoria(matX, n)
    CALL matrizrespostaaleatoria(matrizAleatoriaResposta, n)
        
        

    DO i = 1, n
        seed = 32764561
        posicoesI(i) = (-1.0)**(i) * 5.0 * rand(seed)
        posicoesJ(i) = (-1.0)**(i) * 5.0 * rand(seed)
        print *,  posicoesI(i)
        print *,  posicoesJ(i)
    END DO
    constRepeat = 1000000
     DO WHILE (posicaoTrue /= n .and. matrizFail /= constRepeat)
        DO i=1, n
            iTemporario = posicoesI(i)
            jTemporario = posicoesJ(i)
            !Multiplico a posição caida atraves do rand
            IF(matrizFail == 0) THEN
                CALL multiMatrizes(matriz1, matriz2, iTemporario, jTemporario, n)
                CALL multiMatrizes(matriz1, matX, iTemporario, jTemporario, n)
            END IF
            CALL multiMatrizes(matrizAleatoriaResposta, matX, iTemporario, jTemporario, n)
            !Lembrando a Matriz1 contem resposta de 50% da multiplicação
            IF(matriz1(iTemporario, jTemporario) == matrizAleatoriaResposta(iTemporario, jTemporario)) THEN
                !Posivel matriz solução
                posicaoTrue = posicaoTrue + 1;
            ELSE
            !Troco a matriz aleatoria
                CALL matrizrespostaaleatoria(matrizAleatoriaResposta, n)
                matrizFail = matrizFail + 1
                posicaoTrue = 0
                STOP
            ENDIF
        END DO
    END DO


    !Verifico se bateu os 50% ou se nao encontrei
    IF(posicaoTRUE == n) THEN
        ! Teste de Print Soment
        DO i = 1, n
            DO j = 1, n
                Print *, matrizAleatoriaResposta(i,j)
            END DO
        END DO
    ELSE
        print *, "Nao deu kkk"
    ENDIF

    DO i = 1, n
        DO j = 1, n
            print *, matriz1(i,j)
        END DO
    END DO

END subroutine monteCarlo

