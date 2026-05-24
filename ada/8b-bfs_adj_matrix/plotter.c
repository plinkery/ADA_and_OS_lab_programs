#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100];
int count, queue[100], front, rear;

void reset(int n) {
    for (int i = 0; i < n; i++) visited[i] = 0;
}

void BFS(int n, int s) {
    front = rear = 0;
    visited[s] = 1;
    queue[rear++] = s;
    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < n; v++) {
            count++;
            if (graph[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
}

void runBFS(int n) {
    for (int i = 0; i < n; i++)
        if (!visited[i]) BFS(n, i);
}

void gen_best(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    for (int i = 0; i < n - 1; i++) {
        graph[i][i + 1] = 1;
        graph[i + 1][i] = 1;
    }
}

void gen_worst(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = (i != j) ? 1 : 0;
}

int main() {
    FILE *f1 = fopen("BFSBEST.txt", "w");
    FILE *f2 = fopen("BFSWORST.txt", "w");
    for (int n = 1; n <= 10; n++) {
        gen_best(n); reset(n); count = 0; runBFS(n); fprintf(f1, "%d\t%d\n", n, count);
        gen_worst(n); reset(n); count = 0; runBFS(n); fprintf(f2, "%d\t%d\n", n, count);
    }
    fclose(f1); fclose(f2);
    system("gnuplot command.txt");
    return 0;
}
