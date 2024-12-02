#include <iostream>
#include <set>
#include <queue>

#include "Graph.h"

// breadth first search using while loop and queue
class BFS {
private:
    std::queue<int> queue;
    std::vector<bool> visited;
    std::vector<int> order;

    void run_bfs(Graph graph, int start){        
        // create queue and add first node
        queue.push(start);
        
        while(!queue.empty()){
            int current = queue.front();
            queue.pop();

            // if already visited don't search again
            if(visited[current]) continue;

            visited[current] = true;    // mark as visited (during this round)
            order.push_back(current);

            // if node is null will return an empty set.

            // check through all current's connections
            for(int dest : graph.getEdges(current)){
                // if not yet visited
                if(!visited[dest]){
                    // add to back of queue to later visit
                    queue.push(dest);
                }
            }
        }
    }

public:
    BFS(Graph graph, int startNode){
        // create visited graph
        visited.resize(graph.getGraph().size(), false);
        order.reserve(graph.getGraph().size());     // preallocate for efficiency without setting

        run_bfs(graph, startNode);
    }


    void printOrder(){
        for(int i : order){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }


};