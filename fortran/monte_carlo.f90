module GLOBAL
    IMPLICIT none
end module

module meu
implicit none

contains
    SUBROUTINE multiMatrizes(matriz1, matriz2, iTemporario, jTemporario, n)
        implicit none
        INTEGER :: k, iTemporario, jTemporario, n
        INTEGER, DIMENSION( :, : ), ALLOCATABLE :: matrizAUX, matriz1, matriz2, matrizT 
        ALLOCATE(matrizAUX(n, n))
        IF ( ALLOCATED (matrizAUX) ) THEN
            print *, "A has been allocated"
        ELSE
            print *, "A has not been allocated"    
        END IF


        DO k = 0, n
            matrizT = matriz1(iTemporario, k)  * matriz2(k ,jTemporario)
            matrizAUX(iTemporario, jTemporario) = matrizAUX(iTemporario, jTemporario) + matrizT
        END DO
        matriz1(iTemporario,jTemporario) = matrizAUX(iTemporario,jTemporario)
        
        DEALLOCATE(matrizAUX)
    END SUBROUTINE multiMatrizes





    SUBROUTINE monteCarlo(matriz1, matriz2, n)
        implicit none

        INTEGER :: i = 0, j = 0, posicaoTrue = 0, matrizFail = 0, matriz1, matriz2, n, iTemporario, jTemporario
        INTEGER, DIMENSION( :, : ), ALLOCATABLE :: matX, matrizAleatoriaResposta
        INTEGER, DIMENSION(n) :: posicoesI, posicoesJ
        
        ALLOCATE(matX(n, n))
        IF ( ALLOCATED (matX) ) THEN
            print *, "A has been allocated"
        ELSE
            print *, "A has not been allocated"    
        END IF

        
        ALLOCATE(matrizAleatoriaResposta(n,n))   
        IF ( ALLOCATED (matrizAleatoriaResposta) ) THEN
            print *, "A has been allocated"
        ELSE
            print *, "A has not been allocated"    
        END IF


        !Gero a matriz randomica de Zeros e Uns
        CALL matrizXAleatoria(matX, n)
        CALL matrizRespostaAleatoria(matrizAleatoriaResposta, n)
        
        

        DO i = 1, n
            seed = 32764561
            posicoesI(i) = (-1.0)**(i) * 5.0 * rand(seed)
            posicoesJ(i) = (-1.0)**(i) * 5.0 * rand(seed)
            print *,  posicoesI(i)
            print *,  posicoesJ(i)
        END DO

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
                    print *, "Posicao True"
                ELSE
                !Troco a matriz aleatoria
                    CALL matrizRespostaAlteatoria(matrizAleatoriaResposta, n)
                    matrizFail = matrizFail + 1
                    posicaoTrue = 0
                    print *, matrizFail
                    STOP
                ENDIF
            END DO
        END DO


        print *, posicaoTrue
        !Verifico se bateu os 50% ou se nao encontrei
        IF(posicaoTRUE == n) THEN
            ! Teste de Print Soment
            DO i = 1, n
                DO j = 1, n
                    print *, matrizAleatoriaResposta(i,j)
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
