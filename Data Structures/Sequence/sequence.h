//
//  The Sequence class is a container class that stores int
//  values. The order is important but repetition is not in
//  the Sequence class. Each Sequence has a fixed capacity.
//  The default capacity is 20. Int stored in sequence must be
//  greater then -2147483648 and less then or equal to 2147483647
//


#ifndef SEQUENCE2_0_SEQUENCE_H
#define SEQUENCE2_0_SEQUENCE_H
#include <iostream>

namespace mikhail_kreytser {

    class Sequence {
    public:
        int counter = 0;

        static const int DEFAULT_CAPACITY = 20;

        Sequence (int size = DEFAULT_CAPACITY);
        //  Postcondition   Sequence of capacity size is created.

        Sequence (Sequence &obj);
        //  Postcondition   "obj" Is copied to a new Sequence.

        void insert (const int &val);
        //  Precondition    There needs to be space in the sequence.
        //  Postcondition   "val" is placed at the end of the sequence.

        void insert_first (const int &val);
        //  Precondition    There needs to be space in the sequence.
        //  Postcondition   "val" is placed at the beginning of the sequence.

        void insert_at (const int &index, const int &val);
        //  Precondition    There needs to be space in the sequence.
        //  Postcondition   "val" is paced into "index" of the sequence.

        int count (const int &val);
        //  Postcondition   Returns the count of "val".

        int size() const;
        //  Postcondition   Returns used.

        int get (const int &index) const;
        //  Precondition    The index should be within the used portion of the sequence.
        //  Postcondition    Returns value at "index".

        void erase_first();
        //  Precondition    There has to be an element in the first position.
        //  Postcondition   The element in the first position is erased.

        void erase_last();
        //  Precondition    There has to be an element in the last position.
        //  Postcondition   The element in the last position is erased.

        void erase_occurrence (const int &occ, const int &val);
        //  Precondition    There should be at least "occ" number of "val" in the sequence.
        //  Postcondition   The "occ" of "val" is removed.

        void erase_from (const int &index);
        //  Precondition    The index should be within the used portion of the sequence.
        //  Postcondition   The element at the "index" position is erased.

        void operator += (const Sequence &addend);
        //  Precondition    The combined capacity should not exceed the capacity of the sequence being added to.
        //  Postcondition   THIS and "addend" are combined together.

        void operator = (const Sequence &equaled);
        //  Precondition    The capacity of "equaled" should not exceed the capacity of the sequence being set.
        //  Postcondition   THIS is set to be the same as "equaled".

        void shifting();
        //  Postcondition   All elements are shifted to the left and empty spaces are removed

        void expand();
        //  Postcondition   Sequence is enlarged by 0.5%

        void shrink();
        //  Postcondition   Sequence is shrunk by 0.4%

        friend Sequence operator + (const Sequence &one, const Sequence &two);
        //  Precondition    The size of the combined input must not exceed the capacity.
        //  Postcondition   A combined sequence is returned.

        friend bool operator == (const Sequence &one, const Sequence &two);
        //  Postcondition   A bool is returned.

        friend std::ostream &operator << (std::ostream &os, const Sequence &num);
        //  Postcondition   "num" is out-putted.

        friend std::istream &operator >> (std::istream &is, Sequence &num);
        //
        //  Postcondition   "num" is over writen with the input provided.

        ~Sequence() {
            delete[] data;
        }

    private:

        int capacity;
        int used = 0;
        int empty;
        int *data = nullptr;


    };

}

#endif //SEQUENCE2_0_SEQUENCE_H
