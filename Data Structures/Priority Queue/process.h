//
//      This is the deceleration for the Process class. A Priority_queue
//      class has priority lvl, process time, and the data. You can
//      set the lvl, time, and data. You can get the lvl, time, and data.
//

#ifndef PRIORITY_QUEUE_PROCESS_H
#define PRIORITY_QUEUE_PROCESS_H

namespace mikhail_kreytser {

    class Process {
    public:
        Process();
        //  Postcondition   Process created with all values set to 0

        Process(int lvl,int time, int data);
        //  Postcondition   Process created with all values set to their respectable values

        int getLVL();
        //  Postcondition   item priority returned

        void setLVL(int key);
        //  Postcondition   item priority set

        int getTime();
        //  Postcondition   item process time returned

        void setTime(int time);
        //  Postcondition   item process time set

        int getData();
        //  Postcondition   data item returned

        void setData(int data);
        //  Postcondition   data item value set

    private:
        int m_priority_lvl;
        int m_time;
        int m_data;
    };
}

#endif //PRIORITY_QUEUE_PROCESS_H
