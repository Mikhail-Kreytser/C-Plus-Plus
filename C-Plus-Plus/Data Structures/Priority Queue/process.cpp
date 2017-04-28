//
//      This is the implementation for the Process class. A Priority_queue
//      class has priority lvl, process time, and the data. You can
//      set the lvl, time, and data. You can get the lvl, time, and data.
//

#include "process.h"

namespace mikhail_kreytser{

    Process::Process(){
        m_priority_lvl = 0;
        m_data = 0;
        m_time = 0;
    }

    Process::Process(int lvl, int time, int data){
        m_priority_lvl = lvl;
        m_time = time;
        m_data = data;
    }

    int Process::getLVL(){
        return m_priority_lvl;
    }

    void Process::setLVL(int lvl){
        m_priority_lvl = lvl;
    }

    int Process::getTime(){
        return m_time;
    }

    void Process::setTime(int time) {
        m_time = time;
    }

    int Process::getData(){
        return m_data;
    }

    void Process::setData(int data){
        m_data = data;
    }

}
