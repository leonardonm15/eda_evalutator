#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "pilha.h"
#include <string.h>

#define ERRO_INPUT -2
#define NOT_OPERATOR -1
#define FECHAR_SEM_ABRIR -3
#define ABRIR_SEM_FECHAR -4
#define CARACTER_INVALIDO -5



char expression[INT_MAX];
char saida[INT_MAX];
Pilha p;


int precedencia(char value) {
    switch(value){
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void transforma() {
    char atual, aux;
    int j = 0;

    for (int i = 0; i < strlen(expression); i++) {
        atual = expression[i];
        switch (atual) {
            case '(':
                empilha(&p, atual);
                break;
            case ')':
                while (!pilha_vazia(p) && le_topo(p) != '('){
                    saida[j++] = desempilha(&p);
                    desempilha(&p); 
                }
                break;
            case '^':
            case '*' ... '/': // caracteres incluidos ->  * + , - . / */
                while (!pilha_vazia(p) && precedencia(le_topo(p)) >= precedencia(atual)) {
                    saida[j++] = desempilha(&p);
                }
                empilha(&p, atual);
                break;
            default:
                saida[j++] = atual;
                break;
        }
    }

    while (!pilha_vazia(p)) {
        saida[j++] = desempilha(&p);
    }
    saida[j] = '\0'; // termina a string com o caractere nulo
}


void printa(){
    int i = 0;

    while(saida[i]){
        printf("%c", saida[i++]);
    }
}


int main() {
    int size_expression;
    printf("qual a expressao?\n");
    
    //le_input(expression, &size_expression);
    fgets(expression, INT_MAX, stdin);
    inicializa_pilha(&p, size_expression); 
    transforma();
    printa();

}


