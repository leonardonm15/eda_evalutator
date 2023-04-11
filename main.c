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


// le o input e devolve o tamanho dele
// todo tratamento de erro que merda é essa
/*
void le_input(char exp[], int* size) {
    for (int i=0; i < INT_MAX; i++) {
        scanf("%c", &exp[i]);
        if (exp[i] == '\0') {
            *size = i + 1;
        }
    }
}
*/
//vo usar essa mesma e so colocar a pot, vou mover la pra baixo so pra separar oq eu fiz
/*
int precedencia(char value) {
    if (value == '(' || value == ')') {
        return 0;
    } else if ( value == '-' || value == '+') {
        return 1;
    } else {
        return 2;
    }
}
*/

void append_saida(char exp[], int* index, char value) {
    exp[*index] = value;
    *index++;
}

void register_error(int* flag, int* message_holder, int message) {
    *flag++;
    *message_holder = message;
}

void print_string(char string[]) { 
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/' || string[i] == '^') {
            printf("%c", string[i]);
        } else {
            printf("%d", string[i]);
        }
    }
    printf("\n");
}

// ainda nao peguei a visão daquele X que ele usa como auxiliar pra botar na string 
// eu acho que é so a variavel que ele usa pra segurar o pop, mas to fudido do cerebelo ja

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
    char atual, aux, valor_desempilhado;
    int j = 0;

    for (int i = 0; i < strlen(expression); i++) {
        atual = expression[i];
        switch (atual) {
            case '(':
                empilha(&p, atual);
                break;
            case ')':
                while ((valor_desempilhado = desempilha(&p, &aux)) != '(') {
                    saida[j++] = valor_desempilhado;
                }
                break;
            case '*' ... '/': // caracteres incluidos ->  * + , - . / */
                while (!pilha_vazia(p) && precedencia(ultimo_add(&p, &aux)) >= precedencia(atual)) {
                    saida[j++] = desempilha(&p, &aux);
                }
                empilha(&p, atual);
                break;
            default:
                saida[j++] = atual;
                break;
        }
    }

    while (!pilha_vazia(p)) {
        saida[j++] = desempilha(&p, &aux);
    }

    saida[j] = '\0'; // termina a string com o caractere nulo
}


void printa(){
    int i = 0;

    while(saida[i]){
        printf("%c", saida[i++]);
    }
    printf("\n");
}


int main() {
    int ERROR_FLAG = 0;
    int curr_is = 0;
    int size_expression;
    int ERROR_MESSAGE;
    char x; // auxiliar char

    printf("qual a expressao?\n");
    
    //le_input(expression, &size_expression);
    fgets(expression, INT_MAX, stdin);
    //da p usar o fgets e passar o max do vetor so

    //deixei aq so p te mostrar dps, vou tentar passar p uma func separada

    inicializa_pilha(&p, size_expression); 
    transforma();
    printa();

    /* for (int i=0; i < size_expression; i++) { */
    /*     char curr_char = expression[i]; */
    /*     switch (curr_char) { */
    /*         case '0' ... '9': */
    /*             saida[curr_is] = curr_char; */
    /*             curr_is++; */
    /*         case '(': */
    /*             empilha(&p, curr_char); */
    /*         case ')': */
    /*             while (le_topo(p, &x) != ERRO_PILHA_CHEIA && x != '(') { */
    /*                 desempilha(&p, &x); // pilha ta feito pra int */
    /*                 append_saida(saida, &curr_is, x); */
    /*             } */
    /*             if (le_topo(p, &x) == ERRO_PILHA_VAZIA) { */
    /*                 register_error(&ERROR_FLAG, &ERROR_MESSAGE, FECHAR_SEM_ABRIR); */
    /*                 break; */
    /*             } else { */
    /*                 desempilha(&p, &x); // descarta o ( */
    /*             } */

    /*         case '*' ... '/': // caracteres incluidos ->  * + , - . / */
    /*             if (curr_char == ',' || curr_char == '.') { // tirando os invalidos */
    /*                 register_error(&ERROR_FLAG, &ERROR_MESSAGE, CARACTER_INVALIDO); */
    /*                 break; */
    /*             } */
    /*             if (le_topo(p, &x) == ERRO_PILHA_VAZIA || x == '(') { */
    /*                 empilha(&p, curr_char); */
    /*             } else { */
    /*                 while (le_topo(p, &x) != ERRO_PILHA_VAZIA && precedencia(x) > precedencia(curr_char)) { */
    /*                     desempliha(&p, &x); */
    /*                     append_saida(saida, &curr_is, x); */
    /*                 } */
    /*                 empilha(&p, curr_char); */
    /*             } */
    /*             // sei la, meu cerebelo nao me permite mais compreender esse pseudocodigo em cobol */
    /*         default: */
    /*             register_error(&ERROR_FLAG, &ERROR_MESSAGE, CARACTER_INVALIDO); */
    /*     } */
    /* } */
    /* if (!ERROR_FLAG) { */
    /*     while (le_topo(p, &x) != ERRO_PILHA_VAZIA && x != '(') { */ 
    /*             desempilha(&p, &x); */
    /*             append_saida(saida, &curr_is, x); */
    /*     } */
    /*     if (le_topo(p, &x) == ERRO_PILHA_VAZIA) { */
    /*         append_saida(saida, &curr_is,  '\0'); */
    /*         print_string(saida); */
    /*         // evaluate_expression() */
    /*     } else { */
    /*         register_error(&ERROR_FLAG, &ERROR_MESSAGE, ABRIR_SEM_FECHAR); */
    /*     } */
    
    /* } else if (ERROR_FLAG) { */
    /*     switch (ERROR_MESSAGE) { */
    /*         case CARACTER_INVALIDO: */
    /*             printf("ERRO: caracter invalido!"); */
    /*         case FECHAR_SEM_ABRIR: */
    /*             printf("ERRO: ')' sem '('!"); */
    /*         case ABRIR_SEM_FECHAR: */
    /*             printf("ERRO: '(' nao foi fechado!"); */
    /*     } */
    /* } */
}

