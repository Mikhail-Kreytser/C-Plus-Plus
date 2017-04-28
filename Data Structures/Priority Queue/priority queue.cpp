//
//      This is the implementation for the Priority_queue class. A Priority_queue
//      class has a pointer to the elements, it keeps track of how many elements
//      there are, as well as the capacity. You can add to the queue. When an
//      element is removed the priority of the other items in the queue increase
//      by the time taken for the process. You can also increase the priority of a certain process
//

#include "priority queue.h"
#include <iostream>

namespace mikhail_kreytser {
    Priority_queue::Priority_queue(int size) {
        m_Elements = new Process[size];
        m_iNumElements = 0;
        m_iHeapLength = size;
    }

    void Priority_queue::reheapRemove(int root, int bottom) {
        int maxChild;
        int rightNext;
        int leftNext;
        Process temp;

        leftNext = root * 2 + 1;
        rightNext = root * 2 + 2;

        if(leftNext <= bottom)
        {
            if(leftNext == bottom){
                maxChild = leftNext;
            }
            else{
                if(m_Elements[leftNext].getLVL() <= m_Elements[rightNext].getLVL())
                    maxChild = rightNext;
                else
                    maxChild = leftNext;
            }
            if(m_Elements[root].getLVL() < m_Elements[maxChild].getLVL()){
                temp = m_Elements[root];
                m_Elements[root] = m_Elements[maxChild];
                m_Elements[maxChild] = temp;

                reheapRemove(maxChild, bottom);
            }
        }
    }
    
    void Priority_queue::reheapInsert(int root, int bottom){
        int parent;
        Process temp;
        if(bottom > root)
        {
            parent = (bottom -1) / 2;
            if(m_Elements[parent].getLVL() < m_Elements[bottom].getLVL())
            {
                temp = m_Elements[parent];
                m_Elements[parent] = m_Elements[bottom];
                m_Elements[bottom] = temp;
                reheapInsert(root, parent);
            }
        }
    }

    bool Priority_queue::insert(Process *item){
        if(m_iNumElements < m_iHeapLength)
        {
            m_Elements[m_iNumElements] = *item;
            reheapInsert(0, m_iNumElements);
            m_iNumElements++;
            return true;
        }
        return false;
    }

    bool Priority_queue::insert(int lvl,int time, int data){
        bool retVal;
        Process *temp = new Process(lvl, time, data);
        retVal = insert(temp);
        delete temp;
        return retVal;
    }

    Process *Priority_queue::get(){
        Process *temp = new Process(m_Elements[0].getLVL(),m_Elements[0].getTime(), m_Elements[0].getData());
        m_iNumElements--;
        m_Elements[0] = m_Elements[m_iNumElements];
        reheapRemove(0, m_iNumElements - 1);
        if(m_iNumElements == 0)
            return NULL;
        else {
            increasePriority_all(temp->getTime());
            return temp;
        }
    }

    void Priority_queue::increasePriority_all(int add){
        for(int i=0; i<m_iNumElements; i++){
            m_Elements[i].setLVL(m_Elements[i].getLVL() + add);
        }
    }

    void Priority_queue::increasePriority_of(Process obj, int add) {
        for(int i=0; i<m_iNumElements; i++){
            if(m_Elements[i].getData() == obj.getData() && m_Elements[i].getTime() == obj.getTime() && m_Elements[i].getLVL() == obj.getLVL()){
                m_Elements[i].setLVL(m_Elements[i].getLVL() + add);
            }
        }
    }

    int Priority_queue::getNumElements(){
        return m_iNumElements;
    }

    void Priority_queue::printAll(){
        for(int i=0; i<m_iNumElements; i++){
            std::cout << "Element " << i << " in the heap has, Priority: " << m_Elements[i].getLVL()
                      << ", The Process time is: " << m_Elements[i].getTime() << ", The data is:"<<
                      m_Elements[i].getData()<< std::endl;
        }
    }
    
    Priority_queue::~Priority_queue(){
        delete[] m_Elements;
    }


}
