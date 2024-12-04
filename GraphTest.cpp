#include <iostream>
#include <cassert>
#include <vector>

#include "Graph.h"

class GraphTest {
private:

    void addNode(){
        // add node to empty graph
        {
            Graph graph(0);
            assert(graph.addNode() == 0);
            assert(graph.getNumNodes() == 1);
            std::cout << "Test 1 passed" << std::endl;
        }

        // add node to non-empty graph
        {
            Graph graph(3);
            assert(graph.getNumNodes() == 3);   // check has nodes
            assert(graph.addNode() == 3);       // add node at index 3
            assert(graph.getNumNodes() == 4);
            std::cout << "Test 2 passed" << std::endl;
        }

        // multiple add node
        {
            Graph graph(3);
            assert(graph.addNode() == 3);
            assert(graph.addNode() == 4);
            assert(graph.addNode() == 5);
            assert(graph.getNumNodes() == 6);
            std::cout << "Test 3 passed" << std::endl;
        }   
    }

    void addNodeIndex(){
        // insert into empty graph
        {
            Graph graph(0);
            assert(graph.addNode(0) == true);
            assert(graph.getNumNodes() == 1);
            std::cout << "Test 1 passed" << std::endl;
        }

        // insert into non-empty graph
        {
            Graph graph(3);
            assert(graph.addNode(3) == true);
            assert(graph.getNumNodes() == 4);
            std::cout << "Test 2 passed" << std::endl;
        }

        // fails when index is out of bounds or already exists
        // next test is index past graph - graph grows to include
        {
            // node already exists there
            Graph graph(3);
            assert(graph.addNode(1) == false);
            assert(graph.getNumNodes() == 3);
            // index out of bounds < 0
            assert(graph.addNode(-1) == false);
            assert(graph.getNumNodes() == 3);
            std::cout << "Test 3 passed" << std::endl;
        }

        // insert after main graph
        {
            Graph graph(4);
            assert(graph.addNode(8) == true);
            //size should be 9, but num nodes is 5
            assert(graph.getNumNodes() == 5);
            assert(graph.getGraph().size() == 9);
            std::cout << "Test 4 passed" << std::endl;
        }
    }

    void addEdge(){
        // add edge to empty graph
        {
            Graph graph(0);
            assert(graph.addEdge(0, 1) == false);
            std::cout << "Test 1 passed" << std::endl;
        }

        // invalid indicies
        {
            Graph graph(3); // indicies 0, 1, 2
            assert(graph.addEdge(5, 4) == false);   //both
            assert(graph.addEdge(1, 4) == false);   //1
            assert(graph.addEdge(4, 1) == false);   //other
            assert(graph.addEdge(1, 1) == false);   //same
            std::cout << "Test 2 passed" << std::endl;
        }

        // add edge to graph
        {
            Graph graph(3);
            assert(graph.addEdge(0, 1) == true);
            // use count to see how many times number appears
            assert(graph.getEdges(0).count(1) == 1);    
            assert(graph.getEdges(1).count(0) == 1);
            assert(graph.getEdges(2).count(0) == 0);
            assert(graph.getEdges(2).count(1) == 0);
            std::cout << "Test 3 passed" << std::endl;
        }

        // try to add edge twice
        {
            Graph graph(3);
            assert(graph.addEdge(0, 1) == true);
            assert(graph.addEdge(0, 1) == false);
            std::cout << "Test 4 passed" << std::endl;
        }

        // attempt to add edge to deleted node
        {
            Graph graph(3);
            assert(graph.removeNode(1) == true);
            assert(graph.addEdge(0, 1) == false);
            std::cout << "Test 5 passed" << std::endl;
        }

        // create strongly connected graph
        {
            Graph graph(3);
            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            graph.addEdge(1, 2);
            // check all edges
            assert(graph.getEdges(0).count(1) == 1);
            assert(graph.getEdges(0).count(2) == 1);
            assert(graph.getEdges(1).count(0) == 1);
            assert(graph.getEdges(1).count(2) == 1);
            assert(graph.getEdges(2).count(0) == 1);
            assert(graph.getEdges(2).count(1) == 1);
            std::cout << "Test 6 passed" << std::endl;
        }
    }

