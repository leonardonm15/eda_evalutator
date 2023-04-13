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
#define OPERADOR_INVALIDO -6


char expression[1000];
char saida[1000];
Pilha p;

int solve(){
    int resultado = 0;
    for(int i = 0; i < strlen(saida); i++){
        char atual = saida[i];
        if (atual >= '0' && atual <= '9') {
            int num = atual - '0';
            empilha(&p, num);
        } else{
            int aux = desempilha(&p);
            int aux2 = desempilha(&p);
            switch(atual){
                case '+':
                    resultado = aux + aux2;
                    break;
                case '-':
                    resultado = aux - aux2;
                    break;
                case '*':
                    resultado = aux * aux2;
                    break;
                case '/':
                    resultado = aux / aux2;
                    break;
                case '^':
                    resultado = aux ^ aux2;
                    break;
                default:
                    printf("OPERADOR INVALIDO\n");
                    return OPERADOR_INVALIDO;
            }
            empilha(&p, resultado);
        }

    }
    return resultado;
}

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

int transforma() {
    char atual, aux;
    int j = 0;

    for (int i = 0; i < strlen(expression); i++) {
        atual = expression[i];
        switch (atual) {
            case '(':
                empilha(&p, atual);
                break;
            case ')':
                while (le_topo(p) != '('){
                    if(!pilha_vazia(p)){
                        return FECHAR_SEM_ABRIR;
                    }
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
            case '0' ... '9':
                saida[j++] = atual;
                break;
            default:
                return CARACTER_INVALIDO;
        }
    }

    while (!pilha_vazia(p)) {
        saida[j++] = desempilha(&p);
    }
    saida[++j] = '\0'; // termina a string com o caractere nulo
    return 1;
}


void printa(){
    int i = 0;
    while(saida[i]){
        printf("%c", saida[i++]);
    }
    printf("\n");
}


int main() {
    int size_expression;
    printf("qual a expressao?\n");
    
    //le_input(expression, &size_expression);
    fgets(expression, 1000, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // remove the newline character
    if(strlen(expression) == 0){
        printf("ERRO DE INPUT\n");
        return ERRO_INPUT;
    } 
    inicializa_pilha(&p, strlen(expression));
    int x = transforma();
    if(x == 1){
        printf("a equacao posfixada fica dessa forma:\n");
        printa();
        int resultado = solve();
        printf("o resultado e %d\n", resultado);
    } else {
        switch(x){
            case CARACTER_INVALIDO:
                printf("CARACTER INVALIDO!\n");
                break;
            case FECHAR_SEM_ABRIR:
                printf("FECHOU PARENTESES SEM ABRIR\n");
        } 
    }
}

