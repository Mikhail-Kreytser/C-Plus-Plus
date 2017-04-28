//
//      This is the template implementation for the Node class. A node stores
//      the data for a class type of T as well as the pointer to the next node.
//      You can set the pointer to the next node, set the data, get the data and
//      get the pointer to the next node.
//

#ifndef LINKED_LIST_TEMPLATE_NODE_H
#define LINKED_LIST_TEMPLATE_NODE_H

namespace mikhail_kreytser {

    template <class T> class Node {
    public:
        Node(T init_data , Node *init_link ){
            data = init_data;
            next_ptr = init_link;
        }
        //  Postcondition   A node is created with the data of init_data.
        //                  The node also holds a pointer "init_link"

        void set_next_ptr(Node *next) {
            next_ptr = next;

        }
        //  Precondition    A valid pointer should be passed
        //  Postcondition   The node stores the pointer "next"

        void set_data(T new_data) {
            data = new_data;
        }
        //  Precondition    A valid type T is data should be passed
        //  Postcondition   The node stores "new_data"

        T get_data() const {
            return data;
        }
        //  Postcondition   Returns the data stored in the node

        Node* get_link() {
            return next_ptr;
        }
        //  Postcondition   Returns the pointer of the next node

    private:
        T data;
        Node *next_ptr;
    };
}

#endif //LINKED_LIST_TEMPLATE_NODE_H