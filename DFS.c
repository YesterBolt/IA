#include <stdio.h>
#include <stdint.h>

int listaVazia(int lista[20]);
int removeLista(int lista[20]);
void insereFila(int lista[20], int vertice);

int main(){
    FILE *arquivo;
    arquivo = fopen("matriz", "r");
    int grafo[20][20];
    int visitados[20];
    int lista[20];
    int aux, aux2;
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
        lista[i] = -1;
    }
    insereFila(lista, 0);

    while(!listaVazia(lista)){
        aux = removeLista(lista);
        visitados[aux] = 1;
        if(aux == 11)
            break;
        for(int i = 0; i < 20; i++){
            if(grafo[aux][i] != -1 && visitados[i] != 1){
                insereFila(lista, i);
            }
        }
    }

}

int listaVazia(int lista[20]){
    if(lista[0] != -1)
        return 0;
    else return 1;
}

int removeLista(int lista[20]){
    int aux = lista[0];
    for(int i = 0; i < 20; i++)
        lista[i] = lista[i+1];
    lista[19] = -1;
    return aux;
}

void insereFila(int lista[20], int vertice){
    for(int i = 0; i < 20; i++){
        if(lista[i] == -1){
            lista[i] = vertice;
            return;
        }
    }
    return;
}
