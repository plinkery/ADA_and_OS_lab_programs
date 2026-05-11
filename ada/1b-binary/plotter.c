#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

int count;

int binarySearch(int *a, int k, int n)
{
    int low = 0, high = n - 1;
    count = 0;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        count++;
        if (a[mid] == k)
        {
            return count;
        }
        count++;
        if (a[mid] < k)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
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
    for (n = 10; n < 30000; n = (n < 10000 ? n * 2 : n + 10000))
    {
        a = (int *)malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            a[i] = i + 1;
        if (p == 1)
        {
            key = -1;
        }
        else
        {
            key = a[(n-1)/2];
        }
        res = binarySearch(a, key, n);
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
