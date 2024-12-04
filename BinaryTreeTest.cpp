#include <iostream>
#include <cassert>
#include <vector>

#include "BinaryTree.h"


class BinaryTreeTest {
private:
    // preorder prints self, left then right
    bool testTree(BinaryTree& tree, std::string expectedPreorder){
        std::string preorder = tree.preorderString();
        return preorder == expectedPreorder;
    }

    // test insert
    void insert(){
        // general insertion test
        {
            BinaryTree tree({5, 3, 7, 2, 4, 6, 8});
            assert(testTree(tree, "5 3 2 4 7 6 8 "));
            std::cout << "Test 1 passed" << std::endl;
        }

        // additonal insertion test
        {
            BinaryTree tree({5, 3, 7, 2, 4, 6, 8});
            assert(tree.insert(10) == true);
            assert(testTree(tree, "5 3 2 4 7 6 8 10 "));
            std::cout << "Test 2 passed" << std::endl;
        }

        // no duplicates test
        {
            BinaryTree tree({5, 3, 7, 5});
            assert(testTree(tree, "5 3 7 "));
            std::cout << "Test 3 passed" << std::endl;
        }
    }

    // test contains
    void contains(){
        // empty tree test
        {
            BinaryTree tree;
            assert(!tree.contains(5));
            std::cout << "Test 1 passed" << std::endl;
        }
        
        // check contains all values, 3 level full tree
        {
            BinaryTree tree({5, 3, 7, 2, 4, 6, 8});
            assert(tree.contains(5));
            assert(tree.contains(3));
            assert(tree.contains(7));
            assert(tree.contains(2));
            assert(tree.contains(4));
            assert(tree.contains(6));
            assert(tree.contains(8));

            // correct order
            assert(testTree(tree, "5 3 2 4 7 6 8 "));
            std::cout << "Test 2 passed" << std::endl;

            // does not contain
            assert(!tree.contains(1));
            std::cout << "Test 3 passed" << std::endl;
        }
    }

    // test removal
    void remove(){

        // remove empty tree
        {
            BinaryTree tree;
            assert(tree.remove(5) == false);
            assert(testTree(tree, ""));
            std::cout << "Test 1 passed" << std::endl;
        }

        // remove node not in tree
        {
            BinaryTree tree = BinaryTree({5, 3, 7});
            assert(tree.remove(1) == false);
            assert(testTree(tree, "5 3 7 "));
            std::cout << "Test 2 passed" << std::endl;
        }

        // remove root from 1 node tree, 0 nodes left
        {
            BinaryTree tree({5});
            assert(tree.remove(5) == true);
            assert(testTree(tree, ""));
            std::cout << "Test 3 passed" << std::endl;
        }

        // remove node with no children
        {
            BinaryTree tree({5, 3, 7, 2, 4, 6, 8});
            assert(tree.remove(2) == true);
            assert(testTree(tree, "5 3 4 7 6 8 "));
            std::cout << "Test 4 passed" << std::endl;
        }

        // remove node with one child
        {
            BinaryTree tree({5, 3, 7, 2});
            assert(tree.remove(3) == true);
            assert(testTree(tree, "5 2 7 "));
            std::cout << "Test 5 passed" << std::endl;
        }

        // remove node with two children
        {
            BinaryTree tree({5, 3, 2, 4});
            assert(tree.remove(3) == true);
            // gets largest from left subtree, so 3 is replaced with 2
            assert(testTree(tree, "5 2 4 "));
            std::cout << "Test 6 passed" << std::endl;
        }

        // remove root from full 3 level tree
        {
            BinaryTree tree({5, 3, 7, 2, 4, 6, 8});
            assert(tree.remove(5) == true);
            // gets largest from left subtree, so root 5 is replaced with 4
            assert(testTree(tree, "4 3 2 7 6 8 "));
            std::cout << "Test 7 passed" << std::endl;
        }

    }

public:
    BinaryTreeTest(){
        // BinaryTree tree({5, 3, 7, 2, 4, 6, 8});
        // BinaryTree::Node * current = tree.getRoot();
        // current = current->left;
        // std::cout << current->left << std::endl;
        // std::cout << current->right << std::endl;
        
        // exit(1);

        std::cout << "Running Insert Tests" << std::endl;
        insert();
        std::cout << "\n";
        std::cout << "Running Contains Tests" << std::endl;
        contains();
        std::cout << "\n";
        std::cout << "Running Remove Tests" << std::endl;
        remove();
        std::cout << "\n";
        std::cout << "Finished" << std::endl;
    }
};


int main(){
    BinaryTreeTest t;
    return 0;
}
    