#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES   100
#define INF   1000000   /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
   int n;   // 정점의 개수
   int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int change[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g, int k)
{
   int i, j;
   if (k == -1)
      printf("그래프의 가중치 행렬로 초기화한 배열 A^%d\n", k);
   else
      printf("정점 %d를 거쳐가는 경로와 비교하여 최단 경로를 수정한 배열 A^%d\n", k, k);

   printf("========================================================\n");
   for (i = 0; i < g->n; i++) {
      for (j = 0; j < g->n; j++) {
         if (A[i][j] == INF)
            printf("   *   ");
         else if (change[i][j] >= 0)
            printf("%3d(%d) ", A[i][j], change[i][j]);
         else
            printf(" %3d   ", A[i][j]);
      }
      printf("\n");
   }
   printf("\n\n");
}


void print_shortest_path(GraphType* g, int start, int end) {
      
   if (change[start][end] == -1) {
      printf("%d-", end);
   }
   else {
      print_shortest_path(g,start, change[start][end]);
      print_shortest_path(g, change[start][end], end);
   }
}

void floyd(GraphType* g)
{
   int i, j, k;
   for (i = 0; i < g->n; i++) {
      for (j = 0; j < g->n; j++) {
         A[i][j] = g->weight[i][j];
         change[i][j] = -1;
      }
   }
   // 초기화
   printA(g, -1);

   for (k = 0; k < g->n; k++) {
      //   change[i][j] = FALSE; // 계속 초기화
      for (i = 0; i < g->n; i++)
         for (j = 0; j < g->n; j++)
            if (A[i][k] + A[k][j] < A[i][j]) {
               A[i][j] = A[i][k] + A[k][j];
               change[i][j] = k;
            }
      printA(g, k);
   }

   printf("\n");

   for (i = 0; i < g->n; i++) {
      for (j = 0; j < g->n; j++) {
         if (i != j) {
            printf("%d에서 %d까지의 최단 경로와 가중치 %d-", i, j, i);
            print_shortest_path(g, i, j);
            printf("(%d)\n\n", A[i][j]);
         }
      }
   }
}

int main(void)
{
   GraphType g = { 7,
   {{ 0,  7,  INF, INF,   3,  10, INF },
   { 7,  0,    4,  10,   2,   6, INF },
   { INF,  4,    0,   2, INF, INF, INF },
   { INF, 10,    2,   0,  11,   9,   4 },
   { 3,  2,  INF,  11,   0, INF,   5 },
   { 10,  6,  INF,   9, INF,   0, INF },
   { INF, INF, INF,   4,   5, INF,   0 } }
   };

   GraphType g1 = { 3,
      {{0,3,1},{2,0,4},{5,1,0}} };
   floyd(&g);
   return 0;
}
