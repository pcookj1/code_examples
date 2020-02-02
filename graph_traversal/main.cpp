/*========================================================
* Winter 2019 - Patrick Cook
* Breadth First Traversal for a simple, undirected graph
========================================================*/

#include "graph.hpp"

int main() {
    // Construct simple, undirected graph with 10 vertices
    Graph G(10);
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(0,3);
    G.addEdge(1,7);
    G.addEdge(1,6);
    G.addEdge(1,5);
    G.addEdge(2,8);
    G.addEdge(2,7);
    G.addEdge(2,9);
    G.printBFS(0);
    G.printBFS(3);
}
