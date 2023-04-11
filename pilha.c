#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

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

//alterei o tipo de *info de int para char;
//vo comentar pq nem tamo usando o info, vo retornar o valor excluido caso precise
    int desempilha(Pilha *p /*, char *info */) {
    if(pilha_vazia(*p)){
        return ERRO_PILHA_VAZIA;
    }
    //*info = p->dados[p->topo];
    //p->topo--;
    return p->dados[p->topo--];
    //sim isso funciona kkkk
}

//vo retornar o topo invez de salvar no *info
int le_topo (Pilha p/*, int *info */){
    if(pilha_vazia(p)){
        return ERRO_PILHA_VAZIA;
    }
     //*info = p.dados[p.topo];
     return p.dados[p.topo];
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

void desaloca_pilha(Pilha *p ){
	free( p->dados );
}


