#ifndef GRAPH_H
#define GRAPH_H

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int choose(int distance[], int n, int found[]);
void create_graph(GraphType* g);
void add_edge(GraphType* g, int start, int end, int weight);
void shortest_path(GraphType* g, int start);
void print_status(GraphType* g);

#endif
