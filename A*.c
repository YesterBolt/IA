#include <stdio.h>
#define MAXINT 1000000

int main(){
    FILE *arquivo;
    arquivo = fopen("matriz", "r");
    int grafo[20][20];
    int visitados[20];
    int lista[20];
    int distancia[20] = {366, 374, 380, 253, 329, 244, 241,
    242, 160, 193, 98, 0, 178};

    for(int i = 0; i < 20; i++)
        visitados[i] = 0;


}

