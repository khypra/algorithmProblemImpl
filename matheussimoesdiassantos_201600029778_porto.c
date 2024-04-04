#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct container
{
    char codigo[12];
    char cnpj[18];
    int peso;
} Container;

typedef struct saida
{
    char codigo[12];
    char diffCnpj[40];
    int peso;
    int percentPeso;
    int order;

} Saida;

int compare(const void *a, const void *b)
{

    Container *dataA = (Container *)a;
    Container *dataB = (Container *)b;
    int i = 0;
    for (i = 0; dataA->codigo[i] == dataB->codigo[i]; i++)
    {
        if (dataA->codigo[i] == '\0')
            return 0;
    }
    return dataA->codigo[i] - dataB->codigo[i];
}

void MergeC(Container *lista, int inicio, int metade, int fim)
{
    int i, j, k;
    int n1 = metade - inicio + 1;
    int n2 = fim - metade;

    Container esquerda[n1];
    Container direita[n2];

    for (i = 0; i < n1; i++)
        esquerda[i] = lista[inicio + i];
    for (j = 0; j < n2; j++)
        direita[j] = lista[metade + 1 + j];

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2)
    {
        int comp = compare(esquerda[i].codigo, direita[j].codigo);
        if (comp < 0)
        {
            lista[k] = esquerda[i];
            i++;
        }
        else if (comp > 0)
        {
            lista[k] = direita[j];
            j++;
        }
        else
        {
            lista[k] = esquerda[i];
            i++;
        }
        k++;
    }

    while (i < n1)
    {
        lista[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        lista[k] = direita[j];
        j++;
        k++;
    }
}

void MergeSortC(Container *lista, int inicio, int fim)
{
    if (inicio < fim)
    {
        int metade = inicio + (fim - inicio) / 2;

        MergeSortC(lista, inicio, metade);
        MergeSortC(lista, metade + 1, fim);

        MergeC(lista, inicio, metade, fim);
    }
}

void Merge(Saida *lista, int inicio, int metade, int fim)
{
    int i, j, k;
    int n1 = metade - inicio + 1;
    int n2 = fim - metade;

    Saida esquerda[n1];
    Saida direita[n2];

    for (i = 0; i < n1; i++)
        esquerda[i] = lista[inicio + i];
    for (j = 0; j < n2; j++)
        direita[j] = lista[metade + 1 + j];

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2)
    {
        if (strlen(esquerda[i].diffCnpj) > 0 && strlen(direita[j].diffCnpj) > 0)
        {
            if (esquerda[i].order < direita[j].order)
            {
                lista[k] = esquerda[i];
                i++;
            }
            else
            {
                lista[k] = direita[j];
                j++;
            }
        }
        else if (strlen(esquerda[i].diffCnpj) > 0)
        {
            lista[k] = esquerda[i];
            i++;
        }
        else if (strlen(direita[j].diffCnpj) > 0)
        {
            lista[k] = direita[j];
            j++;
        }
        else if (esquerda[i].percentPeso == direita[j].percentPeso)
        {
            if (esquerda[i].order < direita[j].order)
            {
                lista[k] = esquerda[i];
                i++;
            }
            else
            {
                lista[k] = direita[j];
                j++;
            }
        }
        else if (esquerda[i].percentPeso > direita[j].percentPeso)
        {
            lista[k] = esquerda[i];
            i++;
        }
        else if (esquerda[i].percentPeso < direita[j].percentPeso)
        {
            lista[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        lista[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        lista[k] = direita[j];
        j++;
        k++;
    }
}

void MergeSort(Saida *lista, int inicio, int fim)
{
    if (inicio < fim)
    {
        int metade = inicio + (fim - inicio) / 2;

        MergeSort(lista, inicio, metade);
        MergeSort(lista, metade + 1, fim);

        Merge(lista, inicio, metade, fim);
    }
}

int binarySearch(Container *a, int tam, Container *val)
{
    int inicio = 0;
    int mid = 0;
    int fim = tam - 1;
    while (inicio <= fim)
    {
        mid = (inicio + fim) / 2;

        int comp = compare(&a[mid], val);
        if (comp == 0)
            return mid;

        if (comp < 0)
            inicio = mid + 1;
        else
            fim = mid;

        if (inicio == fim && inicio == mid)
            return -1;
    }
}

int main(int argc, char *argv[])
{
    fflush(stdin);
    if (argc < 3)
    {
        printf("Falta de argumentos na execucao. %d\n", argc);
        return -1;
    }
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");

    if (entrada == NULL || saida == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    int n1 = 0, n2 = 0;

    Container *lista;
    Container selecionado;
    Saida *resposta;
    int indexResposta = 0;

    fscanf(entrada, "%d", &n1);

    // scanf("%d", &n1);
    lista = (Container *)calloc(n1, sizeof(Container));

    for (int i = 0; i < n1; i++)
    {
        fscanf(entrada, "%s %s %d", &lista[i].codigo, &lista[i].cnpj, &lista[i].peso);
        // scanf("%s %s %d", &lista[i].codigo, &lista[i].cnpj, &lista[i].peso);
    }

    MergeSortC(lista, 0, n1 - 1);

    // scanf("%d", &n2);
    fscanf(entrada, "%d", &n2);

    resposta = (Saida *)calloc(n2, sizeof(Saida));

    for (int i = 0; i < n2; i++)
    {
        int k = 0;
        // scanf("%s %s %d", &selecionado.codigo, &selecionado.cnpj, &selecionado.peso);
        fscanf(entrada, "%s %s %d", &selecionado.codigo, &selecionado.cnpj, &selecionado.peso);

        k = binarySearch(lista, n1, &selecionado);
        if (compare(lista[k].cnpj, selecionado.cnpj) != 0)
        {
            strcpy(resposta[indexResposta].codigo, lista[k].codigo);
            strcat(resposta[indexResposta].diffCnpj, lista[k].cnpj);
            strcat(resposta[indexResposta].diffCnpj, "<->");
            strcat(resposta[indexResposta].diffCnpj, selecionado.cnpj);
            resposta[indexResposta].peso = 0;
            resposta[indexResposta].percentPeso = 0;
            resposta[indexResposta].order = indexResposta;
            indexResposta++;
        }
        else
        {
            int valor = abs(lista[k].peso - selecionado.peso);
            float percentil = (valor * 100 / (float)(lista[k].peso));

            if (round(percentil) > 10)
            {
                strcpy(resposta[indexResposta].codigo, lista[k].codigo);
                resposta[indexResposta].peso = valor;
                resposta[indexResposta].percentPeso = round(percentil);
                resposta[indexResposta].order = indexResposta;
                indexResposta++;
            }
        }
    }

    fclose(entrada);

    MergeSort(resposta, 0, indexResposta);

    for (int i = 0; i < indexResposta; i++)
    {
        if (resposta[i].percentPeso == 0)
        {
            // printf("%s: %s\n", resposta[i].codigo, resposta[i].diffCnpj);
            fprintf(saida, "%s: %s\n", resposta[i].codigo, resposta[i].diffCnpj);
        }
        else
        {
            // printf("%s: %d (%d%%)\n", resposta[i].codigo, resposta[i].peso, resposta[i].percentPeso);
            fprintf(saida, "%s: %dkg (%d%%)\n", resposta[i].codigo, resposta[i].peso, resposta[i].percentPeso);
        }
    }

    fclose(saida);

    return 0;
}