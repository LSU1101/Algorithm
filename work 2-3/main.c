#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int parent[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType *g) {
    int i, j;
    printf("================================\n");
    for (i = 0; i < g -> n; i++) {
        for (j = 0; j < g -> n; j++) {
            if (A[i][j] == INF) {
                printf("  * ");
            } else {
                printf("%3d ", A[i][j]);
            }
        }
        printf("\n");
    }
    printf("================================\n");
}

void floyd(GraphType *g) {
    int i, j, k;
    for (i = 0; i < g -> n; i++) {
        for (j = 0; j < g -> n; j++) {
            A[i][j] = g -> weight[i][j];
        }
    }
    
    
    printA(g);
    
    for (k = 0; k < g -> n; k++) {
        for (i = 0; i < g -> n; i++) {
            for (j = 0; j < g -> n; j++) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    parent[i][j] = k; // 최단 경로 저장
                }
            }
        }
        printA(g);
    }
}

void print_path(int start, int end) {
    if (parent[start][end] != 0) {
        print_path(start, parent[end][start]);
        printf("%d -> ", parent[start][end]);
        print_path(parent[start][end], end);
    }
    
}

// 2번과 같이 print_path 함수에 재귀를 사용해 문제를 해결했습니다. 그러나 문제를 푸는 중 계속해서 무한루프가 발생해 if (parent[start][end] != 0) 를 이용해 거쳐가야 할 정점이 없는 경우 실행하지 않도록 했습니다.
int main(void) {
    GraphType g = {7,
        {{0, 7, INF, INF, 3, 10, INF }, // 0
        {7, 0, 4, 10, 2, 6, INF },      // 1
        {INF, 4, 0, 2, INF, INF, INF }, // 2
        {INF, 10, 2, 0, 11, 9, 4 },     // 3
        {3, 2, INF, 11, 0, INF, 5 },    // 4
        {10, 6, INF, 9, INF, 0, INF },  // 5
        {INF, INF, INF, 4, 5, INF, 0 }} // 6
    };
    
    floyd(&g);
    
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            printf("%d -> ", i);
            print_path(i, j);
            printf("%d 거리: %d\n", j, A[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
