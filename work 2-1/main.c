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

// 부모 정점을 저장하는 배열을 선언해 정점을 저장하고 추가 되는 정점과 함께 출력해 간선을 출력했습니다. 그러나 parent 배열의 값을 모두 -1로 초기화 해 놓아 맨 처음 출력 결과가 간선 (-1, 0)으로 나와 if문을 이용해 parent 배열의 값이 -1이면 출력하지 않도록 수정했습니다.

void prim(GraphType *g, int s) {
    int i, u, v;
    int parent[MAX_VERTICES];
    
    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
        parent[u] = -1;
    }
    distance[s] = 0;
    
    for (i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;
        
        if (distance[u] == INF) { // 끝
            return;
        }
        
        if (parent[u] != -1) {
            printf("간선 (%d, %d) \n", parent[u], u);
        }
        
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF) {
                if (!selected[v] && g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];
                    parent[v] = u;
                }
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
        {INF, INF, INF, INF, 0, 5, INF, 8}, // 4
        {INF, 2, 7, INF, 5, 0, 9, INF}, // 5
        {INF, INF, INF, INF, INF, 9, 0, 12}, // 6
        {1, INF, INF, 3, 8, INF, 12, 0}} // 7
    };
    
    printf("최소 신장 트리 간선 \n");
    prim(&g, 0);
    return 0;
}


