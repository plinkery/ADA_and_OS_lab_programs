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

int partition(int *arr, int beg, int end)
{
    int pivot = arr[beg];
    int i = beg, j;
    for (j = beg + 1; j <= end; j++)
    {
        count++;
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[beg], &arr[i]);
    return i;
}

void quicksort(int *arr, int beg, int end)
{
    if (beg < end)
    {
        int split = partition(arr, beg, end);
        quicksort(arr, beg, split - 1);
        quicksort(arr, split + 1, end);
    }
}

void gen_worst(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}

void gen_avg(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % n;
}

void best_rearrange(int *arr, int lo, int hi)
{
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    best_rearrange(arr, lo, mid - 1);
    best_rearrange(arr, mid + 1, hi);
    int tmp = arr[lo];
    arr[lo] = arr[mid];
    arr[mid] = tmp;
}

void gen_best(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
    best_rearrange(arr, 0, n - 1);
}

void plotter(int p)
{
    int *arr, n;
    FILE *fp;

    if (p == 1)
        fp = fopen("Best_Case.txt", "w");
    else if (p == 2)
        fp = fopen("Worst_Case.txt", "w");
    else
        fp = fopen("Avg_Case.txt", "w");

    for (n = 4; n < 1034; n = n * 2)
    {
        arr = (int *)malloc(n * sizeof(int));

        if (p == 1)
            gen_best(arr, n);
        else if (p == 2)
            gen_worst(arr, n);
        else
            gen_avg(arr, n);

        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(fp, "%d\t%d\n", n, count);
        free(arr);
    }
    fclose(fp);
}

int main()
{
    int i;
    srand(time(NULL));
    for (i = 1; i <= 3; i++)
        plotter(i);
    system("gnuplot command.txt");
    return 0;
}
