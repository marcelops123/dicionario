#include "dicionario.h" //é um arquivo de cabeçalho personalizado
#include <ctype.h> // contém funções para manipulação de caracteres.

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
//Para encontrar o menor valor entre três números

tNO *texto_entrada, *texto_saida; //ponteiros para uma estrutura
size_t cont = 0;
size_t i = 0;
extern char vet[275502][30]; // indica que a definição da variável vet é externa

void copiaString(char *Palavra, char *novaPalavra) { //Essa função é responsável por copiar
    char *pAux;                                     //uma string para outra, removendo \n

    strcpy(novaPalavra, Palavra);
    pAux = strchr(novaPalavra, '\n');
    if (pAux)
        *pAux = '\0';
}

void correcaoLinha(char *linha, FILE *arqvSaida, char *opc[])
{//Essa função realiza a correção ortográfica em uma linha de texto
    if (linha[0] == '\n')
    {
        fprintf(arqvSaida, "%s", linha);
        return;
    } 

    char *palavra, auxPalavra[40];
    int menor, retLevn = 0;
    char sugestao[40];
    memset(sugestao, '\0', 40);//preeche

    palavra = strtok(linha, " "); //usado p/ dividir a linha em palavras
    copiaString(palavra, auxPalavra);
    printf("%s\n", auxPalavra);

    while (palavra) //percorre todas as palavras da linha
    {
        if ((strlen(auxPalavra)) > 1)
        {
            if (busca_binaria(vet, auxPalavra, 275502))//Verifica se a palavra atual está presente no dicionário, chamando a função buscaBinaria
            {
                fprintf(arqvSaida, "%s ", palavra);
            }
            else
            {
                if (strcmp(opc[3], "1") == 0)
                {
                    menor = levenshtein (vet[0], auxPalavra);
                    for (int j = 0; j < 275502; j++)
                    {
                        if (((strlen(vet[j]) - strlen(auxPalavra)) < 4) && (strlen(auxPalavra) >= 3))
                        { // Filtragem de quantidade de letras
                            retLevn = levenshtein (vet[j], auxPalavra);
                            if (retLevn < menor)
                            {
                                menor = retLevn;
                                strcpy(sugestao, vet[j]);
                            }
                        }
                    }
                    if (sugestao[0] != '\0') // Caso exista alguma palavra correspondente no dicionário
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



int busca_binaria(char lista[][30], char *chave, unsigned int tamanhoDaLista)
{//Essa função procura um elemento específico em uma lista ordenada.
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

int levenshtein (char *s1, char *s2)//é usado para calcular a distância entre duas strings.Fazendo o mínimo de operações 
{// para transformar uma string na outra
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
