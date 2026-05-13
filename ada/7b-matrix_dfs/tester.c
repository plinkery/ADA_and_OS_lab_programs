#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100], isCyclic = 0;
int dfsCount = 0, count = 0;
int dcount = 0;
int path[100];
int d;

void dfs(int n, int start, int parent)
{
    visited[start] = 1;
    path[start] = 1;
    count++;
    printf("--> %c ", start + 65);

    int i;
    for (i = 0; i < n; i++)
    {
        if (d == 1)
        {
            /* directed graph: cycle if we see a node still on current path */
            if (i != parent && graph[start][i] && visited[i] == 1 && path[i] == 1)
                isCyclic = 1;
        }
        else
        {
            /* undirected graph: cycle if visited neighbour is not parent */
            if (i != parent && graph[start][i] && visited[i])
                isCyclic = 1;
        }

        dcount++;
        if (graph[start][i] && visited[i] == 0)
            dfs(n, i, start);
    }
    path[start] = 0;
}

void main()
{
    int n, start, i, j;
    dfsCount = 0;
    count    = 0;
    dcount   = 0;
    d        = 0;

    printf("Enter the number of nodes in the graph:\n");
    scanf("%d", &n);

    printf("Enter the Adjacency Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
        visited[i] = 0;
        path[i]    = 0;
    }

    printf("Enter 1 if the graph is directed, 0 if undirected:\n");
    scanf("%d", &d);

    printf("The Adjacency Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    isCyclic = 0;
    printf("\nDFS traversal starting from node %c\n", 65);
    dfs(n, 0, -1);
    dfsCount++;

    if (count == n)
        printf("\nThe Graph is connected\n");
    else
    {
        printf("\nThe Graph is not connected\n");
        start = 1;
        while (count != n)
        {
            if (visited[start] != 1)
            {
                printf("\n");
                dfs(n, start, -1);
                dfsCount++;
            }
            start++;
        }
    }

    printf("\nThe number of components is %d\n", dfsCount);

    if (isCyclic)
        printf("\nThe graph is cyclic\n");
    else
        printf("\nThe graph is not cyclic\n");
}
