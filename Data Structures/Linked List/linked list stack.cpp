//
//      This is the implementation for the Link_list_stack class.
//      You can insert an new node that holds and int, insert an
//      new node that holds and int at a specific location, you
//      can remove_from elements from a location, you can get
//      the value from a location
//

#include "linked list stack.h"

namespace mikhail_kreytser {

    Link_list_stack::Link_list_stack(int size) {
        capacity = size;
        data = new int[capacity];
    }

    Link_list_stack::Link_list_stack(Link_list_stack &obj) {
        capacity = obj.capacity;
        data = new int[capacity];
        used = 0;
        size_t i;
        int temp_size = obj.used;
        for (i = 0; i < temp_size; ++i) {
            data[used] = obj.data[i];
            used++;
        }
    }

    void Link_list_stack::insert(int &val) {
        assert(used < capacity);
        *(data + used) = val;
        used++;
    }

    void Link_list_stack::insert_at(int &index, int &val) {
        assert(used < capacity);
        if (index >= used) {
            std::cout << "Index Invalid" << std::endl;
        } else {
            for (int i = (used - 1); i >= index; i--) {
                *(data + i + 1) = *(data + i);
            }
            used++;
            *(data + index) = val;
        }
    }

    void Link_list_stack::remove_from(int &index) {
        for (int i = index; i < (used - 1); i++) {
            *(data + i) = *(data + i + 1);
        }
        delete (data + used);
        used--;

    }

    int Link_list_stack::size() const {
        return used;
    }

    int Link_list_stack::get(const int &index) const {
        return *(data + index);
    }

    Link_list_stack::~Link_list_stack() {
            delete[] data;
    }


}
