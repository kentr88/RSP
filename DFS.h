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

    // will start at node and continuously choose the first child until it hits a dead end
    // then goes back to last node with an unvisited child and repeats
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
    // takes graph type and index of node to start the search at.
    DFS(Graph graph, int startNode){
        visited.resize(graph.getGraph().size(), false);
        order.reserve(graph.getGraph().size());

        // empty graph
        if(graph.getGraph().size() == 0) return;
        run_dfs(graph, startNode);
    }

    // print saved traversal order
    void printOrder(){
        for(int i : order){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    // get saved traversal order for checking
    std::vector<int> getOrder(){
        return order;
    }

};