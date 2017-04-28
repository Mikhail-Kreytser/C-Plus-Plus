//
//      This is the deceleration for the double-ended queue (DEQUE). The DEQUE
//      stores ints in nodes (by default). Although this is not a template class
//      I made it very easy to change the type that is stored. The type can be
//      changed by modifying line 18. (IF CHANGED: please also edit deque.cpp,
//      node.h and node.cpp). You can add to the front of the queue as well as
//      the back. You can also remove from the front and remove from the
//      back. I also added a ostream function to display the queue.
//

#include "node.h"
#include <iostream>
#ifndef LINKED_LIST_DEQUE_H
#define LINKED_LIST_DEQUE_H

namespace mikhail_kreytser {

    typedef int T;

    class Deque {
    public:
        Deque(T val);
        //  Precondition    The data in all nodes should be the same type
        //  Postcondition   A node with the data val is added to the end of the queue

        void add_rear(T val);
        //  Precondition    The data in all nodes should be the same type
        //  Postcondition   A node with the data val is added to the front of the queue

        void add_front(T val);
        //  Precondition    The data in all nodes should be the same type
        //  Postcondition   A node with the data val is added to the front of the queue

        void remove_rear();
        //  Precondition    There should be two or more nodes
        //  Postcondition   The node at the end of the queue is removed

        void remove_front();
        //  Precondition    There should be two or more nodes
        //  Postcondition   The node at the front of the queue is removed

        T get_front();
        //  Precondition    There should be one or more nodes
        //  Postcondition   The data of the node at the front of the queue is returned

        T get_rear();
        //  Precondition    There should be one or more nodes
        //  Postcondition   The data of the node at the end of the queue is returned

        friend std::ostream &operator << (std::ostream &os, const Deque &que);
        //  Precondition    There should be one or more nodes, T should be a primitive type
        //                  or have an overridden ostream operator
        //  Postcondition   The data of all the nodes is shown

    private:
        Node *head_ptr = nullptr;
        Node *tail_ptr = nullptr;
    };
}

#endif //LINKED_LIST_DEQUE_H
