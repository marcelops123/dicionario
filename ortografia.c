#include "dicionario.h"
#include "dicionario.c"

extern tNO *texto_entrada, *texto_saida;
extern size_t cont;
FILE *arqvSaida;
char vet[275502][30];

int main(int argc, char *argv[])
{
    FILE *arqv;

    arqv = fopen("C:/Users/Marcelin/Documents/trabalho-pc2/palavras.txt", "r");
    // Aqui irá abrir o dicionario.txt

    if (!arqv)
    {
        perror("Erro ao abrir o arquivo!");
        exit(1);
    }
    // Verifica se ocorreu algum erro na leitura

    char tmp;
    char linha[1000];
    unsigned int i = 0;

    while (!feof(arqv))
        fscanf(arqv, "%s", vet[i++]);

    fclose(arqv);

    // Irá percorrer todo o arquivo.txt e armazenar na variável vet

    arqv = fopen(argv[1], "r");

    // Abre o arquivo em modo de leitura

    if (!arqv)
    {
        perror("Erro ao abrir o arquivo!");
        exit(1);
    }

    // Retorna mensagem de erro caso ocorra falha ao abrir o arquivo

    arqvSaida = fopen(argv[2], "w+");

    // Irá criar o arquivo de saída, no caso ele irá receber como segundo parâmetro da entrada do programa

    if (!arqvSaida)
    {
        perror("Erro ao criar/abrir arquivo de saída!");
        exit(1);
    }

    // Retorna mensagem de erro caso ocorra falha ao abrir o arquivo

    i = 0;
    // Inicia contador = 0

    while (!feof(arqv))
    {
        tmp = fgetc(arqv);
        while (!feof(arqv) && tmp != '\n')
        {
            if (tmp != 44 && tmp != 34 && tmp != 39 && tmp != 46) // 44 = vírgula : 34 = aspas duplas, 39 = apóstrofo, 46 = ponto final
                linha[i++] = tmp;

            tmp = fgetc(arqv);
        }
        linha[i] = '\n';
        i = 0;

        correcaoLinha(linha, arqvSaida, argv);
        memset(linha, '\0', 1000);
    }
    /*
     Nesse processo ele irá verificar se no final da linha possui vírgula, aspas duplas, apóstrofo ou ponto final.
    // Irá quebrar a linha e copiar para a próxima linha dentro da função memset
    */
    return 0;
}