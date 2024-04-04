#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct datagram
{
    int posicao;
    char *s;
} Datagram;

typedef struct datagramArray
{
    Datagram **dataArray;
} DatagramArray;

void swap(DatagramArray *arr, int a, int b)
{
    Datagram *temp = (Datagram *)calloc(1, sizeof(Datagram));
    temp->posicao = arr->dataArray[a]->posicao;
    temp->s = arr->dataArray[a]->s;
    arr->dataArray[a]->posicao = arr->dataArray[b]->posicao;
    arr->dataArray[a]->s = arr->dataArray[b]->s;
    arr->dataArray[b]->posicao = temp->posicao;
    arr->dataArray[b]->s = temp->s;
}

void heapfy(DatagramArray *arr, int N, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && arr->dataArray[left]->posicao > arr->dataArray[largest]->posicao)
        largest = left;

    if (right < N && arr->dataArray[right]->posicao > arr->dataArray[largest]->posicao)
        largest = right;

    if (largest != i)
    {
        swap(arr, i, largest);
        heapfy(arr, N, largest);
    }
}
void heapsort(DatagramArray *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapfy(arr, size, i);

    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr, 0, i);
        heapfy(arr, i, 0);
    }
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
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    if (saida == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    // n1 e numero de pacotes, n2 e a quantidade minima de pacotes ordenados necessaria para impressao
    // de todos ordenados ate o momento
    int n1 = 0, n2 = 0, count = 0, printCount = 0, totalPrints = 0;

    fscanf(entrada, "%d %d", &n1, &n2);
    // scanf("%d %d", &n1, &n2);
    DatagramArray *arr = (DatagramArray *)calloc(1, sizeof(DatagramArray));
    Datagram *data = (Datagram *)calloc(n1, sizeof(Datagram));
    arr->dataArray = data;
    for (int i = 0; i < n1; i++)
    {
        int tam = 0;
        char *s;
        Datagram *d = (Datagram *)calloc(1, sizeof(Datagram));
        fscanf(entrada, "%d %d", &d->posicao, &tam);
        // scanf("%d %d ", &d->posicao, &tam);
        d->s = (char *)calloc(tam * 3, sizeof(char));
        for (int j = 0; j < tam; j++)
        {
            fscanf(entrada, "%s", &d->s[j * 3]);
            // scanf("%s", &d->s[j * 3]);
            d->s[(j * 3) - 1] = ' ';
        }
        arr->dataArray[i] = d;
        count++;
        if (count == n2)
        {
            heapsort(arr, i + 1);
            count = 0;
            if (printCount == arr->dataArray[printCount]->posicao)
            {
                fprintf(saida, "%d: ", totalPrints);
                // printf("%d: ", totalPrints);
                totalPrints++;
                while (printCount <= i && printCount == arr->dataArray[printCount]->posicao)
                {
                    fprintf(saida, "%s ", arr->dataArray[printCount]->s);
                    // printf("%s ", arr->dataArray[printCount]->s);
                    printCount++;
                }
                fprintf(saida, "\n");
                // printf("\n");
            }
        }
        else if (i + 1 >= n1)
        {
            heapsort(arr, i + 1);
            fprintf(saida, "%d: ", totalPrints);
            // printf("%d: ", totalPrints);
            totalPrints++;

            while (printCount <= i)
            {
                fprintf(saida, "%s ", arr->dataArray[printCount]->s);
                // printf("%s ", arr->dataArray[printCount]->s);
                printCount++;
            }
            fprintf(saida, "\n");
            // printf("\n");
        }
    }

    fclose(entrada);

    fclose(saida);

    return 0;
}