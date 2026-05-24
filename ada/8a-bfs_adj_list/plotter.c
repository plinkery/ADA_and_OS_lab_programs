#include <stdio.h>
#include <stdlib.h>

int count;
int queue[2000], front, rear;

typedef struct Node { int data; struct Node *next; } Node;
typedef struct Graph { int V; int *vis; Node **adj; } Graph;

Node *createNode(int v) {
    Node *nn = malloc(sizeof(Node));
    nn->data = v; nn->next = NULL;
    return nn;
}

Graph *createGraph(int v) {
    Graph *g = malloc(sizeof(Graph));
    g->V = v;
    g->adj = calloc(v, sizeof(Node *));
    g->vis = calloc(v, sizeof(int));
    return g;
}

void addEdge(Graph *g, int u, int v) {
    Node *nn = createNode(v);
    nn->next = g->adj[u]; g->adj[u] = nn;
    nn = createNode(u);
    nn->next = g->adj[v]; g->adj[v] = nn;
}

void freeGraph(Graph *g) {
    for (int i = 0; i < g->V; i++) {
        Node *c = g->adj[i];
        while (c) { Node *t = c; c = c->next; free(t); }
    }
    free(g->adj); free(g->vis); free(g);
}

void BFS(Graph *g, int s) {
    front = rear = 0;
    g->vis[s] = 1;
    queue[rear++] = s;
    while (front < rear) {
        int u = queue[front++];
        Node *t = g->adj[u];
        while (t) {
            count++;
            if (!g->vis[t->data]) {
                g->vis[t->data] = 1;
                queue[rear++] = t->data;
            }
            t = t->next;
        }
    }
}

void runBFS(Graph *g) {
    for (int i = 0; i < g->V; i++)
        if (!g->vis[i]) BFS(g, i);
}

Graph *gen_best(int n) {
    Graph *g = createGraph(n);
    for (int i = 0; i < n - 1; i++) addEdge(g, i, i + 1);
    return g;
}

Graph *gen_worst(int n) {
    Graph *g = createGraph(n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            addEdge(g, i, j);
    return g;
}

int main() {
    FILE *f1 = fopen("Best_Case.txt", "w");
    FILE *f2 = fopen("Worst_Case.txt", "w");
    for (int n = 1; n < 1025; n *= 2) {
        Graph *g = gen_best(n); count = 0; runBFS(g); fprintf(f1, "%d\t%d\n", n, count); freeGraph(g);
        g = gen_worst(n); count = 0; runBFS(g); fprintf(f2, "%d\t%d\n", n, count); freeGraph(g);
    }
    fclose(f1); fclose(f2);
    system("gnuplot command.txt");
    return 0;
}
