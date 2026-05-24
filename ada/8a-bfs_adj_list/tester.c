#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int V;
    Node **adjList;
    Node **rear;
    int *dist;
    int *parent;
} Graph;

int stepCount = 0, cycleCount = 0;

Node *createNode(int v) {
    Node *nn = malloc(sizeof(Node));
    nn->data = v; nn->next = NULL;
    return nn;
}

Graph *createGraph(int v) {
    Graph *g = malloc(sizeof(Graph));
    g->V = v;
    g->adjList = calloc(v, sizeof(Node *));
    g->rear = calloc(v, sizeof(Node *));
    g->dist = malloc(v * sizeof(int));
    g->parent = malloc(v * sizeof(int));
    for (int i = 0; i < v; i++) {
        g->dist[i] = -1;
        g->parent[i] = -1;
    }
    return g;
}

void append(Graph *g, int u, int v) {
    Node *nn = createNode(v);
    if (!g->adjList[u])
        g->adjList[u] = g->rear[u] = nn;
    else {
        g->rear[u]->next = nn;
        g->rear[u] = nn;
    }
}

void addEdge(Graph *g, int u, int v) {
    append(g, u, v);
    append(g, v, u);
}

void BFS(Graph *g, int s) {
    int q[100], f = 0, r = 0;
    g->dist[s] = ++stepCount;
    g->parent[s] = -1;
    q[r++] = s;
    printf(" %c", s + 'A');
    while (f < r) {
        int u = q[f++];
        Node *t = g->adjList[u];
        while (t) {
            int w = t->data;
            if (g->dist[w] == -1) {
                g->dist[w] = ++stepCount;
                g->parent[w] = u;
                q[r++] = w;
                printf(" %c", w + 'A');
            } else if (w != g->parent[u] && g->dist[w] < g->dist[u])
                cycleCount++;
            t = t->next;
        }
    }
}

int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    Graph *g = createGraph(n);
    printf("Enter each edge as two vertices (A B):\n");
    for (int i = 0; i < e; i++) {
        char u, v;
        printf("Edge %d: ", i + 1);
        scanf(" %c %c", &u, &v);
        addEdge(g, u - 'A', v - 'A');
    }
    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        printf("  %c:", i + 'A');
        Node *t = g->adjList[i];
        while (t) { printf(" %c", t->data + 'A'); t = t->next; }
        printf("\n");
    }
    int cc = 0;
    printf("\nBFS Traversal:\n");
    for (int i = 0; i < n; i++) {
        if (g->dist[i] == -1) {
            cc++;
            printf("  Component %d:", cc);
            BFS(g, i);
            printf("\n");
        }
    }
    printf("\nVisit Order:\n");
    for (int i = 0; i < n; i++)
        printf("  %c: step %d\n", i + 'A', g->dist[i]);
    if (cc == 1) printf("\nThe graph IS connected.\n");
    else printf("\nThe graph is NOT connected. (%d components)\n", cc);
    if (!cycleCount) printf("The graph has NO cycle.\n");
    else printf("The graph HAS a cycle. (%d cross/back edge(s))\n", cycleCount);
    return 0;
}
