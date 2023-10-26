#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n) {
    int v, i;
    for (i = 0; i < n; i++) {
        if (!selected[i]) {
            v = i;
            break;
        }
    }
    for (i = 0; i < n; i++) {
        if (!selected[i] && (distance[i] < distance[v])) {
            v = i;
        }
    }
    return (v);
}

void prim(GraphType *g, int s) {
    int i, u, v;
    int parent[MAX_VERTICES];

    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
        parent[u] = -1; // Initialize parent array
    }
    distance[s] = 0;

    for (i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;

        if (distance[u] == INF) {
            return;
        }

        if (parent[u] != -1) {
            printf("간선 (%d, %d) 추가, 가중치: %d\n", parent[u], u, distance[u]);
        }

        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
                parent[v] = u; // Update parent
            }
        }
    }
}

int main(void) {
    GraphType g = {8,
        {{0, 10, INF, 6, INF, INF, INF, 1}, // 0
        {10, 0, 4, INF, INF, 2, INF, INF}, // 1
        {INF, 4, 0, 11, INF, 7, INF, INF}, // 2
        {6, INF, 11, 0, INF, INF, INF, 3}, // 3
        {INF, INF, INF, INF, INF, 5, INF, 8}, // 4
        {INF, 2, 7, INF, 5, 0, 9, INF}, // 5
        {INF, INF, INF, INF, INF, 9, 0, 12}, // 6
        {1, INF, INF, 3, 8, INF, 12, 0}} // 7
    };

    printf("최소 신장 트리 간선 정보:\n");
    prim(&g, 0);

    return 0;
}
