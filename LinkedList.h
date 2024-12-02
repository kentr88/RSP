#include <iostream>

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
    Node * tail;    // store last node for quick insertion
    int size;

public:
    LinkedList(){
        head = nullptr;
        size = 0;
    }

    // insert value at the end of the list
    void insert(int value){
        Node * node = new Node(value);

        // check head
        if(head == nullptr){
            head = node;
            tail = node;
        }

        // use tail to insert
        tail->next = node;
        tail = node;


        size++;
        return;
    }

    // insert value at index
    // if index is larger than the size of the list, insert at the end
    void insertIndex(int index, int value){
        if(index >= size){
            return insert(value);
        }

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

    // delete by searching value
    bool remove(int value){
        if(head == nullptr) return false;

        //first node
        if(head->value == value){
            Node * temp = head->next;
            delete head;
            head = temp;
            return true;
        }

        Node * last = head;
        Node * current = last->next;
        while(current->value != value){
            last = current;
            current = current->next;
            // if last node
            if(current->next == nullptr) return false;
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


    // 
    bool removeIndex(int index){
        if(index >= size) return false;

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
        while(current->next != nullptr){
            if(current->value == value){
                return counter;
            }
            counter++;
        }
        return -1;
    }

    void print(){
        Node * current = head;
        while(current->next != nullptr){
            std::cout << current->value << " ";
        }
    }


};