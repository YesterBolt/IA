#include <stdio.h>
#include <stdlib.h>

#define MAXINT 1000000
#define NUMQUEEN 4

int verificQueen(int QueenList[NUMQUEEN]); //FUNCAO RESPONSAVEL POR VERIFICAR SE AS RAINHAS ESTAO EM CONFLITOS
int nextStage(int QueenList[NUMQUEEN], int coluna); //FUNCAO RESPONSAVEL POR ORGANIZAR AS RAINHAS

int main(){
    int QueenList[NUMQUEEN];    //POSICAO DAS RAINHAS, CADA RAINHA PERTENCE A UMA COLUNA NO QUAL O VALOR PRESENTE REPRESENTA A LINHA EM QUE ELA ESTA POSICIONADA
    int ConflictQueen;          //VARIAVEL PARA CONTROLE DE QUANTIDADES DE RAINHAS EM CONFLITO

    //FOR USADO PARA INICIAR AS RAINHAS COLOCANDO TODAS NA MESMA LINHA, NO CASO LINHA 0
    for(int i = 0; i < NUMQUEEN; i++)
        QueenList[i] = 0;

    //ORGANIZACAO DAS RAINHAS
    nextStage(QueenList, 0);

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

int nextStage(int QueenList[NUMQUEEN], int coluna){
    //PRE: ARRAY DE RAINHAS E COLUNA NA QUAL A RAINHA DEVE MOVIMENTAR
    //POS: 1 SE FOR POSSIVEL ORDENAR, 0 SE NAO POREM AS RAINHAS IRAM ESTAR NA MELHOR POSICAO POSSIVEL

    //CONDICAO DE PARADA
    if(coluna >= NUMQUEEN){
        return 1;
    }
    int auxList[NUMQUEEN], possVisited[NUMQUEEN];   //AUXLIST E USADO PARA PODER VERIFICAR A MELHOR MOVIMENTACAO
    int lessValue = MAXINT;                         //POSSVISITED E USADO PARA MARCAR SE A POSICAO JA FOI TESTADA, EVITANDO REPETICAO
    int possQueen, ConflictQueen, aux;
    //INICIACAO DO VETOR DE POSICOES VISITADAS
    for(int i = 0; i < NUMQUEEN; i++){
        possVisited[i] = 0;
    }
    //COPIA QUEENLIST EM AUXLIST PARA VERIFICAR A MELHOR POSICAO
    memcpy(auxList, QueenList, sizeof(int)*NUMQUEEN);

    for(int i = 0; i < NUMQUEEN; i++){
        //PROCURA A MELHOR POSICAO
        for(int j = 0; j < NUMQUEEN; j++){
            auxList[coluna] = j;
            ConflictQueen = verificQueen(auxList);
            aux = ConflictQueen - 1;
            //CASO MELHOR POSICAO E AINDA NAO TENHA SIDO TESTADA, MARCA COMO MELHOR POSICAO
            if(aux < lessValue && possVisited[j] == 0){
                lessValue = aux;
                possQueen = j;
                possVisited[j] = 1;
            }
        }
        //ATUALIZA A QUEENLIST E FAZ A CHAMADA PARA A PROXIMA COLUNA
        QueenList[coluna] = possQueen;
        if(nextStage(QueenList, coluna + 1))
            //SE ENCONTRA UMA SOLUCAO RETORNA 1
            return 1;
        //CASO NAO ENCONTRE UMA SOLUCAO O STATUS E RECUPERADO E SE TENTA UMA NOVA POSICAO NA COLUNA
        memcpy(auxList, QueenList, sizeof(int)*NUMQUEEN);
        lessValue = MAXINT;
    }
    return 0;
}
