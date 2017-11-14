#include <iostream>
#include <ctime>
#include "graph.h"

int main()
{
    graph G = graph();
    G.makeGraph();
    clock_t t1 = clock();
    G.dijkstra();
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << "\n";
    G.output();
    return 0;
}