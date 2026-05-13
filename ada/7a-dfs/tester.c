#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *next;
};

struct Graph {
    int vertices;
    int *visit;
    struct node **adjLists;
};

typedef struct node *Node;

Node createNode(int n) {
    Node nn = (Node)malloc(sizeof(struct node));
    nn->info = n;
    nn->next = NULL;
    return nn;
}

struct Graph *createGraph(int vertices) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct node *));
    graph->visit = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visit[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph *graph, int u, int v) {
    /* Add v to u's list */
    Node nn = createNode(v);
    nn->next = graph->adjLists[u];
    graph->adjLists[u] = nn;
    /* Add u to v's list (undirected) */
    nn = createNode(u);
    nn->next = graph->adjLists[v];
    graph->adjLists[v] = nn;
}

int count = 0, iscyclic = 0;

void DFS(struct Graph *graph, int vertex, int parent) {
    graph->visit[vertex] = 1;
    count++;
    printf(" %c", vertex + 65);

    struct node *temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int nbr = temp->info;
        if (graph->visit[nbr] == 1 && nbr != parent) {
            iscyclic = 1;
        }
        if (graph->visit[nbr] == 0) {
            DFS(graph, nbr, vertex);
        }
        temp = temp->next;
    }
}

int main() {
    int n, e;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);

    struct Graph *g = createGraph(n);

    printf("Enter each edge as two vertices (e.g. A B):\n");
    for (int i = 0; i < e; i++) {
        char u, v;
        printf("Edge %d: ", i + 1);
        scanf(" %c %c", &u, &v);
        addEdge(g, u - 65, v - 65);
    }

    /* Print adjacency list */
    printf("\nAdjacency List:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("  %c:", i + 65);
        struct node *temp = g->adjLists[i];
        while (temp != NULL) {
            printf(" %c", temp->info + 65);
            temp = temp->next;
        }
        printf("\n");
    }

    /* DFS traversal — find connected components */
    int componentCount = 0;
    printf("\nDFS Traversal:\n");
    for (int i = 0; i < g->vertices; i++) {
        if (g->visit[i] == 0) {
            componentCount++;
            printf("  Component %d:", componentCount);
            DFS(g, i, -1);
            printf("\n");
        }
    }

    /* Connectivity */
    if (componentCount == 1)
        printf("\nThe graph IS connected.\n");
    else {
        printf("\nThe graph is NOT connected. (%d components found)\n", componentCount);
    }

    /* Acyclicity */
    if (iscyclic)
        printf("The graph HAS a cycle.\n");
    else
        printf("The graph has NO cycle (it is acyclic).\n");

    return 0;
}
