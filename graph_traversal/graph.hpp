/* =======================================================
*  Winter 2019 - Patrick Cook
*  Interace for undirected graph related classes and methods
========================================================*/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>

using namespace std;

class Graph {
    int V;
    list<int> *adj; // list of adjacent nodes

    public:
        Graph(int numV);
        void addEdge(int v, int w);
        void printBFS(int root);
        //void printDFS(int root); future implementation
};

#endif


