#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "pilha.h"

#define ERRO_INPUT -2
#define NOT_OPERATOR -1

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

// ainda nao peguei a visão daquele X que ele usa como auxiliar pra botar na string 
// eu acho que é so a variavel que ele usa pra segurar o pop, mas to fudido do cerebelo ja
int main() {
    char expression[INT_MAX];
    int erro_flag = 0;
    int curr_is = 0;
    char saida[INT_MAX];
    int size_expression;
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
                // vai popando a pilha ate achar o (
                // se nao achar, da erro
            case '*' ... '/':
                // * + , - . /
                // sei la, meu cerebelo nao me permite mais compreender esse pseudocodigo em cobol
            default:
                printf("ERRO: caracter inválido: %c", curr_char);
                erro_flag = 1;
                break;
        }
    }

    if (!erro_flag) {
        // todo desempilha em x e joga na string
        // if pilha vazia, bota null byte na saida chamada o evaluator pra calcular 
    } else {
        printf("ERRO: '(' nao foi fechado!");
    }
}
