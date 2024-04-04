#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void troca(int vet[], int x, int y, int *chamadas)
{
    *chamadas += 1;
    int aux = vet[x];
    vet[x] = vet[y];
    vet[y] = aux;
}

void troca2(int *vet, int *vet2, int x, int y)
{
    int aux = vet[x];
    int aux2 = vet2[x];
    vet[x] = vet[y];
    vet2[x] = vet2[y];
    vet[y] = aux;
    vet2[y] = aux2;
}

int med3(int arr[], int inicio, int fim)
{
    int v1, v2, v3;
    int tam = fim - inicio + 1;
    v1 = ((tam) / 4) + inicio;
    v2 = ((tam) / 2) + inicio;
    v3 = ((3 * (tam)) / 4) + inicio;

    if (arr[v1] > arr[v2])
    {
        int aux = v2;
        v2 = v1;
        v1 = aux;
    }
    if (arr[v2] > arr[v3])
    {
        int aux = v2;
        v2 = v3;
        v3 = aux;
    }
    if (arr[v1] > arr[v2])
    {
        int aux = v1;
        v1 = v2;
        v2 = aux;
    }
    if (arr[v2] > arr[v3])
    {
        int aux = v2;
        v2 = v3;
        v3 = aux;
    }

    return v2;
}

int calcPivot(int tipo, int inicio, int fim, int *arr, int *chamadas)
{
    int pivot = 0;
    int x = 0;
    int y = 0;
    int pivotIdx = 0;

    switch (tipo)
    {
    case 0:
        // lomuto padrao
        pivot = arr[fim];
        x = inicio - 1;
        for (y = inicio; y <= fim; y++)
        {
            if (arr[y] < pivot)
            {
                troca(arr, ++x, y, chamadas);
            }
        }
        troca(arr, ++x, fim, chamadas);
        return x;
        break;
    case 1:
        // hoare padrao
        pivot = arr[inicio];
        x = inicio - 1;
        y = fim + 1;
        while (1)
        {
            while (arr[--y] > pivot)
                ;
            while (arr[++x] < pivot)
                ;
            if (x < y)
                troca(arr, x, y, chamadas);
            else
                return y;
        }
        break;
    case 2:
        // lomuto med
        pivotIdx = med3(arr, inicio, fim);
        pivot = arr[pivotIdx];
        troca(arr, fim, pivotIdx, chamadas);
        x = inicio - 1;
        for (y = inicio; y < fim; y++)
        {
            if (arr[y] < pivot)
            {
                troca(arr, ++x, y, chamadas);
            }
        }

        troca(arr, ++x, fim, chamadas);
        return x;
        break;
    case 3:
        // hoare med
        pivotIdx = med3(arr, inicio, fim);
        pivot = arr[pivotIdx];
        troca(arr, inicio, pivotIdx, chamadas);
        x = inicio - 1;
        y = fim + 1;
        while (1)
        {
            while (arr[--y] > pivot)
                ;
            while (arr[++x] < pivot)
                ;
            if (x < y)
            {
                troca(arr, x, y, chamadas);
            }
            else
                return y;
        }
        break;
    case 4:
        // lomuto aleatorio
        pivotIdx = inicio + abs(arr[inicio]) % (fim - inicio + 1);
        pivot = arr[pivotIdx];
        troca(arr, fim, pivotIdx, chamadas);
        x = inicio - 1;
        for (y = inicio; y <= fim; y++)
        {
            if (arr[y] < pivot)
            {
                troca(arr, ++x, y, chamadas);
            }
        }
        troca(arr, ++x, fim, chamadas);
        return x;
        break;
    case 5:
        // hoare aleatorio
        pivotIdx = inicio + abs(arr[inicio]) % (fim - inicio + 1);
        pivot = arr[pivotIdx];
        troca(arr, inicio, pivotIdx, chamadas);
        x = inicio - 1;
        y = fim + 1;
        while (1)
        {
            while (arr[--y] > pivot)
                ;
            while (arr[++x] < pivot)
                ;
            if (x < y)
                troca(arr, x, y, chamadas);
            else
                return y;
        }
        break;

    default:
        break;
    }
}

void quickSortHP(int *arr, int inicio, int fim, int tipo, int *chamadas)
{
    *chamadas += 1;
    if (inicio < fim)
    {
        int pivot = calcPivot(tipo, inicio, fim, arr, chamadas);

        quickSortHP(arr, inicio, pivot, tipo, chamadas);
        quickSortHP(arr, pivot + 1, fim, tipo, chamadas);
    }
}

