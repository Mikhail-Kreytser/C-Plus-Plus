//
//      This is the deceleration for the Link_list class. A link_list
//      class has a head pointer and tail pointer. The head pointer
//      points to the first link in the list. The tail pointer points
//      to the last element of the list.
//


#include <iostream>
#include <vector>
#include "node.h"

#ifndef LINKED_LIST_LINKED_LIST_H
#define LINKED_LIST_LINKED_LIST_H


namespace mikhail_kreytser {


    class Link_list{
    public:
        Link_list(int val);
        //  Postcondition   A Link list is created with the first node holding val

        Link_list(Link_list &obj);
        //  Postcondition   A Link list is created with the same information and parameters as obj

        void insert( int val);
        //  Postcondition   val is inserted to the end of the list

        void insert_at( int loc, std::vector<int> &vals );
        //  Precondition    loc must be within the list, vals should have at least one int inside
        //  Postcondition   all the ints inside val are stored starting from loc

        void remove_from( int loc, int amount);
        //  Precondition    loc must be within the list, loc + amount should not extend farther then the last element
        //  Postcondition   "amount" of ints are removed after loc

        int get( int loc);
        //  Precondition    loc must be within the list
        //  Postcondition   int at loc is returned

        friend std::ostream &operator << (std::ostream &os, const Link_list &list);

        ~Link_list();

    private:
        Node * head;
        Node * tail;
    };

    }
#endif //LINKED_LIST_LINKED_LIST_H
