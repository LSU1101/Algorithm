#include "graph.h"

int main(void) {
    GraphType g;
    create_graph(&g);
    shortest_path(&g, 0);
    return 0;
}
