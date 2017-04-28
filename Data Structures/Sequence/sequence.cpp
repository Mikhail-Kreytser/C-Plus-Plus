#include "sequence.h"
#include <limits>
#include <vector>
#include <cassert>
#include <climits>

namespace mikhail_kreytser {

    Sequence::Sequence(int size) {
        capacity = size;
        empty = capacity;
        used = 0;
        data = new int[capacity];

    }

    Sequence::Sequence(Sequence &obj){
        capacity = obj.capacity;
        empty = capacity;
        data = new int[capacity];
        used = 0;
        size_t i;
        int temp_size = obj.used;
        for (i = 0; i < temp_size; ++i) {
            data[used] = obj.data[i];
            used++;
            empty--;
        }

    }

    void Sequence::insert(const int &val) {
        if (used == capacity) {
            shifting();
        }
        if (used < capacity) {
            *(data + used) = val;
            used++;
            empty--;
            counter++;
        }

        if(empty*1.0/capacity <= 0.2)
            expand();

    }

    int Sequence::get(const int &index) const {
        return *(data + index);
    }

    void Sequence::insert_first(const int &val) {
        if (used == capacity)
            shifting();
        if (used < capacity) {
            if(*(data) ==INT_MIN){
                *(data) = val;
                empty--;
                counter++;
            } else {
                for (int i = used; i > 0; i--) {
                    *(data + i) = *(data + i - 1);
                    counter++;
                }
                used++;
                empty--;
                *(data) = val;
            }
        }
        if(empty*1.0/capacity <= 0.1)
            expand();
    }

    void Sequence::insert_at(const int &index, const int &val) {
        if (used == capacity)
            shifting();
        if (used < capacity) {
            if (*(data + index) == INT_MIN) {
                *(data + index) = val;
                empty--;
                counter++;
            } else {
                for (int i = (used - 1); i >= index; i--) {
                    *(data + i + 1) = *(data + i);
                }
                used++;
                empty--;
                *(data + index) = val;
                counter++;
            }
        }
        if(empty*1.0/capacity <= 0.2)
            expand();
    }

    void Sequence::erase_first() {
        *(data) = INT_MIN;
        empty++;
        counter++;

        if(empty*1.0/capacity>=0.6)
            shrink();
        else if(empty*1.0/ capacity >=0.5)
            shifting();
    }

    void Sequence::erase_last() {
        *(data + used -1) = INT_MIN;
        empty++;
        counter++;

        if(empty*1.0/capacity>=0.6)
            shrink();
        else if(empty*1.0/ capacity>=0.5)
            shifting();
    }

    void Sequence::erase_occurrence(const int &occ, const int &val) {
        int count = 0, pos = 0;
        for (int i = 0; i < used; i++) {
            counter++;
            if (*(data + i) == val)
                count++;
            if (count == occ) {
                pos = i;
                break;
            }
        }
        if (count == 0)
            std::cout << val << " was not found" << std::endl;
        else if (count < occ) {
            std::cout << "There are only " << count << " occurrence(s) of the number " << val << ". Occurrence " << occ
                      << " was not found" << std::endl;
        } else {
            *(data + pos) = INT_MIN;
            empty++;
            counter++;
        }
        if(empty*1.0/capacity>=0.6)
            shrink();
        else if(empty*1.0/ capacity>=0.5)
            shifting();

    }

    void Sequence::erase_from(const int &index) {
        *(data + index) = INT_MIN;
        empty++;
        counter++;
        if(empty*1.0/capacity>=0.6)
            shrink();
    }

    void Sequence::shifting(){
        for(int i = 0; i < used -1; i++) {
            if(*(data + i) == INT_MIN){
                for(int a = i+1; a < used; a++) {
                    counter++;
                    if (*(data + a) != INT_MIN) {
                        *(data + i) = *(data + a);
                        *(data + a) = INT_MIN;

                        break;
                    }
                }
            }
        }
    }

    void Sequence::expand() {
        shifting();
        int increase = (int)(capacity * .5);
        empty += increase;
        std::cout<<"\"Capacity increased from:"<<capacity;
        capacity += increase;
        std::cout<<" to:"<<capacity<<"\" The counter is: "<<counter<<std::endl;
    }

    void Sequence::shrink() {
        shifting();
        int decrease = (int)(capacity * .4);
        int temp[used];
        for (int i = 0; i < used; i++) {
            temp[i] = *(data + i);
            counter++;
        }
        delete[] data;
        data = new int[used];
        for (int i = 0; i < used; i++) {
            *(data + i) = temp[i];
            counter++;
        }
        std::cout<<"\"Capacity decreased from:"<<capacity;
        capacity -= decrease;
        if(empty - decrease>0) empty -= decrease;
        else empty =0;
        used = capacity-empty;
        std::cout<<" to:"<<capacity<<"\" The counter is: "<<counter<<std::endl;
    }

    int Sequence::count(const int &val) {
        int count = 0;
        for (int i = 0; i < used; i++)
            if (*(data + i) == val)
                count++;
        counter++;
        return count;
    }

    int Sequence::size() const {
        return used;
    }

    Sequence operator+(Sequence &one, const Sequence &two) {
        for (int i = 0, temp_size = two.size(); i < temp_size; i++)
            one.insert(two.get(i));
        return one;
    }

    std::ostream &operator<<(std::ostream &os, const Sequence &num) {
        int used = num.size();
        int c = 0;
        for (int i = 0; i < used; i++) {
            if(num.get(i) != INT_MIN) {
                os << c << ". " << num.get(i) << std::endl;
                c++;
            }
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Sequence &num) {
        std::cout<<"Enter your sequence, End entire with a period \" . \": "<<std::endl;
        size_t i;
        num.used = 0;
        for (i = 0; i < num.capacity; i++) {
            if(is ) num.used++;
            else {num.used--; break;}
            is >> num.data[i];
        }
        return is;
    }

    bool operator==(const Sequence &one, const Sequence &two) {
        if (one.size() != two.size())
            return false;
        else {
            for (int i = 0, temp_size = one.size(); i < temp_size; i++)
                if (one.get(i) != two.get(i))
                    return false;
            return true;
        }
    }

    void Sequence::operator+=(const Sequence &addend) {
        size_t i;
        int temp_size = addend.used;
        assert(size() + addend.size() <= capacity);
        for (i = 0; i < temp_size; ++i) {
            data[used] = addend.data[i];
            used++;
        }
    }

    void Sequence::operator=(const Sequence &equaled) {
        assert(equaled.size() <= capacity);
        size_t i;
        used = 0;
        int temp_size = equaled.used;
        for (i = 0; i < temp_size; ++i) {
            data[used] = equaled.data[i];
            used++;
        }
    }

}