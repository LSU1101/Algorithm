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
int parent[MAX_VERTICES];

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
                    parent[i] = k;
                }
            }
        }
        printA(g);
    }
}

void print_path(GraphType *g, int start, int end) {
    
    if (start == end) {
        printf("%d", start);
    }
    print_path(g, start, parent[start]);
    printf("%d ", parent[start]);
    print_path(g, parent[start], end);
    
}

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
    
    print_path(&g, 0, 6);
    
    return 0;
}
