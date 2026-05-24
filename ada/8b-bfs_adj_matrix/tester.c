#include <stdio.h>
#include <stdlib.h>

int graph[100][100];
int dist[100];
int parent[100];
int stepCount = 0, cycleCount = 0;

void BFS(int n, int s) {
    int q[100], f = 0, r = 0;
    dist[s] = ++stepCount;
    parent[s] = -1;
    q[r++] = s;
    printf(" %c", s + 'A');
    while (f < r) {
        int u = q[f++];
        for (int w = 0; w < n; w++) {
            if (graph[u][w]) {
                if (dist[w] == -1) {
                    dist[w] = ++stepCount;
                    parent[w] = u;
                    q[r++] = w;
                    printf(" %c", w + 'A');
                } else if (w != parent[u] && dist[w] < dist[u])
                    cycleCount++;
            }
        }
    }
}

int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) graph[i][j] = 0;
        dist[i] = -1;
        parent[i] = -1;
    }
    printf("Enter each edge as two vertices (A B):\n");
    for (int i = 0; i < e; i++) {
        char u, v;
        printf("Edge %d: ", i + 1);
        scanf(" %c %c", &u, &v);
        graph[u - 'A'][v - 'A'] = 1;
        graph[v - 'A'][u - 'A'] = 1;
    }
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("  %c:", i + 'A');
        for (int j = 0; j < n; j++) printf(" %d", graph[i][j]);
        printf("\n");
    }
    int cc = 0;
    printf("\nBFS Traversal:\n");
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            cc++;
            printf("  Component %d:", cc);
            BFS(n, i);
            printf("\n");
        }
    }
    printf("\nVisit Order:\n");
    for (int i = 0; i < n; i++)
        printf("  %c: step %d\n", i + 'A', dist[i]);
    if (cc == 1) printf("\nThe graph IS connected.\n");
    else printf("\nThe graph is NOT connected. (%d components)\n", cc);
    if (!cycleCount) printf("The graph has NO cycle.\n");
    else printf("The graph HAS a cycle. (%d cross/back edge(s))\n", cycleCount);
    return 0;
}
