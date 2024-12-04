#include <iostream>
#include <cassert>

#include "DFS.h"


class DFSTest {
private:
    // Simple square graph cycle
    void simpleSquare(){
        Graph graph(4);
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 3);
        
        {
            DFS dfs(graph, 0);
            assert(dfs.getOrder() == std::vector<int>({0, 1, 3, 2}));
            std::cout << "Passed Test 1\n";
        }

        {
            DFS dfs(graph, 1);
            assert(dfs.getOrder() == std::vector<int>({1, 0, 2, 3}));
            std::cout << "Passed Test 2\n";
        }
    }

    void invalidGraphs(){
        // single node
        {
            Graph graph(1);
            DFS dfs(graph, 0);
            assert(dfs.getOrder() == std::vector<int>({0}));
            std::cout << "Passed Test 1\n";
        }

        // no edges
        {
            Graph graph(4);
            DFS dfs(graph, 0);
            assert(dfs.getOrder() == std::vector<int>({0}));
            std::cout << "Passed Test 2\n";
        }

        // empty graph
        {
            Graph graph(0);
            DFS dfs(graph, 0);
            assert(dfs.getOrder() == std::vector<int>({}));
            std::cout << "Passed Test 3\n";
        }
    }



    // tree with child having more than one parent
    void tree(){
        // bst type
        {
            Graph graph(8);
            // first layer
            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            // second layer
            graph.addEdge(1, 3);
            graph.addEdge(1, 4);
            graph.addEdge(1, 5);
            graph.addEdge(2, 6);
            graph.addEdge(2, 7);


            DFS dfs(graph, 0);
            assert(dfs.getOrder() == std::vector<int>({0, 1, 3, 4, 5, 2, 6, 7}));
            std::cout << "Passed Test 1\n";
        }

        // tree with child having more than one parent
        {
            Graph graph(6);
            // fist layer
            graph.addEdge(0, 1); 
            graph.addEdge(0, 2);
            graph.addEdge(0, 3);
            // second layer
            graph.addEdge(1, 4);
            graph.addEdge(2, 4);
            graph.addEdge(2, 5);
            // node 4 has two parents, 1 and 2

            DFS dfs(graph, 0);
            assert(dfs.getOrder() == std::vector<int>({0, 1, 4, 2, 5, 3}));
            std::cout << "Passed Test 2\n";
        }
    }


    // graph with internal cycles
    void cycle(){
        // triangle connected to square with diagional shape
        {
            Graph graph(5);
            // triangle
            graph.addEdge(0, 1);
            graph.addEdge(0, 4);
            graph.addEdge(1, 4);
            // square
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);
            graph.addEdge(3, 4);
            graph.addEdge(1, 3);//diagonal

            // chooses based on assending order of connection destination
            DFS dfs(graph, 0);
            // 0-1-2-3-4
            assert(dfs.getOrder() == std::vector<int>({0, 1, 2, 3, 4}));
            std::cout << "Passed Test 1\n";
        }

        // larger tree like cycle
        {
            Graph graph(9);
            // first layer
            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            graph.addEdge(0, 3);
            // connecting - all nodes in this layer are connected
            graph.addEdge(1, 2);
            graph.addEdge(2, 3);
            // second layer
            graph.addEdge(1, 4);
            graph.addEdge(2, 5);
            graph.addEdge(3, 6);
            // third layer
            graph.addEdge(4, 7);
            graph.addEdge(5, 7);
            graph.addEdge(5, 8);
            // node 7 has two parents, 4 and 5 creating a loop with 1 and 2

            DFS dfs(graph, 0);

            //due to choosing direction based on assending order, node 1 will go to node 2 then 3, before going to other child 4
            // first line, 0-1-2-3-6, then using 2's other child 5, 5-7-4, then 8
            assert(dfs.getOrder() == std::vector<int>({0, 1, 2, 3, 6, 5, 7, 4, 8}));
            std::cout << "Passed Test 2\n";
        }
    }


    // disconnected graph or 2 separate graphs
    void disconnected(){
        Graph graph(6);
        // first graph triangle
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 2);

        // second graph line of nodes
        graph.addEdge(3, 4);
        graph.addEdge(4, 5);

        DFS dfs(graph, 0);
        assert(dfs.getOrder() == std::vector<int>({0, 1, 2}));
        std::cout << "Passed Test 1\n";

        DFS dfs2(graph, 3);
        assert(dfs2.getOrder() == std::vector<int>({3, 4, 5}));
        std::cout << "Passed Test 2\n";
    }

    // other example 1

public:
    DFSTest(){
        std::cout << "Running square test\n";
        simpleSquare();
        std::cout << "\n";
        std::cout << "Running invalid tests\n";
        invalidGraphs();
        std::cout << "\n";
        std::cout << "Running tree test\n";
        tree();
        std::cout << "\n";
        std::cout << "Running cycle test\n";
        cycle();
        std::cout << "\n";
        std::cout << "Running disconnected test\n";
        disconnected();
        std::cout << "\n";
    }
};


int main(){
    DFSTest test;
    return 0;
}