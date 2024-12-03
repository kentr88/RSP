#include <iostream>
#include <string>
#include <vector>


class BinaryTree {
private:
    class Node {
    public:
        int value;
        Node * left = nullptr;
        Node * right = nullptr;

        Node(int value){
            this->value = value;
        }
    };

    Node * root = nullptr;
    std::string inorderText;
    std::string preorderText;
    std::string postorderText;

    void inorder(Node * node){
        if(node == nullptr) return;
        // recurse left
        inorder(node->left);        
        // print self
        std::cout << node->value << " ";
        // recurse right
        inorder(node->right);
    }

    void preorder(Node * node){
        if(node == nullptr) return;
        // print
        std::cout << node->value << " ";
        // left
        preorder(node->left);
        // right
        preorder(node->right);
    }

    void postorder(Node * node){
        if(node == nullptr) return;
        // left
        postorder(node->left);
        // right
        postorder(node->right);
        // print
        std::cout << node->value << " ";
    }

    void inorderString(Node * node){
        if(node == nullptr) return;
        // recurse left
        inorderString(node->left);        
        // print self
        inorderText += node->value + " ";
        // recurse right
        inorderString(node->right);
    }

    void preorderString(Node * node){
        if(node == nullptr) return;
        // print
        preorderText += node->value + " ";
        // left
        preorderString(node->left);
        // right
        preorderString(node->right);
    }

    void postorderString(Node * node){
        if(node == nullptr) return;
        // left
        postorderString(node->left);
        // right
        postorderString(node->right);
        // print
        postorderText += node->value + " ";
    }

    void deleteNode(Node * node){
        if(node == nullptr) return;
        // recurse left then right side
        deleteNode(node->left);
        deleteNode(node->right);
        // delete self when finished
        delete node;
    }

public:
    // create empty tree
    BinaryTree(){}

    // create tree inserting values in order from vector
    BinaryTree(std::vector<int> values){
        for(int i = 0; i < values.size(); i++){
            insert(values[i]);
        }
    }


    bool insert(int value){
        if(root == nullptr){
            root = new Node(value);
            return true;
        }

        // traverse tree
        Node * current = root;
        
        while(true){
            if(value == root->value){
                // fail
                return false;
            } else if(value > root->value){
                //right
                if(current->right == nullptr){
                    // insert
                    current->right = new Node(value);
                    return true;
                } else {
                    current = current->right;
                }
            } else {
                // left
                if(current->left == nullptr){
                    // insert
                    current->left = new Node(value);
                    return true;
                } else {
                    current = current->left;
                }
            }
        }


    }

    // 
    bool contains(int value){
        if(root == nullptr) return false;
        Node * current = root;
        while(true){
            if(current->value == value) return true;

            if(current->value > value){
                if(current->right == nullptr) return false;
                current = current->right;
            }

            if(current->value < value){
                if(current->left == nullptr) return false;
                current = current->left;
            }
        }
    }


    bool remove(int value){
        if(root == nullptr) return false;

        // remove root exception
        if(root->value == value){
            // find rightmost in left

        }
        
        // find value
        Node * parent = nullptr;
        Node * current = root;
        bool right = false;     // last direction
        while(true){
            if(current->value == value){
                break;
            }

            // right
            if(current->value > value){
                if(current->right == nullptr) return false; // couldn't be found
                parent = current;
                current = current->right;
                right = true;
            }

            // left
            if(current->value < value){
                if(current->left == nullptr) return false;  // couldn't be found
                parent = current;
                current = current->left;
                right = false;
            }
        }

        // check number of children
        if(current->left == nullptr && current->right == nullptr){
            // no children, only delete from parent
            if(right) parent->right = nullptr;
            else parent->left = nullptr;
            delete current;
            return true;
        }


        // 1 child
        if(current->left == nullptr || current->right == nullptr){
            // move child to replace in parent

            // get current's only child
            Node * child;
            if(current->left != nullptr) child = current->left;
            else child = current->right;

            // add to parent
            if(right) parent->right = child;
            else parent->left = child;

            // delete
            delete current;
            return true;          
        }

        // two nodes, replace with largest/smallest on that side
        // look for rightmost in left subtree
        Node * temp = current->left;    // go into left tree
        Node * tempParent = current;
        // keep going right
        while(temp->right != nullptr){
            tempParent = temp;
            temp = temp->right;
        }

        // move temp up to origional node
        if(right) parent->right = temp;
        else parent->left = temp;

        // fix up temp leafs
        tempParent->right = temp->left; //if temp had a left node

        // fix current's leafs
        temp->left = current->left;
        temp->right = current->right;

        delete current;
        return true;
    }

    
    void inorder(){
        if(root != nullptr) inorder(root);
    }
   

    void preorder(){
        if(root != nullptr) preorder(root);
    }

    void postorder(){
        if(root != nullptr) postorder(root);
    }

    std::string inorderString(){
        inorderText = "";
        if(root != nullptr) inorderString(root);
        return inorderText;
    }
   

    std::string preorderString(){
        preorderText = "";
        if(root != nullptr) preorderString(root);
        return preorderText;
    }

    std::string postorderString(){
        postorderText = "";
        if(root != nullptr) postorderString(root);
        return postorderText;
    }


    ~BinaryTree(){
        // traverse and delete all nodes
        deleteNode(root);
    }

};