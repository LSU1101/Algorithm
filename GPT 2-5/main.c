#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct GraphType {
    int n;               // 정점의 개수
    EdgeNode* adj_list[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];   /* 방문한 정점 표시 */

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

void print_status(GraphType* g) {
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf("        found:    ");
    for (int i = 0; i < g->n; i++)
        printf("%2d ", found[i]);
    printf("\n\n");
}

void add_edge(GraphType* g, int start, int end, int weight) {
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = end;
    newNode->weight = weight;
    newNode->next = g->adj_list[start];
    g->adj_list[start] = newNode;
}

void create_graph(GraphType* g) {
    g->n = 7;

    for (int i = 0; i < g->n; i++) {
        g->adj_list[i] = NULL;
    }

    add_edge(g, 0, 1, 7);
    add_edge(g, 0, 4, 3);
    add_edge(g, 0, 5, 10);
    add_edge(g, 1, 0, 7);
    add_edge(g, 1, 2, 4);
    add_edge(g, 1, 3, 10);
    // 다른 엣지들도 추가
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;
    for (i = 0; i < g->n; i++) /* 초기화 */
    {
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;
    for (i = 0; i < g->n - 1; i++) {
        print_status(g);
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        EdgeNode* current = g->adj_list[u];
        while (current != NULL) {
            w = current->vertex;
            if (!found[w] && distance[u] + current->weight < distance[w]) {
                distance[w] = distance[u] + current->weight;
            }
            current = current->next;
        }
    }
}

int main(void) {
    GraphType g;
    create_graph(&g);
    shortest_path(&g, 0);
    return 0;
}

