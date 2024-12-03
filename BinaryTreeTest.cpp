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
        BinaryTree tree = BinaryTree({5, 3, 7, 2, 4, 6, 8});
        assert(testTree(tree, "5 3 2 4 7 6 8 "));

        // additonal insertion test
        assert(tree.insert(10) == true);
        assert(testTree(tree, "5 3 2 4 7 6 8 10 "));

        // no duplicates test
        tree = BinaryTree({5, 3, 7, 5});
        assert(testTree(tree, "5 3 7 "));
    }

    // test contains
    void contains(){
        BinaryTree tree;
        // empty tree test
        assert(!tree.contains(5));

        tree = BinaryTree({5, 3, 7, 2, 4, 6, 8});
        // contains
        assert(tree.contains(5));
        assert(tree.contains(3));
        assert(tree.contains(7));
        assert(tree.contains(2));
        assert(tree.contains(4));
        assert(tree.contains(6));
        assert(tree.contains(8));

        // does not contain
        assert(!tree.contains(1));

    }

    // test removal
    void remove(){
        BinaryTree tree;

        // remove empty tree
        assert(tree.remove(5) == false);
        assert(testTree(tree, ""));

        // remove node not in tree
        tree = BinaryTree({5, 3, 7});
        assert(tree.remove(1) == false);
        assert(testTree(tree, "5 3 7 "));

        // remove node with no children
        tree = BinaryTree({5, 3, 7, 2, 4, 6, 8});
        assert(tree.remove(2) == true);
        assert(testTree(tree, "5 3 4 7 6 8 "));

        // remove node with one child
        tree = BinaryTree({5, 3, 7, 2});
        assert(tree.remove(3) == true);
        assert(testTree(tree, "5 2 7 "));

        // remove node with two children
        tree = BinaryTree({5, 3, 2, 4});
        assert(tree.remove(3) == true);
        // gets largest from left subtree, so 3 is replaced with 2
        assert(testTree(tree, "5 2 4 "));

        // remove root from full 3 level tree
        tree = BinaryTree({5, 3, 7, 2, 4, 6, 8});
        assert(tree.remove(5) == true);
        // gets largest from left subtree, so root 5 is replaced with 4
        assert(testTree(tree, "4 3 2 7 6 8 "));

    }

public:
    BinaryTreeTest(){
        insert();
        contains();
        remove();
    }

};
    