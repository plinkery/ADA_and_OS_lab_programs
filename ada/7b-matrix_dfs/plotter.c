#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100], isCyclic = 0;
int dfsCount = 0, count = 0;
int dcount = 0;

void dfs1(int n, int start, int parent)
{
    int i;
    visited[start] = 1;
    count++;
    for (i = 0; i < n; i++)
    {
        if (i != parent && graph[start][i] && visited[i])
            isCyclic = 1;

        dcount++;                              /* basic operation: matrix cell examined */
        if (graph[start][i] && visited[i] == 0)
            dfs1(n, i, start);
    }
}

void ploter(int k)
{
    FILE *f1 = fopen("DFSBEST.txt", "w");     /* "w" : overwrite each run */
    FILE *f2 = fopen("DFSWORST.txt", "w");    /* "w" : overwrite each run */
    int v, i, j, l, start;

    for (i = 1; i <= 10; i++)
    {
        v = i;

        /* reset visited array */
        for (j = 0; j < v; j++)
            visited[j] = 0;

        /* k=0 : worst case -> complete graph (maximum edges) */
        if (k == 0)
        {
            for (j = 0; j < v; j++)
                for (l = 0; l < v; l++)
                    graph[j][l] = (j != l) ? 1 : 0;
        }

        /* k=1 : best case -> chain graph 0-1-2-...-(v-1) */
        if (k == 1)
        {
            for (j = 0; j < v; j++)
                for (l = 0; l < v; l++)
                    graph[j][l] = 0;
            for (j = 0; j < v - 1; j++)
            {
                graph[j][j + 1] = 1;
                graph[j + 1][j] = 1;
            }
        }

        isCyclic  = 0;
        dfsCount  = 0;
        count     = 0;
        dcount    = 0;

        dfs1(v, 0, -1);
        dfsCount++;

        start = 1;
        while (count != v)
        {
            if (visited[start] != 1)
            {
                dfs1(v, start, -1);
                dfsCount++;
            }
            start++;
        }

        if (k == 0)
            fprintf(f2, "%d\t%d\n", v, dcount);
        else
            fprintf(f1, "%d\t%d\n", v, dcount);
    }

    fclose(f1);
    fclose(f2);
}

void main()
{
    int i;
    for (i = 0; i < 2; i++)
        ploter(i);
    printf("DATA ENTERED INTO THE FILE\n");
    system("gnuplot command.txt");
}
