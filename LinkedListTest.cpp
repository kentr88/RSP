#include "LinkedList.h"

#include <cassert>
#include <vector>


class LinkedListTest {
private:

    bool checkList(LinkedList& list, std::string expectedList, int expectedLastValue){
        return list.getValues() == expectedList && list.tailValue() == expectedLastValue;
    }



    // insert function tests
    void insert(){
        // empty list
        {
            LinkedList l = LinkedList();
            assert(checkList(l, "", -1));
            std::cout << "test 1 passed" << std::endl;
        }

        {
            // 3 elements
            LinkedList l = LinkedList({5, 6, 2, 1});
            assert(checkList(l, "5 6 2 1 ", 1));
            std::cout << "test 2 passed" << std::endl;
        }
    }

    // middle index insertion
    void insertIndex(){
        std::cout << "insertIndex tests" << std::endl;
        
        // bounds check
        { 
            LinkedList l = LinkedList({1, 7, 5});
            l.insertIndex(20, 2);  // insert 2 at pos 20
            assert(checkList(l, "1 7 5 2 ", 2)); // should insert at end of list
            std::cout << "test 1 passed" << std::endl;
        }


        // middle index insertion
        {
            LinkedList l = LinkedList({1, 7, 5});
            // attempt to insert 2 between 1 and 7 at index 1
            l.insertIndex(1, 2);
            assert(checkList(l, "1 2 7 5 ", 5));
            std::cout << "test 2 passed" << std::endl;
        }

        // start index insertion
        {
            LinkedList l = LinkedList({1, 7, 5});
            // attempt to insert 3 at index 0
            l.insertIndex(0, 3);
            assert(checkList(l, "3 1 7 5 ", 5));
            std::cout << "test 3 passed" << std::endl;
        }

        // end index insertion
        {
            LinkedList l = LinkedList({4, 7, 5});
            l.insertIndex(-1, 10);  // insert 10 a back of list
            assert(checkList(l, "4 7 5 10 ", 10));
            std::cout << "test 4 passed" << std::endl;
        }
    }



    // remove by value tests
    void remove(){
        // test empty list
        {
            LinkedList l = LinkedList();
            assert(l.remove(5) == false);
            assert(checkList(l, "", -1));
            std::cout << "test 1 passed" << std::endl;
        }

        // test invalid value
        {
            LinkedList l = LinkedList({5, 6, 2});
            assert(l.remove(10) == false);
            assert(checkList(l, "5 6 2 ", 2));
            std::cout << "test 2 passed" << std::endl;
        }

        // remove from middle
        {
            LinkedList l = LinkedList({5, 6, 2});
            assert(l.remove(6) == true);
            assert(checkList(l, "5 2 ", 2));
            std::cout << "test 3 passed" << std::endl;
        }

        // remove from start
        {
            LinkedList l = LinkedList({5, 6, 2});
            assert(l.remove(5) == true);
            assert(checkList(l, "6 2 ", 2));
            std::cout << "test 4 passed" << std::endl;
        }

        // remove from end
        {
            LinkedList l = LinkedList({5, 6, 2});
            assert(l.remove(2) == true);
            assert(checkList(l, "5 6 ", 6));
            std::cout << "test 5 passed" << std::endl;
        }
    }


    // remove index test - middle
    void removeIndex(){
        // remove from empty list
        {
            LinkedList l = LinkedList();
            assert(l.removeIndex(0) == false);
            assert(checkList(l, "", -1));
            std::cout << "test 1 passed" << std::endl;
        }

        // remove from out of bounds index
        {
            LinkedList l = LinkedList({5, 6, 2});
            assert(l.removeIndex(10) == false);
            assert(checkList(l, "5 6 2 ", 2));
            std::cout << "test 2 passed" << std::endl;
        }

        // remove from negative index
        {
            LinkedList l = LinkedList({5, 6, 2});
            assert(l.removeIndex(-1) == false);
            assert(checkList(l, "5 6 2 ", 2));
            std::cout << "test 3 passed" << std::endl;
        }

        // remove middle index 2 - (2)
        {
            LinkedList l = LinkedList({5, 6, 2, 8});
            assert(l.removeIndex(2) == true);
            assert(checkList(l, "5 6 8 ", 8));
            std::cout << "test 4 passed" << std::endl;
        }

        // remove first index 0 - (5)
        {
            LinkedList l = LinkedList({5, 6, 2, 8});
            assert(l.removeIndex(0) == true);
            assert(checkList(l, "6 2 8 ", 8));
            std::cout << "test 5 passed" << std::endl;
        }

        // remove last index 3 - (8)
        {
            LinkedList l = LinkedList({5, 6, 2, 8});
            assert(l.removeIndex(3) == true);
            assert(checkList(l, "5 6 2 ", 2));
            std::cout << "test 6 passed" << std::endl;
        }

    }


    // find test
    void find(){
        LinkedList l = LinkedList({5, 6, 2, 8});
        // l.insert(5);//0
        // l.insert(6);//1
        // l.insert(2);//2
        // l.insert(8);//3

        assert(l.find(6) == 1);
        assert(l.find(8) == 3);
        assert(l.find(5) == 0);
        assert(l.find(2) == 2);
        std::cout << "test 1 passed" << std::endl;
    }


public:
    LinkedListTest(){
        std::cout << "Running LinkedList Tests" << std::endl;
        insert();
        std::cout << "\n";
        std::cout << "Running InsertIndex Tests" << std::endl;
        insertIndex();
        std::cout << "\n";
        std::cout << "Running Remove Tests" << std::endl;
        remove();
        std::cout << "\n";
        std::cout << "Running RemoveIndex Tests" << std::endl;
        removeIndex();
        std::cout << "\n";
        std::cout << "Running Find Tests" << std::endl;
        find();
        std::cout << "\n";
        std::cout << "Finished" << std::endl;
    }

};


int main(){
    LinkedListTest l;
    return 0;
}