//
//      This is the implementation for the Hash_Table class. A Hash_Table
//      class has a pointer to the data, pointer to the array that keeps
//      track of if the entry in the hash table follow a tree or link list
//      structure. The Hash_Table expands when used is more then n log(n)
//      you can insert new nodes and get location of keys .
//

#include "Hash Table.h"
#include <math.h>
#include <limits>
#include <vector>

namespace mikhail_kreytser {

    Hash_Table::Hash_Table(int size) {
        capacity = size;
        tree = new int[capacity];
        for(int i = 0; i < capacity; i++)
            *(tree + i) = 0;
        data = new Hash_Node[capacity];
        used = 0;
    }

    Hash_Table::Hash_Table(Hash_Table &obj){
        capacity = obj.capacity;
        tree = new int[capacity];
        for(int i = 0; i < capacity; i++)
            *(tree + i) = 0;
        data = new Hash_Node[capacity];
        used = 0;

        for (int i = 0; i < obj.capacity; i++){
            if((obj.data + i)->get_key() == std::numeric_limits<int>::min())
                i++;
            else {
                Hash_Node *pos = (obj.data + i);
                do{
                    this->insert(*pos);
                    if(pos->get_next() != nullptr)
                        pos = pos->get_next();
                    else break;
                }while(true);
            }
        }
    }

    void Hash_Table::insert(Hash_Node &new_node ) {
        const int hash_pos = new_node.get_key() % capacity;

        if ((data + hash_pos)->get_key() == std::numeric_limits<int>::min()) {
            *(data + hash_pos) = new_node;
            used++;
        } else {
            int counter = 1;
            Hash_Node *pos = (data + hash_pos);
            do {
                if (pos->get_next() == nullptr) {
                    pos->set_next_ptr(new Hash_Node(new_node.get_key()));
                    used++;
                    break;
                } else {
                    counter++;
                    pos = pos->get_next();
                }
            } while (true);
            if (counter >= 10)
                *(tree + hash_pos) = 1;

            pos = (data + hash_pos);
            do {
                if (pos->get_key() < new_node.get_key()) {
                    if (pos->get_left() == nullptr) {
                        pos->set_left_ptr(new Hash_Node(new_node.get_key()));
                        used++;
                        break;
                    } else
                        pos = pos->get_left();
                } else {
                    if (pos->get_right() == nullptr) {
                        pos->set_right_ptr(new Hash_Node(new_node.get_key()));
                        used++;
                        break;
                    } else
                        pos = pos->get_right();
                }
            } while (true);
        }

        if (used >= capacity * log(capacity))
            expand();

    }

    void Hash_Table::expand() {
        std::cout <<"-Expanding from: "<<capacity;
        std::vector<int> keys;
        for(int i = 0; i < capacity; i++){
            Hash_Node *pos = (data + i);
                do{
                    if(pos->get_key() == std::numeric_limits<int>::min())
                        break;
                    else if (pos->get_next() == nullptr){
                        keys.push_back(pos->get_key());
                        break;
                    }
                    else {
                        keys.push_back(pos->get_key());
                        pos = pos->get_next();
                    }
                }while(true);
            }
        capacity +=10;
        used = 0;
        std::cout <<" to: "<<capacity<<std::endl;

        delete [] tree;
        tree = new int[capacity];


        for(int i = 0; i < capacity; i++)
            *(tree + i) = 0;

        delete [] data;
        data = new Hash_Node[capacity];

        for (int i = 0; i < keys.size(); i++){
            Hash_Node temp (keys.at(i));
            this->insert( temp );
        }
    }

    Hash_Node *Hash_Table::get_prt_of(int find_key) {
        const int hash_pos = find_key % capacity;
        int is_tree = *(tree + hash_pos);
        Hash_Node *pos = (data + hash_pos);
        if (is_tree == 1) {
            do {
                if (pos->get_key() < find_key) {
                    if(pos->get_left() != nullptr)
                        pos = pos->get_left();
                    else
                        return nullptr;
                } else {
                    if(pos->get_right() != nullptr)
                        pos = pos->get_right();
                    else
                        return nullptr;
                }
                if (pos->get_key() == find_key)
                    return pos;
            } while (true);
        }
        else {
            do{
                if(pos->get_key() == find_key) {
                    std::cout <<pos->get_key()<<" Is at memory: "<< pos << std::endl;
                    return pos;
                }
                else if(pos->get_next() != nullptr)
                    pos = pos->get_next();
                else {
                    std::cout << "NULL" << std::endl;
                    return nullptr;
                }
            }while(true);
        }
    }

    Hash_Table::~Hash_Table() {
        delete [] tree;
        delete [] data;
    }


}
