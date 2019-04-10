#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXINT 1000000
#define NUMQUEEN 4
#define TABU NUMQUEEN/2

typedef struct populacao{
    int QueenList[NUMQUEEN];
    int ConflictQueen;
}Populacao;

//REPRESENTACAO E COMPOSTA POR UM VETOR DE N RAINHAS CONTENDO A POSICAO NA LINHA DE CADA RAINHA
//HEURISTICA E A QUANTIDADE DE RAINHAS EM CONFLITOS - 1

int verificQueen(int QueenList[NUMQUEEN]); //FUNCAO RESPONSAVEL POR VERIFICAR SE AS RAINHAS ESTAO EM CONFLITOS
int solution(int QueenList[NUMQUEEN], Populacao populacao[5]);
int shattering(Populacao populacao[5]);

int main(){
    int QueenList[NUMQUEEN];    //POSICAO DAS RAINHAS, CADA RAINHA PERTENCE A UMA COLUNA NO QUAL O VALOR PRESENTE REPRESENTA A LINHA EM QUE ELA ESTA POSICIONADA
    int ConflictQueen, aux;          //VARIAVEL PARA CONTROLE DE QUANTIDADES DE RAINHAS EM CONFLITO
    Populacao populacao[5];
    srand(time(NULL));

    //FOR USADO PARA INICIAR AS RAINHAS COLOCANDO TODAS NA MESMA LINHA, NO CASO LINHA 0
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < NUMQUEEN; j++)
            populacao[i].QueenList[j] = rand()%NUMQUEEN;
        populacao[i].ConflictQueen = verificQueen(populacao[i].QueenList);
    }

    int interacoes = solution(QueenList, populacao);
    for(int i = 0; i < NUMQUEEN; i++)
        printf("%d ", QueenList[i]);
    printf("\nNumero de rainhas em conflito: %d\nNumero de Interacoes: %d\n", verificQueen(QueenList), interacoes);

    return 0;
}

int shattering(Populacao populacao[5]){
    int i, aux = 0, selection;
    int auxVet[5];

    for(i = 0; i < 5; i++){
        aux += populacao[i].ConflictQueen;
    }
    //printf("aux1 = %d\n", aux);
    auxVet[0] = (aux - populacao[0].ConflictQueen) ;
    for(i = 1; i < 5; i++){
        auxVet[i] = auxVet[i-1] + (aux - populacao[i].ConflictQueen);
    }
    aux = auxVet[4];
    //printf("aux = %d\n", aux);
    selection = rand()%aux;

    //printf("%d Selection\n", selection);
    if(selection < auxVet[0])
        return 0;
    else if(selection >= auxVet[0] && selection < auxVet[1])
        return 1;
    else if(selection >= auxVet[1] && selection < auxVet[2])
        return 2;
    else if(selection >= auxVet[2] && selection < auxVet[3])
        return 3;
    else if(selection >= auxVet[3])
        return 4;

}

int solution(int QueenList[NUMQUEEN], Populacao populacao[5]){
    Populacao populacaoAux[5], newPopulacao[5];
    int aux, random, mutation = 10, count = 0;

    while(1){
        count++;
        for(int i = 0; i < 5; i++){
            aux = shattering(populacao);
            memcpy(populacaoAux[i].QueenList, populacao[i].QueenList, sizeof(int)*NUMQUEEN);
            populacaoAux[i].ConflictQueen = populacao[aux].ConflictQueen;
        }

        //CROSSOVER
        for(int i = 0; i < 5; i++){
            aux = shattering(populacaoAux);
            for(int j = 0; j < NUMQUEEN/2; j++){
                newPopulacao[i].QueenList[j] = populacaoAux[aux].QueenList[j];
            }
            aux = shattering(populacaoAux);
            for(int j = NUMQUEEN/2; j < NUMQUEEN; j++){
                newPopulacao[i].QueenList[j] = populacaoAux[aux].QueenList[j];
            }
        }

        //MUTACAO
        for(int i = 0; i < 5; i++){
            aux = rand()%mutation;
            if(aux == 0){
                mutation = 10;
                aux = rand()%NUMQUEEN;
                random = rand()%NUMQUEEN;
                newPopulacao[i].QueenList[aux] = random;
            }
        }

        //ATUALIZA STATUS DA POPULACAO
        for(int i = 0; i < 5; i++){
            aux = shattering(populacao);
            memcpy(populacao[i].QueenList, newPopulacao[i].QueenList, sizeof(int)*NUMQUEEN);
            populacao[i].ConflictQueen = verificQueen(populacao[i].QueenList);
        }

        for(int i = 0; i < 5; i++)
            if(populacao[i].ConflictQueen == 0){
                memcpy(QueenList, populacao[i].QueenList, sizeof(int)*NUMQUEEN);
                return count;
            }
    }
}

int verificQueen(int QueenList[NUMQUEEN]){
    //PRE: ARRAY DE RAINHAS
    //POS: QUANTIDADE DE RAINHAS EM CONFLITO
    int aux = 0;
    int cont;

    for(int i = 0; i < NUMQUEEN - 1; i++){
        cont = 1;
        for(int j =  i + 1; j < NUMQUEEN; j++){
            if(QueenList[i] == QueenList[j] || QueenList[j] == QueenList[i] + cont || QueenList[j] ==  QueenList[i] - cont)
                aux++;
            cont++;
        }
    }
    return aux;
}
