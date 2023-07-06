#include "dicionario.h"
#include <ctype.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

tNO *inicio_texto, *final_texto;
size_t cont = 0;
size_t i = 0;
extern char vet[275502][30];

void copiaString(char *Palavra, char *novaPalavra) {
    char *pAux;

    strcpy(novaPalavra, Palavra);
    pAux = strchr(novaPalavra, '\n');
    if (pAux)
        *pAux = '\0';
}

void tratarLinha(char *linha, FILE *arqvSaida, char *opc[])
{
    if (linha[0] == '\n')
    {
        fprintf(arqvSaida, "%s", linha);
        return;
    }
    // Irá verificar se a linha é um \n (final da linha) e adicionará o \n no arquivo de saída fazendo com que a linha seja quebrada 

    char *palavra, auxPalavra[40];
    int menor, retLevn = 0;
    char sugestao[40];
    memset(sugestao, '\0', 40);

    palavra = strtok(linha, " ");
    copiaString(palavra, auxPalavra);
    printf("%s\n", auxPalavra);

    while (palavra)
    {
        if ((strlen(auxPalavra)) > 1)
        {
            if (BinarySearch(vet, auxPalavra, 275502))
            {
                fprintf(arqvSaida, "%s ", palavra);
            }
            else
            {
                if (strcmp(opc[3], "1") == 0)
                {
                    menor = liechtenstein(vet[0], auxPalavra);
                    for (int j = 0; j < 275502; j++)
                    {
                        if (((strlen(vet[j]) - strlen(auxPalavra)) < 4) && (strlen(auxPalavra) >= 3))
                        { // Filtragem de quantidade de letras
                            retLevn = liechtenstein(vet[j], auxPalavra);
                            if (retLevn < menor)
                            {
                                menor = retLevn;
                                strcpy(sugestao, vet[j]);
                            }
                        }
                    }
                    if (sugestao[0] != '\0')
                        fprintf(arqvSaida, "[%s(%s)] ", palavra, sugestao);
                    else
                        fprintf(arqvSaida, "%s ", palavra);
                }
                else if (strcmp(opc[3], "0") == 0)
                    fprintf(arqvSaida, "[%s]", palavra);
            }
        }

        palavra = strtok(NULL, " ");
        if (palavra)
            copiaString(palavra, auxPalavra);
    }
}



int BinarySearch(char lista[][30], char *chave, unsigned int tamanhoDaLista)
{
    int inf = 0;                  // limite inferior (o primeiro índice de vetor em C é zero)
    int sup = tamanhoDaLista - 1; // limite superior (termina em um número a menos. 0 a 9 são 10 números)
    int meio;
    while (inf <= sup)
    {
        meio = (inf + sup) / 2;
        if ((strcmp(chave, lista[meio])) == 0)
            return 1;
        if ((strcmp(chave, lista[meio])) < 0)
            sup = meio - 1;
        if ((strcmp(chave, lista[meio])) > 0)
            inf = meio + 1;
    }
    return 0; // não encontrado
}

int liechtenstein(char *s1, char *s2)
{
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;

    s1len = strlen(s1);
    s2len = strlen(s2);

    unsigned int column[s1len + 1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++)
    {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++)
        {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y - 1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }

    return column[s1len];
}
