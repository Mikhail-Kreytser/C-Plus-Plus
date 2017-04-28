//
//      This is the implementation for the Node class. A node stores
//      ints (by default) as well as the pointer to the next node.
//      Although this is not a template class I made it very easy
//      to change the type that is stored. The type can be changed
//      by modifying line 16. (IF CHANGED: please also edit deque.h,
//      deque.cpp and node.h) You can set the pointer to the next
//      node, set the data, get the data and get the pointer
//      to the next node.
//

#include "node.h"

namespace mikhail_kreytser {

    typedef int T;

    Node::Node(T init_data , Node *init_link ){
        data = init_data;
        next_ptr = init_link;
    }

    void Node::set_next_ptr(Node *next) {
        next_ptr = next;

    }

    void Node::set_data(T new_data) {
        data = new_data;
    }

    T Node::get_data() const {
        return data;
    }

    Node *Node::get_link() {
        return next_ptr;
    }

    const Node *Node::get_link() const {
        return next_ptr;
    }
}
