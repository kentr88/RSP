#include <iostream>
#include <cassert>

#include "BFS.h"


class BFSTest {
private:
    // Simple square graph cycle
    void simpleSquare(){
        Graph graph(4);
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 3);
        
        {
            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0, 1, 2, 3}));
            std::cout << "Passed Test 1\n";
        }

        {
            BFS bfs(graph, 1);
            assert(bfs.getOrder() == std::vector<int>({1, 0, 3, 2}));
            std::cout << "Passed Test 2\n";
        }
    }

    void invalidGraphs(){
        // single node
        {
            Graph graph(1);
            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0}));
            std::cout << "Passed Test 1\n";
        }

        // no edges
        {
            Graph graph(4);
            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0}));
            std::cout << "Passed Test 2\n";
        }

        // empty graph
        {
            Graph graph(0);
            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({}));
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


            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7}));
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

            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0, 1, 2, 3, 4, 5}));
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

            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0, 1, 4, 2, 3}));
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

            BFS bfs(graph, 0);
            assert(bfs.getOrder() == std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8}));
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

        BFS bfs(graph, 0);
        assert(bfs.getOrder() == std::vector<int>({0, 1, 2}));
        std::cout << "Passed Test 1\n";

        BFS bfs2(graph, 3);
        assert(bfs2.getOrder() == std::vector<int>({3, 4, 5}));
        std::cout << "Passed Test 2\n";
    }

    // other example 1

public:
    BFSTest(){
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
    BFSTest test;
    return 0;
}