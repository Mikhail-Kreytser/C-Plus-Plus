//
//      This is the deceleration for the Hash Node class. A node stores a
//      key as well as the pointer to the next node, left node and right node
//      You can set the pointer to the next node, left node, right node, set the key,
//      get the key and get the pointer to the next node, left node, right node
//

#ifndef HASH_TABLE_DATA_STRUCTURE_HASH_NODE_H
#define HASH_TABLE_DATA_STRUCTURE_HASH_NODE_H


namespace mikhail_kreytser {


    class Hash_Node {
    public:

        Hash_Node();
        //  Postcondition   A node is created

        Hash_Node(Hash_Node &obj);
        //  Postcondition   A node is created with the data of obj

        Hash_Node(int init_data);
        //  Postcondition   A node is created with the data of init_data

        void set_next_ptr(Hash_Node *next);
        //  Precondition    A valid pointer should be passed
        //  Postcondition   The node stores the pointer "next"

        void set_left_ptr(Hash_Node *next);
        //  Precondition    A valid pointer should be passed
        //  Postcondition   The node stores the pointer "next"

        void set_right_ptr(Hash_Node *next);
        //  Precondition    A valid pointer should be passed
        //  Postcondition   The node stores the pointer "next"

        void set_key(int new_key);
        //  Precondition    A valid type T is data should be passed
        //  Postcondition   The node stores "new_data"

        int get_key() const;
        //  Postcondition   Returns the data stored in the node

        const Hash_Node* get_next()const ;
        //  Postcondition   Returns the pointer of the next node

        const Hash_Node* get_left()const ;
        //  Postcondition   Returns the pointer of the next node left

        const Hash_Node* get_right()const ;
        //  Postcondition   Returns the pointer of the next node right

        Hash_Node* get_next();
        //  Postcondition   Returns the pointer of the next node

        Hash_Node* get_left();
        //  Postcondition   Returns the pointer of the next node left

        Hash_Node* get_right();
        //  Postcondition   Returns the pointer of the next node right

        ~ Hash_Node();
        //  Postcondition   Deletes the Node

    private:
        int key;
        Hash_Node *next_ptr;
        Hash_Node *left_ptr;
        Hash_Node *right_ptr;
    };
}

#endif //HASH_TABLE_DATA_STRUCTURE_HASH_NODE_H
