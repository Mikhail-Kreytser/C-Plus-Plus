//
//      This is the deceleration for the Hash_Table class. A Hash_Table
//      class has a pointer to the data, pointer to the array that keeps
//      track of if the entry in the hash table follow a tree or link list
//      structure. The Hash_Table expands when used is more then n log(n)
//      you can insert new nodes and get location of keys .
//

#ifndef HASH_TABLE_DATA_STRUCTURE_HASH_TABLE_H
#define HASH_TABLE_DATA_STRUCTURE_HASH_TABLE_H

#include <iostream>
#include "Hash Node.h"

namespace  mikhail_kreytser {

    class Hash_Table{
    public:
        static const int DEFAULT_CAPACITY = 20;

        Hash_Table(int size = DEFAULT_CAPACITY);
        //  Postcondition   A Hash Table with the capacity of size is created.

        Hash_Table( Hash_Table &obj);
        //  Postcondition   A Hash Table with the same information as obj is created.

        void insert (Hash_Node &new_node );
        //  Postcondition   new_node is inserted into the Hash Table

        void expand ();
        //  Postcondition   The capacity of the Hash Table is enlarged, Data is stored again.

        Hash_Node* get_prt_of(int find_key);
        //  Postcondition   Returns the location of the key, if not found returns nullptr
        //                  outprints "KEY" Is at memory: "LOCATION"

        ~ Hash_Table();
        //  Postcondition   Deletes the Hash Table

    private:
        int capacity;
        int used;
        int *tree;
        Hash_Node *data;
    };

}

#endif //HASH_TABLE_DATA_STRUCTURE_HASH_TABLE_H
