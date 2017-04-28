#include <iostream>
#include <vector>
#include "linked list.h"

using namespace mikhail_kreytser;

int main() {

    Link_list test(5);
    test.insert(10);

    std::cout << test << std::endl;

    std::vector<int> nums;
    nums.push_back(6);
    nums.push_back(7);
    nums.push_back(8);
    nums.push_back(9);
    test.insert_at(1,nums);

    std::cout << test << std::endl;

    test.remove_from(0,3);

    std::cout << test << std::endl;


    return 0;
}
