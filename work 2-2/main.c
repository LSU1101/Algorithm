#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int parent[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void print_status(GraphType *g) {
    static int step = 1;
    
    printf("STEP %d: ", step++);
    printf("distance: ");
    
    for (int i = 0; i < g -> n; i++) {
        if (distance[i] == INF) {
            printf(" * ");
        } else {
            printf("%2d ", distance[i]);
        }
    }
    
    printf("\n");
    printf(" found: ");
    for (int i =0 ; i < g -> n; i++) {
        printf("%2d ", found[i]);
    }
    printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;
    
    for (i = 0 ; i < g -> n; i++) {
        distance[i] = g -> weight[start][i];
        found[i] = FALSE;
        // parent[i] = start;
    }
    
    found[start] = TRUE;
    distance[start] = 0;
    
    for (i = 0; i < g -> n - 1; i++) {
        print_status(g);
        u = choose(distance, g -> n, found);
        found[u] = TRUE;
        for (w = 0; w < g -> n; w++) {
            if (!found[w]) {
                if (distance[u] + g -> weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g -> weight[u][w];
                    parent[w] = u;
                }
            }
        }
    }
}

// 1번과 같이 parent 배열을 추가해 부모 정점을 저장하고 부모 정점을 따라가며 경로를 출력하려 헀습니다. 이 과정에서 재귀 함수를 사용하는 것이 적절하다 판단헀고, 직접 함수의 재귀 과정을 그리며 구조를 짜고 이해했습니다.

void print_shortest_path(GraphType *g, int start, int end) {
    if (end == start) {
        printf("%d ", start);
    } else {
        print_shortest_path(g, start, parent[end]);
        printf("%d ", end);
    }
}

int main(void) {
    GraphType g = {8,
        {{0, 7, INF, 5, INF, 2, INF, INF }, // 0
        { 7, 0, 6, INF, 2, INF, INF, 1 },   // 1
        { INF, 6, 0, 2, INF, INF, 2, 8 },   // 2
        { 5, INF, 2, 0, INF, 5, INF, INF }, // 3
        { INF, 2, INF, INF, 0, 2, INF, 4 }, // 4
        { 2, INF, INF, 5, 2, 0, 4, INF },   // 5
        { INF, INF, 2, INF, INF, 4, 0, 4 }, // 6
        { INF, 1, 8, INF, 4, INF, 4, 0 } }  // 7
    };
    
    shortest_path(&g, 0);
    
    for (int i = 0; i < g.n; i++) {
        printf("0부터 %d까지의 경로: ", i);
        print_shortest_path(&g, 0, i);
        printf("\n");
    }
    
    return 0;
}
