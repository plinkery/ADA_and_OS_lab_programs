#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1, j;
    for (j = low; j < high; j++)
    {
        count++;
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    int pi;
    if (low < high)
    {
        pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void plotter(int p)
{
    int *a, n, i;
    FILE *fp;

    if (p == 1)
        fp = fopen("Worst_Case.txt", "w");
    else if (p == 2)
        fp = fopen("Best_Case.txt", "w");
    else
        fp = fopen("Average_Case.txt", "w");

    srand(time(NULL));

    for (n = 10; n < 30000; n = (n < 10000 ? n * 2 : n + 10000))
    {
        a = (int *)malloc(n * sizeof(int));

        if (p == 1)
        {
            /* Worst case: sorted ascending, last element always max pivot */
            for (i = 0; i < n; i++)
                a[i] = i + 1;
        }
        else if (p == 2)
        {
            /* Best case: sorted descending, pivot always median after partition */
            for (i = 0; i < n; i++)
                a[i] = n - i;
        }
        else
        {
            /* Average case: random shuffle */
            for (i = 0; i < n; i++)
                a[i] = i + 1;
            for (i = n - 1; i > 0; i--)
                swap(&a[i], &a[rand() % (i + 1)]);
        }

        count = 0;
        quickSort(a, 0, n - 1);
        fprintf(fp, "%d\t%d\n", n, count);
        free(a);
    }

    fclose(fp);
}

int main()
{
    int i;
    for (i = 1; i <= 3; i++)
        plotter(i);
    system("gnuplot > load 'command.txt'");
    return 0;
}
