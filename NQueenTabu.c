#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINT 1000000
#define NUMQUEEN 4
#define TABU NUMQUEEN/2

//REPRESENTACAO E COMPOSTA POR UM VETOR DE N RAINHAS CONTENDO A POSICAO NA LINHA DE CADA RAINHA
//HEURISTICA E A QUANTIDADE DE RAINHAS EM CONFLITOS - 1

int verificQueen(int QueenList[NUMQUEEN]); //FUNCAO RESPONSAVEL POR VERIFICAR SE AS RAINHAS ESTAO EM CONFLITOS
int nextStage(int QueenList[NUMQUEEN], int listMove[TABU]); //FUNCAO RESPONSAVEL POR ORGANIZAR AS RAINHAS
int searchOnList(int list[TABU], int aux); //FUNCAO VERIFICA SE EXISTE UM ELEMENTO NA LISTA, RETURN 1 IF TRUE 0 IF FALSE
void insertOnList(int list[TABU], int number); //FUNCAO RESPONSAVEL POR INSERIR UM NOVO ELEMENTO NA LISTA

int main(){
    int QueenList[NUMQUEEN], listTabu[TABU];    //POSICAO DAS RAINHAS, CADA RAINHA PERTENCE A UMA COLUNA NO QUAL O VALOR PRESENTE REPRESENTA A LINHA EM QUE ELA ESTA POSICIONADA
    int ConflictQueen;          //VARIAVEL PARA CONTROLE DE QUANTIDADES DE RAINHAS EM CONFLITO

    //FOR USADO PARA INICIAR AS RAINHAS COLOCANDO TODAS NA MESMA LINHA, NO CASO LINHA 0
    for(int i = 0; i < NUMQUEEN; i++)
        QueenList[i] = 0;

    //FOR USADO PARA INICIAR A LISTA DE TABU, -1 E UMA INDICACAO QUE NAO HA NADA NA POSICAO
    for(int i = 0; i < TABU; i++)
        listTabu[i] = -1;

    //ORGANIZACAO DAS RAINHAS
    nextStage(QueenList, listTabu);

    //FOR USADO PARA MOSTRAR O STATUS DAS RAINHAS
    for(int i = 0; i < NUMQUEEN; i++){
        printf("%d ", QueenList[i]);
    }
    printf("\n");
    ConflictQueen = verificQueen(QueenList);
    printf("Existem %d rainhas em conflito!\n\n", ConflictQueen);

    return 0;
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

int nextStage(int QueenList[NUMQUEEN], int listTabu[TABU]){
    //PRE: ARRAY DE RAINHAS E COLUNA NA QUAL A RAINHA DEVE MOVIMENTAR
    //POS: 1 SE FOR POSSIVEL ORDENAR, 0 SE NAO POREM AS RAINHAS IRAM ESTAR NA MELHOR POSICAO POSSIVEL

    int auxList[NUMQUEEN];   //AUXLIST E USADO PARA PODER VERIFICAR A MELHOR MOVIMENTACAO
    int lessValue = MAXINT;                         //POSSVISITED E USADO PARA MARCAR SE A POSICAO JA FOI TESTADA, EVITANDO REPETICAO
    int possQueen, possTable, ConflictQueen, aux;

    //COPIA QUEENLIST EM AUXLIST PARA VERIFICAR A MELHOR POSICAO
    memcpy(auxList, QueenList, sizeof(int)*NUMQUEEN);

    for(int i = 0; i < NUMQUEEN; i++){
        //SE A RAINHA JA FOI MOVIDA PREVIAMENTE, NAO A NECESSIDADE DE MOVELA AGORA
        while(searchOnList(listTabu, i))
            i++;
        //PROCURA A MELHOR POSICAO
        for(int j = 0; j < NUMQUEEN; j++){
            auxList[i] = j;
            ConflictQueen = verificQueen(auxList);
            aux = ConflictQueen - 1;
            //CASO MELHOR POSICAO E AINDA NAO TENHA SIDO TESTADA, MARCA COMO MELHOR POSICAO
            if(aux < lessValue && QueenList[i] != j){
                lessValue = aux;
                possQueen = i;
                possTable = j;
            }
        }
    }
    //ATUALIZA O ESTADO DAS RAINHAS
    QueenList[possQueen] = possTable;
    ConflictQueen = verificQueen(QueenList);
    insertOnList(listTabu, possQueen);
    //CONDICAO DE PARADA
    if(ConflictQueen == 0)
        return 1;
    //CHAMADA RECURSIVA
    if(nextStage(QueenList, listTabu))
        //SE ENCONTRA UMA SOLUCAO RETORNA 1
        return 1;
    return 0;
}

int searchOnList(int list[TABU], int aux){
    //PRE: LISTA DE INTEIROS E UM ELEMENTO
    //POS: 1 SE O ELEMENTO ESTA NA LISTA, 0 SE NAO ESTIVER

    for(int i = 0; i < TABU; i++)
        //SE ENCONTRA O VALOR NA LISTA RETORNA 1
        if(list[i] == aux)
            return 1;
    //SE NAO RETORNA 0
    return 0;
}

void insertOnList(int list[TABU], int number){
    //PRE: LISTA DE INTEIROS E UM ELEMENTO
    //POS: O ELEMENTO E INSERIDO NA LISTA, SE A LISTA ESTA CHEIA O ELEMENTO SUBSTITUI O MAIS ANTIGO DA LISTA

    int aux;
    for(int i = 0; i < TABU; i++){
        aux = list[i];
        list[i] = number;
        number = aux;
    }
}
