#include <iostream>
#include "process.h"
#include "priority queue.h"

using namespace mikhail_kreytser;

int main() {

    Priority_queue test;

//  (priority lvl , time complexity, data);

    test.insert(3,1,95);
    test.insert(4,2,121);
    test.insert(6,2,987);
    test.insert(5,1,778);
    test.insert(3,1,44);
    test.insert(2,3,3);
    test.insert(1,3,1234);
    test.insert(7,1,5432);
    test.insert(5,1,342);

    test.printAll();

    std::cout << "Top Element is: " << test.get()->getData() << std::endl;

    test.printAll();

    std::cout << "Top Element is: " << test.get()->getData() << std::endl;

    std::cout << "Top Element is: " << test.get()->getData() << std::endl;

    std::cout << "Top Element is: " << test.get()->getData() << std::endl;

    test.printAll();

    return 0;
}
