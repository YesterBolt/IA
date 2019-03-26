#include <stdio.h>
#include <stdint.h>

void dfs(int grafo[20][20], int visitados[20], int vertice);

int main(){
    FILE *arquivo;
    arquivo = fopen("matriz.txt", "r");
    int grafo[20][20];
    int visitados[20];
    int v1, v2, peso;

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++)
            grafo[i][j] = -1;
    }

    while(fscanf(arquivo, "%d %d %d", &v1, &v2, &peso) != EOF){
        grafo[v1][v2] = peso;
        grafo[v2][v1] = peso;
    }

    for(int i = 0; i < 20; i++){
        visitados[i] = 0;
    }

    dfs(grafo, visitados, 0);
}

void dfs(int grafo[20][20], int visitados[20], int vertice){
    visitados[vertice] = 1;
    if(vertice == 11) return;

    for(int i = 0; i < 20; i++){
        if(visitados[grafo[vertice][i]] == -1){
            dfs(grafo, visitados, i);
        }
    }
}
