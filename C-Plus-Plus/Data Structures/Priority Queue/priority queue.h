//
//      This is the deceleration for the Priority_queue class. A Priority_queue
//      class has a pointer to the elements, it keeps track of how many elements
//      there are, as well as the capacity. You can add to the queue. When an
//      element is removed the priority of the other items in the queue increase
//      by the time taken for the process. You can also increase the priority of a certain process
//

#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_PRIORITY_QUEUE_H

#include "process.h"

namespace mikhail_kreytser {

    class Priority_queue {
    public:
        static const int DEFAULT_CAPACITY = 10;

        Priority_queue(int size = DEFAULT_CAPACITY);
        //  Postcondition       queue created with capacity size

        void reheapRemove(int root, int bottom);
        //  Postcondition       queue reheaped

        void reheapInsert(int root, int bottom);
        //  Postcondition       queue reheaped

        bool insert(Process *item);
        //  Postcondition       item added to queue

        bool insert(int lvl,int time, int data);
        //  Postcondition       item added to queue

        void increasePriority_all(int add);
        //  Postcondition       Increases everyone's priority by "Add"

        void increasePriority_of(Process obj ,int add);
        //  Postcondition       Increases obj's priority by "Add"

        Process *get();
        //  Postcondition       top item is removed and returned

        int getNumElements();
        //  Postcondition       number of elements in the heap returned

        void printAll();
        //  Postcondition       all the elements in the heap printed

        ~Priority_queue();

    private:
        Process *m_Elements;
        int m_iNumElements;
        int m_iHeapLength;

    };
}
#endif //PRIORITY_QUEUE_PRIORITY_QUEUE_H
