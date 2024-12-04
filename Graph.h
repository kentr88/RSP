#include <iostream>
#include <vector>
#include <set>

// unweighted and bi-directional graph
// nodes and edges can be added and removed
// removed nodes marked as null
// changed list to set for faster duplicate prevention
class Graph {
private:
    // node class stored in vector
    // each node has a linked list for edges, value being the value of the other node
    class Node {
        std::set<int> edges;

    public:
        Node(){}

        bool contains(int dest){
            if(edges.find(dest) != edges.end()) return true;
            return false;
        }

        bool add(int dest){
            std::pair res = edges.insert(dest);
            if(res.second == true) return true;
            return false;
        }

        bool remove(int dest){
            int n = edges.erase(dest);
            if(n == 1) return true;
            return false;
        }

        std::set<int> getEdges(){
            return edges;
        }

        void print(){
            for(int e : edges){
                std::cout << e << " ";
            }
        }
    };

    std::vector<Node*> nodes;
    int size;

public:
    Graph(int startingNodes){
        nodes.resize(startingNodes);
        for(int i = 0; i < startingNodes; i++){
            nodes[i] = new Node();
        }
        size = startingNodes;
    }

    std::vector<Node*> getGraph(){
        return nodes;
    }

    int getNumNodes(){
        return size;
    }

    // return set of edges from node
    // set is sorted in assending order
    // if node doesn't exist returns empty set
    std::set<int> getEdges(int node){
        // if invalid node returns empty set
        if(nodes[node] == nullptr) return std::set<int>();
        return nodes[node]->getEdges();
    }

    // inserts new node and returns index 
    int addNode(){
        nodes.push_back(new Node());
        size ++;
        return (int) nodes.size() - 1;
    }


    // inserts new node at index, making node vector larger
    // returns false if index is negative or node already exists
    bool addNode(int index){
        if(index < 0) return false;
        // check if node already exists - greater than size won't exist
        if(index < (int) nodes.size() && nodes[index] != nullptr) return false;

        // reszie list to include
        nodes.resize(index + 1, nullptr);

        nodes[index] = new Node();
        size++;
        return true;
    }


    // inserts edge from start -> end
    // return false if nodes don't exist or already exists
    bool addEdge(int start, int end){
        // out of bounds
        if(start > (int) nodes.size() - 1 || end > (int) nodes.size() - 1) return false; 
        if(nodes[start] == nullptr || nodes[end] == nullptr) return false;
        if(start == end) return false;

        // already exists
        if(nodes[start]->contains(end) && nodes[end]->contains(start)) return false;

        // add into lists
        nodes[start]->add(end);
        nodes[end]->add(start);

        return true;
    }


    // removes edge from start -> end
    // return false if nodes or edge doesn't exist 
    bool removeEdge(int start, int end){
        // out of bounds
        if(start > (int) nodes.size() - 1 || end > (int) nodes.size() - 1) return false; 
        if(nodes[start] == nullptr || nodes[end] == nullptr) return false;

        // check exists
        if(!(nodes[start]->contains(end) && nodes[end]->contains(start))) return false;

        // remove from lists 
        nodes[start]->remove(end);
        nodes[end]->remove(start);
        return true;
    }

    // removes node at index by setting to null
    // removes all edges connected to node
    bool removeNode(int index){
        if(index > (int) nodes.size() - 1 || nodes[index] == nullptr) return false; 
        
        // attempt to remove all existing edges
        std::set<int> edges = nodes[index]->getEdges();
        for(int e : edges){
            nodes[e]->remove(index);
        }

        // delete
        delete nodes[index];
        nodes[index] = nullptr;
        size--;
        return true;
    }

    // prints each node and adjacency list
    void printGraph(){
        for(int i = 0; i < (int) nodes.size(); i++){
            std::cout << i << ": ";
            nodes[i]->print();
            std::cout << "\n";
        }
    }

};