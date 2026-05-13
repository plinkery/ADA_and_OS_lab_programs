#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------
   Basic operation counter: incremented every time DFS
   examines a neighbour (edge inspection).
   Best case  : chain graph  -> E = V-1  -> count ~ 2(V-1)
   Worst case : complete graph -> E = V(V-1)/2 -> count ~ V^2
   ------------------------------------------------------- */

int count;

/* ---------- Adjacency-list graph ---------- */

struct node
{
    int info;
    struct node *next;
};

struct Graph
{
    int vertices;
    int *visit;
    struct node **adjLists;
};

typedef struct node *Node;

Node createNode(int n)
{
    Node nn = (Node)malloc(sizeof(struct node));
    nn->info = n;
    nn->next = NULL;
    return nn;
}

struct Graph *createGraph(int v)
{
    int i;
    struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
    g->vertices = v;
    g->adjLists = (struct node **)malloc(v * sizeof(struct node *));
    g->visit    = (int *)malloc(v * sizeof(int));
    for (i = 0; i < v; i++)
    {
        g->adjLists[i] = NULL;
        g->visit[i]    = 0;
    }
    return g;
}

void addEdge(struct Graph *g, int u, int v)
{
    Node nn;
    nn = createNode(v);
    nn->next = g->adjLists[u];
    g->adjLists[u] = nn;

    nn = createNode(u);
    nn->next = g->adjLists[v];
    g->adjLists[v] = nn;
}

void freeGraph(struct Graph *g)
{
    int i;
    for (i = 0; i < g->vertices; i++)
    {
        struct node *cur = g->adjLists[i];
        while (cur != NULL)
        {
            struct node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(g->adjLists);
    free(g->visit);
    free(g);
}

/* ---------- DFS ---------- */

void DFS(struct Graph *g, int vertex, int parent)
{
    struct node *temp = g->adjLists[vertex];
    g->visit[vertex] = 1;
    while (temp != NULL)
    {
        count++;                          /* basic operation: edge examination */
        if (g->visit[temp->info] == 0)
            DFS(g, temp->info, vertex);
        temp = temp->next;
    }
}

void runDFS(struct Graph *g)
{
    int i;
    for (i = 0; i < g->vertices; i++)
        if (g->visit[i] == 0)
            DFS(g, i, -1);
}

/* ---------- Graph generators ---------- */

/*
 * Best case: chain  0-1-2-...(n-1)
 * E = n-1, each edge examined twice -> count = 2(n-1)  => O(V)
 */
struct Graph *gen_best(int n)
{
    int i;
    struct Graph *g = createGraph(n);
    for (i = 0; i < n - 1; i++)
        addEdge(g, i, i + 1);
    return g;
}

/*
 * Worst case: complete graph K_n
 * E = n(n-1)/2, each edge examined twice -> count = n(n-1) => O(V^2)
 */
struct Graph *gen_worst(int n)
{
    int i, j;
    struct Graph *g = createGraph(n);
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            addEdge(g, i, j);
    return g;
}

/* ---------- Plotter (mirrors quicksort template exactly) ---------- */

void plotter(int p)
{
    int n;
    FILE *fp;
    struct Graph *g;

    if (p == 1)
        fp = fopen("Best_Case.txt", "w");
    else
        fp = fopen("Worst_Case.txt", "w");

    for (n = 1; n < 1034; n = n * 2)
    {
        if (p == 1)
            g = gen_best(n);
        else
            g = gen_worst(n);

        count = 0;
        runDFS(g);
        fprintf(fp, "%d\t%d\n", n, count);
        freeGraph(g);
    }
    fclose(fp);
}

int main()
{
    int i;
    for (i = 1; i <= 2; i++)
        plotter(i);
    system("gnuplot command.txt");
    return 0;
}
