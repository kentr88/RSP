#include <iostream>
#include <string>
#include <vector>


class BinaryTree {
public:
    class Node {
    public:
        int value;
        Node * left = nullptr;
        Node * right = nullptr;

        Node(int value){
            this->value = value;
        }
    };

private:
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
        inorderText += std::to_string(node->value) + " ";
        // recurse right
        inorderString(node->right);
    }

    void preorderString(Node * node){
        if(node == nullptr) return;
        // print
        preorderText += std::to_string(node->value) + " ";
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
        postorderText += std::to_string(node->value) + " ";
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

    Node * getRoot(){
        return root;
    }

    // create tree inserting values in order from vector
    BinaryTree(std::vector<int> values){
        for(int i = 0; i < (int) values.size(); i++){
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
            if(value == current->value){
                // fail
                return false;
            } else if(value > current->value){
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
        while(current != nullptr){
            if(value == current->value){
                return true;
            } else if(value > current->value){
                current = current->right;
            } else if(value < current->value){
                current = current->left;
            }
        }
        return false;
    }


    bool remove(int value){
        if(root == nullptr) return false;

         // find value
        Node * parent = nullptr;
        Node * current = root;
        bool right = false;     // last direction
        bool isRoot = false;

        // remove root exception
        if(root->value == value) isRoot = true;
       
        while(current != nullptr && isRoot == false){
            if(current->value == value){
                break;
            } else if(value > current->value){
                // right
                parent = current;
                current = current->right;
                right = true;
            } else if(value < current->value){
                // left
                parent = current;
                current = current->left;
                right = false;
            }
        }

        // not found
        if(current == nullptr) return false;

        // check number of children //

        // no children
        if(current->left == nullptr && current->right == nullptr){
            // root node
            if(isRoot){
                delete root;
                root = nullptr;
                return true;
            }

            // no children, only delete from parent
            if(right) parent->right = nullptr;
            else parent->left = nullptr;
            delete current;
            return true;
        }


        // 1 child
        if(current->left == nullptr || current->right == nullptr){
            // get current's only child
            Node * child;
            if(current->left != nullptr) child = current->left;
            else child = current->right;

            // add to parent
            if(isRoot){
                // most likely 2 node tree 
                root = child;
            } else {
                if(right) parent->right = child;
                else parent->left = child;
            }

            // delete
            delete current;
            return true;          
        }

        // two children, replace with largest/smallest on that side
        // look for rightmost in left subtree
        Node * tempParent = current;
        Node * temp = current->left;    // go into left tree
        // keep going right
        while(temp->right != nullptr){
            tempParent = temp;
            temp = temp->right;
        }

        // fix temp's parent
        // if temp had a left node, or could just be nullptr
        if(tempParent != current) tempParent->right = temp->left; 
        else tempParent->left = temp->left; // if temp was left child of current

        // if root node or has a parent
        if(isRoot){
            root = temp;
        } else {
            // move temp up to origional node
            if(right) parent->right = temp;
            else parent->left = temp;
        }


        // fix current/root children
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