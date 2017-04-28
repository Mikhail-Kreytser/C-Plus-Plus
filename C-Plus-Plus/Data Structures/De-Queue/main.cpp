//
//      This is the main.cpp file for the double-ended queue (DEQUE).
//      This DEQUE has both a template implementation and a regular
//      one. To use the template implementation please UNCOMMENT
//      the "#define USE_TEMPLATE" (10th line)... On the other hand,
//      to use the non template class please COMMENT the
//      "#define USE_TEMPLATE" (10th line)
//

#define USE_TEMPLATE

#ifdef USE_TEMPLATE
    #include "TEMPLATE_deque.h"
#else
    #include "deque.h"
#endif

using namespace mikhail_kreytser;

int main() {
#ifdef USE_TEMPLATE
    Deque <char>test('d');

    test.add_front('c');
    test.add_front('b');
    test.add_rear('e');
    test.add_front('a');
    test.add_rear('f');
    test.remove_front();
    test.remove_rear();
    test.add_front('y');
    test.add_rear('z');
#else
    Deque test(4);

    test.add_front(3);
    test.add_front(2);
    test.add_rear(5);
    test.add_front(1);
    test.add_rear(6);
    test.remove_front();
    test.remove_rear();
    test.add_front(100);
    test.add_rear(600);
#endif

    std::cout<<"FRONT: "<<test.get_front()<<" REAR: "<< test.get_rear()<<std::endl<<std::endl;

    std::cout << "||| PRINT ALL |||"<<std::endl;
    std::cout << "VVV PRINT ALL VVV"<<std::endl<<test << std::endl;
    return 0;
}

//
//      To speed up this queue we can make the nodes hold a pointer to
//      the previous node. This will make the remove rear node function
//      lot faster to. This will have a huge impact on the time it takes
//      to remove the last node especially in long queues. We will not
//      have to start from front and work all the way to the end. We
//      wil be able to start from the back.
//
