//
//      This is the implementation for the double-ended queue (DEQUE). The DEQUE
//      stores ints in nodes (by default). Although this is not a template class
//      I made it very easy to change the type that is stored. The type can be
//      changed by modifying line 16. (IF CHANGED: please also edit deque.h,
//      node.h and node.cpp). You can add to the front of the queue as well as
//      the back. You can also remove from the front and remove from the
//      back. I also added a ostream function to display the queue.
//

#include <iostream>
#include "deque.h"

namespace mikhail_kreytser {

    typedef int T;

    Deque::Deque(T val) {
            tail_ptr = head_ptr = new Node(val, nullptr);
        }

    void Deque::add_rear(T val) {
        Node *old_tail_ptr = tail_ptr;
        tail_ptr = new Node(val, nullptr);
        old_tail_ptr->set_next_ptr(tail_ptr);
    }

    void Deque::add_front(T val) {
        Node *old_head_ptr = head_ptr;
        head_ptr = new Node(val, old_head_ptr);
    }

    void Deque::remove_rear() {
        Node *pos = head_ptr;
        while(true){
            if (pos->get_link()!=tail_ptr)
                pos = pos->get_link();
            else{
                tail_ptr->~Node();
                tail_ptr = pos;
                break;
            }
        }

    }

    void Deque::remove_front() {
        Node *old_head_ptr = head_ptr;
        head_ptr = old_head_ptr->get_link();
        old_head_ptr->~Node();
    }

    T Deque::get_front() {
        return head_ptr->get_data();
    }

    T Deque::get_rear() {
        return tail_ptr->get_data();
    }

    std::ostream &operator << (std::ostream &os, const Deque &que){
        Node *pos = que.head_ptr;
        while(true){
            if (pos->get_link()!=que.tail_ptr) {
                std::cout << pos->get_data() << std::endl;
                pos = pos->get_link();
            }
            else{
                std::cout<< pos->get_data() << std::endl<<que.tail_ptr->get_data()<<std::endl;
                break;
            }
        }
    }

}