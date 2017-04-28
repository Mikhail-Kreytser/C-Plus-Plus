//
//      This is the deceleration for the Link_list_stack class.
//      This class knows its capacity, how much it can store.
//      it knows used, how much is already taken up.
//      it knows where on the stack is the information, starting pointer.
//
//

#include <iostream>
#include <cassert>

#ifndef LINKED_LIST_STACK_LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_LINKED_LIST_STACK_H


namespace mikhail_kreytser {

    class Link_list_stack{
    public:
        static const int DEFAULT_CAPACITY = 20;
        Link_list_stack(int size );

        Link_list_stack(Link_list_stack &obj);

        void insert( int &val );

        void insert_at( int &index, int &val );

        void remove_from( int &index );

        int size() const;

        int get(const int &index) const;

        ~Link_list_stack();


    private:
        int capacity;
        int used = 0;
        int *data = nullptr;
    };

}

#endif //LINKED_LIST_STACK_LINKED_LIST_STACK_H
