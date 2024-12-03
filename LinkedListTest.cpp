#include "LinkedList.h"

#include <cassert>
#include <vector>


class LinkedListTest {
private:

    bool checkList(LinkedList& list, std::string expectedList, int expectedLastValue){
        return list.printString() == expectedList && list.tailValue() == expectedLastValue;
    }

    LinkedList createList(std::vector<int> values){
        LinkedList l;
        for(int i = 0; i < values.size(); i++) l.insert(values[i]);
        return l;
    }


    // insert function tests
    void insert(){
        // empty list
        LinkedList l = createList({});
        assert(checkList(l, "", -1));

        // 3 elements
        LinkedList l = createList({5, 6, 2});
        assert(checkList(l, "5 6 2", 2));
    }

    // middle index insertion
    void insertIndex(){
        // bounds check
        LinkedList l = createList({1, 7, 5});
        l.insertIndex(20, 2);  // insert 2 at pos 20
        assert(checkList(l, "1 7 5 2", 2)); // should insert at end of list


        // middle index insertion
        LinkedList l = createList({1, 7, 5});
        // attempt to insert 2 between 1 and 7 at index 1
        l.insertIndex(1, 2);
        assert(checkList(l, "1 2 7 5", 5));

        // start index insertion
        l = createList({1, 7, 5});
        // attempt to insert 3 at index 0
        l.insertIndex(0, 3);
        assert(checkList(l, "3 1 7 5", 5));

        // end index insertion
        l = createList({4, 7, 5});
        l.insertIndex(-1, 10);  // insert 10 a back of list
        assert(checkList(l, "4 7 5 10", 10));
    }



    // remove by value tests
    void remove(){
        // test empty list
        LinkedList l = createList({});
        assert(l.remove(5) == false);
        assert(checkList(l, "", -1));

        // test invalid value
        l = createList({5, 6, 2});
        assert(l.remove(10) == false);
        assert(checkList(l, "5 6 2", 2));

        // remove from middle
        LinkedList l = createList({5, 6, 2});
        assert(l.remove(6) == true);
        assert(checkList(l, "5 2", 2));

        // remove from start
        l = createList({5, 6, 2});
        assert(l.remove(5) == true);
        assert(checkList(l, "6 2", 2));

        // remove from end
        l = createList({5, 6, 2});
        assert(l.remove(2) == true);
        assert(checkList(l, "5 6", 6));
    }


    // remove index test - middle
    void removeIndex(){
        // remove from empty list
        LinkedList l = createList({});
        assert(l.removeIndex(0) == false);
        assert(checkList(l, "", -1));

        // remove from out of bounds index
        l = createList({5, 6, 2});
        assert(l.removeIndex(10) == false);
        assert(checkList(l, "5 6 2", 2));

        // remove from negative index
        l = createList({5, 6, 2});
        assert(l.removeIndex(-1) == false);
        assert(checkList(l, "5 6 2", 2));

        // remove middle index 2 - (2)
        LinkedList l = createList({5, 6, 2, 8});
        assert(l.removeIndex(2) == true);
        assert(checkList(l, "5 6 8", 8));

        // remove first index 0 - (5)
        l = createList({5, 6, 2, 8});
        assert(l.removeIndex(0) == true);
        assert(checkList(l, "6 2 8", 8));

        // remove last index 3 - (8)
        l = createList({5, 6, 2, 8});
        assert(l.removeIndex(3) == true);
        assert(checkList(l, "5 6 2", 2));

    }


    // find test
    void find(){
        LinkedList l = createList({5, 6, 2, 8});
        // l.insert(5);//0
        // l.insert(6);//1
        // l.insert(2);//2
        // l.insert(8);//3

        assert(l.find(6) == 1);
        assert(l.find(8) == 3);
        assert(l.find(5) == 0);
        assert(l.find(2) == 2);
    }


public:
    LinkedListTest(){
        insert();
        insertIndex();
        remove();
        removeIndex();
        find();
    }
};