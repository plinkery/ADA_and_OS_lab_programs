#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ── utility functions ───────────────────────────────────────────── */

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void generateRandom(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}

void generateSorted(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void generateReverse(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

/* ── sorting algorithms (return comparison count) ─────────────────── */

/* Selection Sort */
int selectionSort(int arr[], int n)
{
    int count = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            count++;
            if (arr[j] < arr[min])
                min = j;
        }

        if (min != i)
            swap(&arr[i], &arr[min]);
    }

    return count;
}

int bubbleSort(int arr[], int n)
{
    int count = 0;
    int swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            count++;

            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    return count;
}

/* Insertion Sort */
int insertionSort(int arr[], int n)
{
    int count = 0;

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0)
        {
            count++;
            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            else
                break;
        }

        arr[j + 1] = key;
    }

    return count;
}

/* ── empirical plotter ───────────────────────────────────────────── */

void plotter_empirical(const char *worst_file,
                       const char *best_file,
                       const char *avg_file,
                       int (*algo)(int[], int))
{
    FILE *fw = fopen(worst_file, "w");
    FILE *fb = fopen(best_file, "w");
    FILE *fa = fopen(avg_file, "w");

    int arr[200], temp[200];

    for (int n = 10; n <= 100; n += 10)
    {
        int worst, best, avg = 0;

        /* Worst case */
        generateReverse(arr, n);
        copyArray(arr, temp, n);
        worst = algo(temp, n);

        /* Best case */
        generateSorted(arr, n);
        copyArray(arr, temp, n);
        best = algo(temp, n);

        /* Average case (take average of 5 runs) */
        for (int i = 0; i < 5; i++)
        {
            generateRandom(arr, n);
            copyArray(arr, temp, n);
            avg += algo(temp, n);
        }
        avg /= 5;

        fprintf(fw, "%d\t%d\n", n, worst);
        fprintf(fb, "%d\t%d\n", n, best);
        fprintf(fa, "%d\t%d\n", n, avg);
    }

    fclose(fw);
    fclose(fb);
    fclose(fa);
}

/* ── graph generator ───────────────────────────────────────────── */

void generateGraph(const char *title,
                   const char *worst,
                   const char *best,
                   const char *avg)
{
    FILE *cmd = fopen("command.txt", "w");

    fprintf(cmd, "set title '%s'\n", title);
    fprintf(cmd, "set xlabel 'Input size (n)'\n");
    fprintf(cmd, "set ylabel 'Comparisons'\n");
    fprintf(cmd, "set style data linespoints\n");

    fprintf(cmd,
        "plot '%s' title 'Worst', '%s' title 'Best', '%s' title 'Average'\n",
        worst, best, avg);

    fprintf(cmd, "pause -1\n");

    fclose(cmd);

    system("gnuplot command.txt");
}

/* ── main ───────────────────────────────────────────────────────── */

int main()
{
    srand(time(NULL));

    printf("Running analysis...\n");

    printf("Selection Sort...\n");
    plotter_empirical("Sel_W.txt", "Sel_B.txt", "Sel_A.txt", selectionSort);
    generateGraph("Selection Sort", "Sel_W.txt", "Sel_B.txt", "Sel_A.txt");

    printf("Bubble Sort...\n");
    plotter_empirical("Bub_W.txt", "Bub_B.txt", "Bub_A.txt", bubbleSort);
    generateGraph("Bubble Sort", "Bub_W.txt", "Bub_B.txt", "Bub_A.txt");

    printf("Insertion Sort...\n");
    plotter_empirical("Ins_W.txt", "Ins_B.txt", "Ins_A.txt", insertionSort);
    generateGraph("Insertion Sort", "Ins_W.txt", "Ins_B.txt", "Ins_A.txt");

    printf("Done.\n");

    return 0;
}
