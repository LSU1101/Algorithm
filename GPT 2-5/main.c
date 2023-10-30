#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType {
    int n;               // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
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

void add_edge(GraphType *g, int start, int end, int weight) {
    GraphNode *node;
    
    if (start >= g -> n || end  >= g -> n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    
    node = (GraphNode *)malloc(sizeof(GraphNode));
    node -> vertex = end;
    node -> weight = weight;
    node -> next = g -> adj_list[start];
    g-> adj_list[start] = node;
}

void create_graph(GraphType* g) {
    g -> n = 7;

    for (int i = 0; i < g->n; i++) {
        g -> adj_list[i] = NULL;
    }

    add_edge(g, 0, 1, 7);
    add_edge(g, 0, 4, 3);
    add_edge(g, 0, 5, 10);
    add_edge(g, 1, 0, 7);
    add_edge(g, 1, 2, 4);
    add_edge(g, 1, 3, 10);
    add_edge(g, 1, 4, 2);
    add_edge(g, 1, 5, 6);
    add_edge(g, 2, 1, 4);
    add_edge(g, 2, 3, 2);
    add_edge(g, 3, 1, 10);
    add_edge(g, 3, 2, 2);
    add_edge(g, 3, 4, 11);
    add_edge(g, 3, 6, 4);
    add_edge(g, 4, 0, 3);
    add_edge(g, 4, 1, 2);
    add_edge(g, 4, 3, 11);
    add_edge(g, 4, 6, 5);
    add_edge(g, 5, 0, 10);
    add_edge(g, 5, 1, 6);
    add_edge(g, 5, 3, 9);
    add_edge(g, 6, 3, 4);
    add_edge(g, 6, 4, 5);
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;
    for (i = 0; i < g->n; i++) { // 초기화
        distance[i] = INF;
        found[i] = FALSE;
    }
    
    distance[start] = 0;
    
    for (i = 0; i < g -> n - 1; i++) {
        print_status(g);
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        GraphNode* current = g -> adj_list[u];
        while (current != NULL) {
            w = current -> vertex;
            if (!found[w] && distance[u] + current -> weight < distance[w]) {
                distance[w] = distance[u] + current->weight;
            }
            current = current -> next;
        }
    }
}

// 10.2 코드를 참고해 GraphNode 구조체를 만들어 그래프를 연결리스트로 구현했습니다. 그리고 이 그래프에는 가중치가 있기에 10.2 구조체에 weight 변수를 추가했습니다. shortest_path 부분도 연결리스트에 맞게 수정하여 작성헀습니다. 또한 add_edge 함수를 호출하는 과정이 메인 함수에 모두 써 넣기에는 메인 함수 부분이 너무 길어져 creat_graph라는 함수를 새로 만들어  10.2에 init 함수와 합쳐 작성했습니다.

int main(void) {
    GraphType g;
    create_graph(&g);
    shortest_path(&g, 0);
    return 0;
}

