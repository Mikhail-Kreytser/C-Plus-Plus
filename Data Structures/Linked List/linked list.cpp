//
//      This is the implementation for the Link_list class. A link_list
//      class has a head pointer and tail pointer. The head pointer
//      points to the first link in the list. The tail pointer points
//      to the last element of the list. You can insert an new node
//      that holds and int, insert an new node that holds and int
//      at a specific location, you can remove_from elements from a location,
//      you can get the value from a location
//

#include <iostream>
#include <vector>
#include "linked list.h"

namespace mikhail_kreytser {


    Link_list::Link_list(int val) {
        tail = head = new Node(val, nullptr);
    }

    Link_list::Link_list(Link_list &obj) {
        tail = head = new Node(obj.head->get_data(), nullptr);
        Node *curr = head;
        int i = 0;
        while (curr->get_link() != nullptr) {
            curr = curr->get_link();
            i++;
            this->insert(curr->get_data());
        }
    }

    void Link_list::insert(int val) {
        Node *old_tail_ptr = tail;
        tail = new Node(val, nullptr);
        old_tail_ptr->set_next_ptr(tail);
    }

    void Link_list::insert_at(int loc, std::vector<int> &vals) {
        unsigned long tempsize = vals.size();
        Node *curr = head;
        int i = 0;

        while (curr->get_link() != nullptr && loc != i) {

            curr = curr->get_link();
            i++;
        }
        if(loc == 0) {
            Node *temp = new Node(curr->get_data(),head);
            head->set_data(vals.at(tempsize - 1));
            head = temp;
        }
        else {
            Node *temp = new Node(curr->get_data(), curr->get_link());
            if (curr->get_link() == nullptr)
                tail = temp;
            curr->set_next_ptr(temp);
            curr->set_data(vals.at(tempsize - 1));
        }
        if (tempsize > 1) {
            vals.pop_back();
            this->insert_at(loc, vals);
        }


    }

    void Link_list::remove_from(int loc, int amount) {
        Node * curr = head;
        Node * del;
        int i =0;
        if(loc == 0){
            del = head;
            head = curr->get_link();
        }
        else {
            while (curr->get_link() != nullptr && loc - 1 != i) {
                curr = curr->get_link();
                i++;
            }

            if (curr->get_link() == tail) {
                curr->set_next_ptr(nullptr);
                del = tail;
                tail = curr;
            } else {
                del = curr->get_link();
                curr->set_next_ptr(curr->get_link()->get_link());
            }
        }
        delete del;
        amount--;
        if(amount >= 1)
            this->remove_from(loc, amount);
    }

    int Link_list::get(int loc) {
        Node *curr = head;
        int i = 0;
        while (curr->get_link() != nullptr && loc != i) {
            curr = curr->get_link();
            i++;
        }
        return curr->get_data();
    }

    std::ostream &operator << (std::ostream &os, const Link_list &list){
        Node *pos = list.head;
        while(true){
            if (pos->get_link()!=list.tail) {
                std::cout << pos->get_data() << std::endl;
                pos = pos->get_link();
            }
            else{
                std::cout<< pos->get_data() << std::endl<<list.tail->get_data()<<std::endl;
                break;
            }
        }
    }

    Link_list::~Link_list(){
        Node *curr = head;
        Node *temp = head;
        int i = 0;
        do{

            curr = curr->get_link();
            delete temp;
            temp = curr;
            i++;
        }while (curr->get_link() != nullptr);
        delete temp;
    }




}

