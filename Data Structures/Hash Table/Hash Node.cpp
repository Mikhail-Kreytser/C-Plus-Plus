//
//      This is the implementation for the Hash Node class. A node stores a
//      key as well as the pointer to the next node, left node and right node
//      You can set the pointer to the next node, left node, right node, set the key,
//      get the key and get the pointer to the next node, left node, right node
//


#include "Hash Node.h"
#include <limits>

namespace mikhail_kreytser {

    Hash_Node::Hash_Node() {
        key = std::numeric_limits<int>::min();
        next_ptr = nullptr;
        right_ptr = nullptr;
        left_ptr = nullptr;
    }

    Hash_Node::Hash_Node(Hash_Node &obj){
        key = obj.get_key();
        next_ptr = obj.get_next();
        left_ptr = obj.get_left();
        right_ptr = obj.get_right();

    }

    Hash_Node::Hash_Node(int init_data){
        key = init_data;
        next_ptr  = nullptr;
        left_ptr= nullptr;
        right_ptr = nullptr;
    }

    void Hash_Node::set_next_ptr(Hash_Node *next) {
        next_ptr = next;
    }

    void Hash_Node::set_left_ptr(Hash_Node *next) {
        left_ptr = next;
    }

    void Hash_Node::set_right_ptr(Hash_Node *next) {
        right_ptr = next;
    }

    void Hash_Node::set_key(int new_key) {
        key = new_key;
    }

    int Hash_Node::get_key() const {
        return key;
    }

    Hash_Node *Hash_Node::get_next(){
        return next_ptr;
    }

    Hash_Node *Hash_Node::get_left(){
        return left_ptr;
    }

    Hash_Node *Hash_Node::get_right(){
        return right_ptr;
    }

    const Hash_Node *Hash_Node::get_next() const {
        return next_ptr;
    }

    const Hash_Node *Hash_Node::get_left() const {
        return left_ptr;
    }

    const Hash_Node *Hash_Node::get_right() const {
        return right_ptr;
    }

    Hash_Node::~Hash_Node() {
        delete left_ptr;
        delete right_ptr;
    }


}