    void removeEdge(){
        // remove edge from empty graph
        {
            Graph graph(0);
            assert(graph.removeEdge(0, 1) == false);
            std::cout << "Test 1 passed" << std::endl;
        }

        // remove non existant edge
        {
            Graph graph(3);
            assert(graph.removeEdge(0, 1) == false);
            std::cout << "Test 2 passed" << std::endl;
        }

        // remove non existant edge 2
        {
            Graph graph(3);
            graph.addEdge(0, 1);
            assert(graph.removeEdge(1, 2) == false);
            std::cout << "Test 3 passed" << std::endl;
        }

        // remove edge
        {
            Graph graph(3);
            assert(graph.addEdge(0, 1) == true);
            assert(graph.removeEdge(0, 1) == true);
            // check removed
            assert(graph.getEdges(0).count(1) == 0);
            assert(graph.getEdges(1).count(0) == 0);
            std::cout << "Test 4 passed" << std::endl;
        }

        // remove edge with multiple edges
        {
            Graph graph(3);
            assert(graph.addEdge(0, 1) == true);
            assert(graph.addEdge(0, 2) == true);
            assert(graph.removeEdge(0, 1) == true);

            // check removed
            assert(graph.getEdges(0).count(1) == 0);
            assert(graph.getEdges(1).count(0) == 0);
            // check other edge
            assert(graph.getEdges(0).count(2) == 1);
            assert(graph.getEdges(2).count(0) == 1);
            std::cout << "Test 5 passed" << std::endl;
        }
    }

    void removeNode(){
        // remove node from empty graph
        {
            Graph graph(0);
            assert(graph.removeNode(0) == false);
            std::cout << "Test 1 passed" << std::endl;
        }

        // remove non existant node
        {
            Graph graph(3);
            assert(graph.removeNode(4) == false);
            std::cout << "Test 2 passed" << std::endl;
        }

        // remove node no edges
        {
            Graph graph(3);
            assert(graph.removeNode(1) == true);
            assert(graph.getNumNodes() == 2);
            assert(graph.getGraph().size() == 3);
            std::cout << "Test 3 passed" << std::endl;
        }

        // remove node with edges
        {
            Graph graph(3);
            // fully connected graph
            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            graph.addEdge(1, 2);
            // remove node 0, 
            assert(graph.removeNode(0) == true);
            assert(graph.getNumNodes() == 2);
            assert(graph.getGraph().size() == 3);
            // deletes edges 0-1 and 0-2 not 1-2
            assert(graph.getEdges(1).count(0) == 0);
            assert(graph.getEdges(2).count(0) == 0);
            assert(graph.getEdges(1).count(2) == 1);
            assert(graph.getEdges(2).count(1) == 1);
            std::cout << "Test 4 passed" << std::endl;
        }

        // add node with gap due to deleted node
        {
            Graph graph(3);
            graph.removeNode(1);    // remove node at index 1
            assert(graph.addNode() == 3);       // would be inserting at end, index 3
            assert(graph.getNumNodes() == 3);
            assert(graph.getGraph().size() == 4);   // check gap exists
            std::cout << "Test 5 passed" << std::endl;
        } 
    }


public:
    GraphTest(){
        std::cout << "Running Add Node Tests" << std::endl;
        addNode();
        std::cout << "\n";
        std::cout << "Running Add Node Index Tests" << std::endl;
        addNodeIndex();
        std::cout << "\n";
        std::cout << "Running Add Edge Tests" << std::endl;
        addEdge();
        std::cout << "\n";
        std::cout << "Running Remove Edge Tests" << std::endl;
        removeEdge();
        std::cout << "\n";
        std::cout << "Running Remove Node Tests" << std::endl;
        removeNode();
        std::cout << "\n";
        std::cout << "Finished" << std::endl;
    }
};


int main(){
    GraphTest t;
    return 0;
}