void quickSortLP(int *arr, int inicio, int fim, int tipo, int *chamadas)
{
    *chamadas += 1;
    if (inicio < fim)
    {
        int pivot = calcPivot(tipo, inicio, fim, arr, chamadas);

        quickSortLP(arr, inicio, pivot - 1, tipo, chamadas);
        quickSortLP(arr, pivot + 1, fim, tipo, chamadas);
    }
}

int particiona(int *arr, int *arr2, int inicio, int fim)
{
    int pivotIdx = inicio;
    int pivot = arr[inicio];
    int x = inicio - 1;
    int y = fim + 1;
    while (1)
    {
        while (arr[--y] > pivot)
            ;
        while (arr[++x] < pivot)
            ;
        if (x < y)
            troca2(arr, arr2, x, y);
        else
            return y;
    }
    return pivotIdx;
}

void quickSort2Arr(int *arr, int *arr2, int inicio, int fim)
{
    if (inicio < fim)
    {
        int pivot = particiona(arr, arr2, inicio, fim);
        quickSort2Arr(arr, arr2, inicio, pivot);
        quickSort2Arr(arr, arr2, pivot + 1, fim);
    }
}

int quicksortCaller(int *arr, int inicio, int fim, int tipo, FILE *f)
{
    int *tempArr = (int *)calloc(fim, sizeof(int));
    int chamadas = 0;
    memcpy(tempArr, arr, sizeof(int) * fim);
    switch (tipo)
    {
    case 0:
        quickSortLP(tempArr, inicio, fim - 1, tipo, &chamadas);
        return chamadas;
    case 1:
        quickSortHP(tempArr, inicio, fim - 1, tipo, &chamadas);
        return chamadas;
    case 2:
        quickSortLP(tempArr, inicio, fim - 1, tipo, &chamadas);

        return chamadas;
    case 3:
        quickSortHP(tempArr, inicio, fim - 1, tipo, &chamadas);

        return chamadas;
    case 4:
        quickSortLP(tempArr, inicio, fim - 1, tipo, &chamadas);
        return chamadas;
    case 5:
        quickSortHP(tempArr, inicio, fim - 1, tipo, &chamadas);
        return chamadas;
    default:
        return -1;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return -1;
    }
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");

    if (entrada == NULL)
    {
        return -1;
    }

    int n1 = 0, n2 = 0;
    int *arr;

    fscanf(entrada, "%d", &n1);
    // scanf("%d", &n1);

    for (int i = 0; i < n1; i++)
    {
        fscanf(entrada, "%d", &n2);
        // scanf("%d", &n2);
        arr = (int *)calloc(n2, sizeof(int));
        for (int j = 0; j < n2; j++)
        {
            // scanf("%d", &arr[j]);
            fscanf(entrada, "%d", &arr[j]);
        }
        fprintf(saida, "%d: N(%d) ", i, n2);
        int saidaArr[6];
        int caseN[6] = {0, 1, 2, 3, 4, 5};

        saidaArr[0] = quicksortCaller(arr, 0, n2, 0, saida);
        saidaArr[1] = quicksortCaller(arr, 0, n2, 1, saida);
        saidaArr[2] = quicksortCaller(arr, 0, n2, 2, saida);
        saidaArr[3] = quicksortCaller(arr, 0, n2, 3, saida);
        saidaArr[4] = quicksortCaller(arr, 0, n2, 4, saida);
        saidaArr[5] = quicksortCaller(arr, 0, n2, 5, saida);

        quickSort2Arr(saidaArr, caseN, 0, 5);

        for (int j = 0; j < 6; j++)
        {
            switch (caseN[j])
            {
            case 0:
                if (j < 5)
                    fprintf(saida, "LP(%d) ", saidaArr[j]);
                else
                    fprintf(saida, "LP(%d)", saidaArr[j]);
                break;
            case 1:
                if (j < 5)
                    fprintf(saida, "HP(%d) ", saidaArr[j]);
                else
                    fprintf(saida, "HP(%d)", saidaArr[j]);
                break;
            case 2:
                if (j < 5)
                    fprintf(saida, "LM(%d) ", saidaArr[j]);
                else
                    fprintf(saida, "LM(%d)", saidaArr[j]);
                break;
            case 3:
                if (j < 5)
                    fprintf(saida, "HM(%d) ", saidaArr[j]);
                else
                    fprintf(saida, "HM(%d)", saidaArr[j]);
                break;
            case 4:
                if (j < 5)
                    fprintf(saida, "LA(%d) ", saidaArr[j]);
                else
                    fprintf(saida, "LA(%d)", saidaArr[j]);
                break;
            case 5:
                if (j < 5)
                    fprintf(saida, "HA(%d) ", saidaArr[j]);
                else
                    fprintf(saida, "HA(%d)", saidaArr[j]);
                break;
            default:
                break;
            }
        }
        if (i + 1 < n1)
            fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}