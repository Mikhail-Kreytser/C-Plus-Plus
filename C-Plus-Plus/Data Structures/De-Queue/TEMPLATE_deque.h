//
//      This is the template implementation for the double-ended queue (DEQUE).
//      The DEQUE stores T class types in nodes. You can add to the front of the
//      queue as well as the back. You can also remove from the front and remove
//      from the back. I also added a ostream function to display the queue.
//

#include "TEMPLATE_node.h"
#include <iostream>
#ifndef LINKED_LIST_TEMPLATE_DEQUE_H
#define LINKED_LIST_TEMPLATE_DEQUE_H

namespace mikhail_kreytser {
    template<class T> class Deque {
    public:

        Deque<T>(T val) {
            tail_ptr = head_ptr = new Node<T>(val, nullptr);
        }

        void add_rear(T val) {
            Node<T> *old_tail_ptr = tail_ptr;
            tail_ptr = new Node<T>(val, nullptr);
            old_tail_ptr->set_next_ptr(tail_ptr);
        }
        //  Precondition    The data in all nodes should be the same type
        //  Postcondition   A node with the data val is added to the end of the queue

        void add_front(T val) {
            Node<T> *old_head_ptr = head_ptr;
            head_ptr = new Node<T>(val, old_head_ptr);
        }
        //  Precondition    The data in all nodes should be the same type
        //  Postcondition   A node with the data val is added to the front of the queue

        void remove_rear() {
            Node<T> *pos = head_ptr;
            while (true) {
                if (pos->get_link() != tail_ptr)
                    pos = pos->get_link();
                else {
                    //tail_ptr->~Node();
                    tail_ptr = pos;
                    break;
                }
            }

        }
        //  Precondition    There should be two or more nodes
        //  Postcondition   The node at the end of the queue is removed

        void remove_front() {
            Node<T> *old_head_ptr = head_ptr;
            head_ptr = old_head_ptr->get_link();
            //old_head_ptr->~Node();
        }
        //  Precondition    There should be two or more nodes
        //  Postcondition   The node at the front of the queue is removed

        T get_front() {
            return head_ptr->get_data();
        }
        //  Precondition    There should be one or more nodes
        //  Postcondition   The data of the node at the front of the queue is returned

        T get_rear() {
            return tail_ptr->get_data();
        }
        //  Precondition    There should be one or more nodes
        //  Postcondition   The data of the node at the end of the queue is returned

        friend std::ostream &operator<<(std::ostream &os, const Deque<T> &que) {
            Node<T> *pos = que.head_ptr;
            while (true) {
                if (pos->get_link() != que.tail_ptr) {
                    std::cout << pos->get_data() << std::endl;
                    pos = pos->get_link();
                } else {
                    std::cout << pos->get_data() << std::endl << que.tail_ptr->get_data() << std::endl;
                    break;
                }
            }
        }
        //  Precondition    There should be one or more nodes, T should be a primitive type
        //                  or have an overridden ostream operator
        //  Postcondition   The data of all the nodes is shown

    private:
        Node<T> *head_ptr = nullptr;
        Node<T> *tail_ptr = nullptr;
    };

}

#endif //LINKED_LIST_TEMPLATE_DEQUE_H
