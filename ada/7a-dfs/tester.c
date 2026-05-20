#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int V;
    Node **adjList;   /* adjList[i] = head of adjacency list for vertex i     */
    Node **rear;      /* rear[i]    = pointer to last node, for O(1) append   */
    int  *visitOrder; /* visitOrder[vertex] = the step at which it was visited */
} Graph;

/* Globals – simple to use in lab, clearly named */
int stepCount   = 0; /* increments with each vertex visited, stored in visitOrder */
int cycleCount  = 0; /* increments on each back edge found                        */

/* ── helpers ── */

Node *createNode(int n) {
    Node *newNode  = (Node *)malloc(sizeof(Node));
    newNode->data  = n;
    newNode->next  = NULL;
    return newNode;
}

Graph *createGraph(int v) {
    Graph *g    = (Graph *)malloc(sizeof(Graph));
    g->V        = v;
    g->adjList  = (Node **)malloc(v * sizeof(Node *));
    g->rear     = (Node **)malloc(v * sizeof(Node *));
    g->visitOrder = (int  *)malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->adjList[i]   = NULL;
        g->rear[i]      = NULL;
        g->visitOrder[i] = 0;   /* 0 = not yet visited */
    }
    return g;
}

/* Rear-pointer append: O(1) instead of walking to the end every time */
void appendToList(Graph *g, int vertex, int neighbour) {
    Node *newNode = createNode(neighbour);

    if (g->adjList[vertex] == NULL) {
        g->adjList[vertex] = newNode;
        g->rear[vertex]    = newNode;
    } else {
        g->rear[vertex]->next = newNode;
        g->rear[vertex]       = newNode;
    }
}

void addEdge(Graph *g, int u, int v) {
    appendToList(g, u, v);
    appendToList(g, v, u);
}

/* ── DFS ── */

void DFS(Graph *g, int vertex, int parent) {
    stepCount++;
    g->visitOrder[vertex] = stepCount;   /* store the actual visit step, not just 1 */

    printf(" %c", vertex + 'A');

    Node *nbr = g->adjList[vertex];
    while (nbr != NULL) {
        int w = nbr->data;

        /* count back edge only when neighbor is already visited and is an ancestor  Only count as back edge if w was visited BEFORE current vertex */
        if (g->visitOrder[w] != 0 && w != parent && g->visitOrder[w] < g->visitOrder[vertex])
            cycleCount++;

        if (g->visitOrder[w] == 0)  
            DFS(g, w, vertex);

        nbr = nbr->next;
    }
}

/* ── main ── */

int main() {
    int n, e;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    Graph *g = createGraph(n);

    printf("Enter each edge as two vertices (e.g. A B):\n");
    for (int i = 0; i < e; i++) {
        char u, v;
        printf("Edge %d: ", i + 1);
        scanf(" %c %c", &u, &v);
        addEdge(g, u - 'A', v - 'A');
    }

    /* Print adjacency list */
    printf("\nAdjacency List:\n");
    for (int i = 0; i < g->V; i++) {
        printf("  %c:", i + 'A');
        Node *temp = g->adjList[i];
        while (temp != NULL) {
            printf(" %c", temp->data + 'A');
            temp = temp->next;
        }
        printf("\n");
    }

    /* DFS – one call per component */
    int componentCount = 0;

    printf("\nDFS Traversal:\n");
    for (int i = 0; i < g->V; i++) {
        if (g->visitOrder[i] == 0) {
            componentCount++;
            printf("  Component %d:", componentCount);
            DFS(g, i, -1);
            printf("\n");
        }
    }

    /* Print visit order */
    printf("\nVisit Order:\n");
    for (int i = 0; i < g->V; i++)
        printf("  %c: step %d\n", i + 'A', g->visitOrder[i]);

    /* Results */
    if (componentCount == 1)
        printf("\nThe graph IS connected.\n");
    else
        printf("\nThe graph is NOT connected. (%d components found)\n", componentCount);

    if (cycleCount == 0)
        printf("The graph has NO cycle (it is acyclic).\n");
    else
        printf("The graph HAS a cycle. (%d back edge(s) found)\n", cycleCount);

    return 0;
}