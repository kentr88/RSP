#include <iostream>
#include <vector>

#include "Graph.h"


// depth first search on prior graph using recursion
class DFS {
private:
    // visit node, go to first child, add to visited, recurse
    // when going back if a child is not in visited, visit and recurse

    std::vector<bool> visited;
    std::vector<int> order;

    void run_dfs(Graph graph, int node){

        visited[node] = true;   // don't need to check if already visited
        order.push_back(node);

        // if node null graph.getEdges() will return a empty set

        // loop through connections
        for(int dest : graph.getEdges(node)){
            // if dest node hasn't already been checked
            if(!visited[dest]){
                // recurse on child
                // giving the result of going down the tree with the first child
                run_dfs(graph, dest);
            }
        }
    }

public:
    DFS(Graph graph, int startNode){
        visited.resize(graph.getGraph().size(), false);
        order.reserve(graph.getGraph().size());

        run_dfs(graph, startNode);
    }

    void printOrder(){
        for(int i : order){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

};