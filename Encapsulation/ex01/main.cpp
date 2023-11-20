#include "Graph.hpp"

int main()
{
    Graph graph;

    graph.addPoint(0, 0);
    graph.addPoint(2, 2);
    graph.addPoint(4, 2);
    graph.addPoint(2, 4);
    // graph.addPoint(1.2, 1.2);
    // graph.addPoint(1.5, 1.5);
    // graph.addPoint(0, 3);
    // graph.addPoint(15, 3);
    // graph.addPoint(0, 0);
    // graph.addPoint(7, 7);
    // graph.addPoint(8, 8);
    // graph.addPoint(9, 9);

    graph.printGraph();
}