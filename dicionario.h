#ifndef SUM_H
#define SUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO {
    char frase[600];
    struct NO *prox;
} tNO;

//void buscar(char *, tNO *);
int BinarySearch (char lista[][30], char *chave, unsigned int tamanhoDaLista);
int liechtenstein(char *, char *);
void tratarLinha(char *,FILE *,char *arg[]);
void carregar_texto(char);

#endif