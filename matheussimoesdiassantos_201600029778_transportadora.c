#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char codigo[13];
    double valor;
    int peso;
    int volume;
} Pacote;

typedef struct
{
    char placa[8];
    int peso;
    int volume;
    Pacote *pacotes;
    int num_pacotes;
} Veiculo;

int main(int argc, char *argv[])
{
    // if (argc < 3)
    // {
    //     printf("Falta de argumentos na execucao. %d\n", argc);
    //     return -1;
    // }
    // FILE *entrada = fopen(argv[1], "r");
    // FILE *saida = fopen(argv[2], "w");
    int n = 0;
    int m = 0;
    scanf("%d", &n);
    Pacote *pacotes = (Pacote *)calloc(n, sizeof(Pacote));

    int itemMapPeso [n][m];
    int itemMapVolume[n][m];
    int itemMapValor[n][m];


    // fclose(entrada);
    // fclose(saida);

    return 0;
}