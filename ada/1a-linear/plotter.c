#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

int linearSearch(int *a, int k, int n)
{
    int i;
    count = 0;
    for (i = 0; i < n; i++)
    {
        count++;
        if (*(a + i) == k)
        {
            return count;
        }
    }
    return count;
}

void plotter(int p)
{
    int *a, n, key, i, res;
    FILE *fp;
    if (p == 1)
        fp = fopen("Worst_Case.txt", "w");
    else
        fp = fopen("Best_Case.txt", "w");
    srand(time(NULL));
    for (n = 10; n < 30000; n = (n < 10000 ? n * 10 : n + 10000))
    {
        a = (int *)malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            *(a + i) = rand() % n;
        key = (p == 1) ? (*(a + n - 1) = -1) : a[0];
        res = linearSearch(a, key, n);
        fprintf(fp, "%d\t%d\n", n, res);
        free(a);
    }
    fclose(fp);
}

int main()
{
    int i;
    for (i = 1; i <= 2; i++)
        plotter(i);
    system("gnuplot > load 'command.txt'");
    return 0;
}
