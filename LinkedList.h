#include <iostream>
#include <string>
#include <vector>

class LinkedList {
private:
    class Node {
    public:
        int value;
        Node * next;

        Node(int value){
            this->value = value;
            this->next = nullptr;
        }
    };

    Node * head;
    Node * tail;    // store last node for quick back insertion
    int size;

public:
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // constructor that accepts a vector of values
    LinkedList(std::vector<int> values) : LinkedList() {
        // insert values in order
        for(int i = 0; i < (int) values.size(); i++){
            insert(values[i]);
        }
    }

    // insert value at the end of the list
    void insert(int value){
        Node * node = new Node(value);

        // check head
        if(head == nullptr){
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }       

        size++;
        return;
    }

    // insert value at index
    // if index is larger than the size of the list, insert at the end
    void insertIndex(int index, int value){
        if(index >= size){
            return insert(value);
        }

        if(index == -1) return insert(value);   // end of list
        if(index < -1) return;  // invalid index

        Node * node = new Node(value);

        if(index == 0){
            // first
            node->next = head;
            head = node;
            return;
        } 

        Node * last = head;
        for(int i = 1; i < index; i++){
            Node * temp = last->next;
            last = temp;
        }

        node->next = last->next;
        last->next = node;
    }

    // delete by searching for value
    bool remove(int value){
        if(head == nullptr) return false;

        //first node
        if(head->value == value){
            Node * temp = head->next;
            delete head;
            head = temp;
            if(head == nullptr) tail = nullptr;
            return true;
        }

        Node * last = head;
        Node * current = last->next;
        while(current->value != value){
            last = current;
            current = current->next;
            // if last node
            if(current == nullptr) return false;
        }

        // last node
        if(current->next == nullptr){
            delete current;
            last->next = nullptr;
            tail = last;
            return true;
        }

        // middle 
        last->next = current->next;
        delete current;
        return true;        
    }


    // remove certain index in tree
    // return false if index is out of bounds
    bool removeIndex(int index){
        if(index >= size) return false;
        if(index < 0) return false;

        if(index == 0){
            Node * temp = head->next;
            delete head;
            head = temp;
            return true;
        }

        Node * previous = head;
        Node * current = head->next;

        for(int i = 1; i < index; i++){
            previous = current;
            current = current->next;
        }

        // last node
        if(current->next == nullptr){
            previous->next = nullptr;//
            tail = previous;
            delete current;//
            return true;//remove
        }

        previous->next = current->next;
        delete current;
        return true;
    }

    // return index of value (first)
    // return -1 if value is not found
    int find(int value){
        Node * current = head;
        int counter = 0;
        while(current != nullptr){
            if(current->value == value){
                return counter;
            }
            counter++;
            current = current->next;
        }
        return -1;
    }

    // print to console
    void print(){
        if(head == nullptr) return;
        Node * current = head;
        while(current != nullptr){
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    // return string of values
    // in format a b c d (with a space on the end)
    std::string getValues(){
        if(head == nullptr) return "";
        Node * current = head;
        std::string s;

        while(current != nullptr){
            s += std::to_string(current->value) + " ";
            current = current->next;
        }
        return s;
    }

    // return last value in list
    int tailValue(){
        if(tail == nullptr) return -1;
        return tail->value;
    }


    ~LinkedList(){
        // delete all nodes (heap allocated)
        Node * current = head;
        while(current != nullptr){
            Node * next = current->next;
            delete current;
            current = next;
        }
    }

};