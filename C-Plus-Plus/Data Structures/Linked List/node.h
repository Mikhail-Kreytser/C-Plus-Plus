//
//      This is the deceleration for the Node class. A node stores
//      ints (by default) as well as the pointer to the next node.
//      You can set the pointer to the next node, set the data,
//      get the data and get the pointer to the next node.
//


#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H



namespace mikhail_kreytser {

    typedef int T;

    class Node {
    public:
        Node(T init_data, Node *init_link);
        //  Postcondition   A node is created with the data of init_data.
        //                  The node also holds a pointer "init_link"

        void set_next_ptr(Node *next);
        //  Precondition    A valid pointer should be passed
        //  Postcondition   The node stores the pointer "next"

        void set_data(T new_data);
        //  Precondition    A valid type T is data should be passed
        //  Postcondition   The node stores "new_data"

        T get_data() const;
        //  Postcondition   Returns the data stored in the node

        Node* get_link();
        //  Postcondition   Returns the pointer of the next node

        const Node* get_link() const;
        //  Postcondition   Returns the pointer of the next node

    private:
        T data;
        Node *next_ptr;
    };
}

#endif //LINKED_LIST_NODE_H
