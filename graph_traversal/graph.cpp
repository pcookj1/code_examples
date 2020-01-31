/*  Winter 2019 - Patrick Cook
    Implementation for graph traversal methods (Breadth first search)

    Print breadth-first search starting from select root
    # start at root
    # visit children of root
    # visit children of children
*/

#include "graph.hpp"
#include <list>
#include <iostream> 

Graph::Graph(int numV) {
    V=numV;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// Print breadth-first search starting from select root
void Graph::printBFS(int root) {
    bool *visited = new bool[V];
    for(int i=0; i<V; i++)
        visited[i] = false;
    
    // Queue of vertices to traverse
    list<int> queue;
    visited[root] = true;
    queue.push_back(root);
    
    list<int>::iterator i;
    std::cout << "Breadth-First Traversal" << "\n";
    while(!queue.empty()) {
        root = queue.front();
        std::cout << root << " ";
        queue.pop_front();
        // Iterate through children of current root
        for(i=adj[root].begin(); i!=adj[root].end(); ++i) {
            if(visited[*i] == false) {
                visited[*i] = true;   
                queue.push_back(*i);
            }
        }
    }
    std::cout << "\n";
}
void Graph::printDFS(int root) {

}
