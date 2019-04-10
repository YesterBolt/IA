#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMQUEEN 4
#define NUMPOP 5

typedef struct populacao{
    int QueenList[NUMQUEEN];
    int ConflictQueen;
}Populacao;

//REPRESENTACAO E COMPOSTA POR UM VETOR DE N RAINHAS CONTENDO A POSICAO NA LINHA DE CADA RAINHA
//HEURISTICA E A QUANTIDADE DE RAINHAS EM CONFLITOS - 1

int verificQueen(int QueenList[NUMQUEEN]); //FUNCAO RESPONSAVEL POR VERIFICAR SE AS RAINHAS ESTAO EM CONFLITOS
int solution(int QueenList[NUMQUEEN], Populacao populacao[NUMPOP]); //FUNCAO QUE RESOLVE O PROBLEMA
int shattering(Populacao populacao[NUMPOP]); //FUNCAO RESPONSAVEL POR SELECIONAR UMA DAS POPULACOES

int main(){
    int QueenList[NUMQUEEN];    //POSICAO DAS RAINHAS, CADA RAINHA PERTENCE A UMA COLUNA NO QUAL O VALOR PRESENTE REPRESENTA A LINHA EM QUE ELA ESTA POSICIONADA
    int ConflictQueen, aux;          //VARIAVEL PARA CONTROLE DE QUANTIDADES DE RAINHAS EM CONFLITO
    Populacao populacao[NUMPOP];
    srand(time(NULL));

    //FOR USADO PARA INICIAR AS POPULACOES, COLOCANDO AS RAINHAS DE FORMA ALEATORIA
    for(int i = 0; i < NUMPOP; i++){
        for(int j = 0; j < NUMQUEEN; j++)
            populacao[i].QueenList[j] = rand()%NUMQUEEN;
        populacao[i].ConflictQueen = verificQueen(populacao[i].QueenList);
    }

    //CHAMADA DA FUNCAO
    int interacoes = solution(QueenList, populacao);
    for(int i = 0; i < NUMQUEEN; i++)
        printf("%d ", QueenList[i]);
    printf("\nNumero de rainhas em conflito: %d\nNumero de Interacoes: %d\n", verificQueen(QueenList), interacoes);

    return 0;
}

int shattering(Populacao populacao[NUMPOP]){
    //PRE: CONJUNTO DE POPULACAO
    //POS: POSICAO SELECIONADA
    int i, aux = 0, selection;
    int auxVet[NUMPOP];

    //AUX E USADO PARA AMAZENAR O TOTAL DE RAINHAS EM CONFLITO
    for(i = 0; i < NUMPOP; i++){
        aux += populacao[i].ConflictQueen;
    }
    //OPERACAO UTILIZADA PARA ESCALAR O PESO DAS RAINHAS EM CONFLITO
    auxVet[0] = (aux - populacao[0].ConflictQueen) ;
    for(i = 1; i < NUMPOP; i++){
        auxVet[i] = auxVet[i-1] + (aux - populacao[i].ConflictQueen);
    }
    aux = auxVet[NUMPOP - 1];
    selection = rand()%aux;

    for(int i = 0; i < NUMPOP; i++){
        if(selection < auxVet[i])
            return i;
    }

}

int solution(int QueenList[NUMQUEEN], Populacao populacao[NUMPOP]){
    //PRE: ARRAY AONDE SERA ARMAZENADO A SOLUCAO E UM CONJUNTO DE POPULACOES
    //POS: SOLUCAO E ARMAZENADA EM QUEENLIST E RETORNA O NUMERO DE INTERACOES
    Populacao populacaoAux[NUMPOP], newPopulacao[NUMPOP];
    int aux, random, mutation = 10, count = 0;

    while(1){
        count++;
        for(int i = 0; i < NUMPOP; i++){
            aux = shattering(populacao);
            memcpy(populacaoAux[i].QueenList, populacao[i].QueenList, sizeof(int)*NUMQUEEN);
            populacaoAux[i].ConflictQueen = populacao[aux].ConflictQueen;
        }

        //CROSSOVER
        for(int i = 0; i < NUMPOP; i++){
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
        for(int i = 0; i < NUMPOP; i++){
            aux = rand()%mutation;
            if(aux == 0){
                mutation = 10;
                aux = rand()%NUMQUEEN;
                random = rand()%NUMQUEEN;
                newPopulacao[i].QueenList[aux] = random;
            }
        }

        //ATUALIZA STATUS DA POPULACAO
        for(int i = 0; i < NUMPOP; i++){
            aux = shattering(populacao);
            memcpy(populacao[i].QueenList, newPopulacao[i].QueenList, sizeof(int)*NUMQUEEN);
            populacao[i].ConflictQueen = verificQueen(populacao[i].QueenList);
        }

        //CASO ENCONTRE UMA SOLUCAO RETORNE
        for(int i = 0; i < NUMPOP; i++)
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
