#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

#define MAX_PILHA 50

void inicializa_pilha( Pilha *p, int c ){
    p->topo = -1;
    p->dados = malloc( sizeof( int ) * c );
    p->capacidade = c;
}

int pilha_vazia (Pilha p){
    return p.topo == -1;
}

int pilha_cheia (Pilha p){
    return p.topo == MAX_PILHA -1;
}

int empilha (Pilha *p, int v){
    if(pilha_cheia(*p)){
        return ERRO_PILHA_CHEIA;
    }
    p-> topo++;
    p-> dados[p->topo] = v;
    return 1;
}

int desempilha(Pilha *p, int *info){
    if(pilha_vazia(*p)){
        return ERRO_PILHA_VAZIA;
    }
    *info = p->dados[p->topo];
    p->topo--;
    return 1;
}

int le_topo (Pilha p, int *info){
    if(pilha_vazia(p)){
        return ERRO_PILHA_VAZIA;
    }
    *info = p.dados[p.topo];
    return -1;
}

void mostra_pilha(Pilha p){
    if(pilha_vazia(p)){
        printf("pilha vazia \n");
    } else {
        printf("dados da pilha\n");
        for(int i = 0; i <= p.topo; i++){
            printf("%d ", p.dados[i]);
        }
        printf("\n");
    }

}

void desaloca_pilha( Pilha *p ){
    free( p->dados );
}

