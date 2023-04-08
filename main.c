#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "pilha.h"

#define ERRO_INPUT -2
#define NOT_OPERATOR -1
#define FECHAR_SEM_ABRIR -3
#define ABRIR_SEM_FECHAR -4
#define CARACTER_INVALIDO -5

// le o input e devolve o tamanho dele
// todo tratamento de erro que merda é essa
void le_input(char exp[], int* size) {
    for (int i=0; i < INT_MAX; i++) {
        scanf("%c", &exp[i]);
        if (exp[i] == '\0') {
            *size = i + 1;
        }
    }
}

int precedencia(char value) {
    if (value == '(' || value == ')') {
        return 0;
    } else if ( value == '-' || value == '+') {
        return 1;
    } else {
        return 2;
    }
}


void append_saida(char exp[], int* index, char value) {
    exp[*index] = value;
    *index++;
}

void register_error(int* flag, int* message_holder, int message) {
    *flag++;
    *message_holder = message;
}

void print_string(char string[]) { 
    for (int i=0; string[i] == '\0'; i++) {
        printf("%c", string[i]);
    }
    printf("\n");
}

// ainda nao peguei a visão daquele X que ele usa como auxiliar pra botar na string 
// eu acho que é so a variavel que ele usa pra segurar o pop, mas to fudido do cerebelo ja
int main() {
    char expression[INT_MAX];
    int ERROR_FLAG = 0;
    int curr_is = 0;
    char saida[INT_MAX];
    int size_expression;
    int ERROR_MESSAGE;
    char x; // auxiliar char
    le_input(expression, &size_expression);
    Pilha p;
    inicializa_pilha(&p, size_expression);
    for (int i=0; i < size_expression; i++) {
        char curr_char = expression[i];
        switch (curr_char) {
            case '0' ... '9':
                saida[curr_is] = curr_char;
                curr_is++;
            case '(':
                empilha(&p, curr_char);
            case ')':
                while (le_topo(p, &x) != ERRO_PILHA_CHEIA && x != '(') {
                    desempilha(&p, &x); // pilha ta feito pra int
                    append_saida(saida, &curr_is, x);
                }
                if (le_topo(p, &x) == ERRO_PILHA_VAZIA) {
                    register_error(&ERROR_FLAG, &ERROR_MESSAGE, FECHAR_SEM_ABRIR);
                    break;
                } else {
                    desempilha(&p, &x); // descarta o (
                }

            case '*' ... '/': // caracteres incluidos ->  * + , - . /
                if (curr_char == ',' || curr_char == '.') { // tirando os invalidos
                    register_error(&ERROR_FLAG, &ERROR_MESSAGE, CARACTER_INVALIDO);
                    break;
                }
                if (le_topo(p, &x) == ERRO_PILHA_VAZIA || x == '(') {
                    empilha(&p, curr_char);
                } else {
                    while (le_topo(p, &x) != ERRO_PILHA_VAZIA && precedencia(x) > precedencia(curr_char)) {
                        desempliha(&p, &x);
                        append_saida(saida, &curr_is, x);
                    }
                    empilha(&p, curr_char);
                }
                // sei la, meu cerebelo nao me permite mais compreender esse pseudocodigo em cobol
            default:
                register_error(&ERROR_FLAG, &ERROR_MESSAGE, CARACTER_INVALIDO);
        }
    }
    if (!ERROR_FLAG) {
        while (le_topo(p, &x) != ERRO_PILHA_VAZIA && x != '(') { 
                desempilha(&p, &x);
                append_saida(saida, &curr_is, x);
        }
        if (le_topo(p, &x) == ERRO_PILHA_VAZIA) {
            append_saida(saida, &curr_is,  '\0');
            print_string(saida);
            // evaluate_expression()
        } else {
            register_error(&ERROR_FLAG, &ERROR_MESSAGE, ABRIR_SEM_FECHAR);
        }
    
    } else if (ERROR_FLAG) {
        switch (ERROR_MESSAGE) {
            case CARACTER_INVALIDO:
                printf("ERRO: caracter invalido!");
            case FECHAR_SEM_ABRIR:
                printf("ERRO: ')' sem '('!");
            case ABRIR_SEM_FECHAR:
                printf("ERRO: '(' nao foi fechado!");
        }
    }
}
