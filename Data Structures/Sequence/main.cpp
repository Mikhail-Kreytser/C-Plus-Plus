#include "sequence.h"

using namespace mikhail_kreytser;

int main() {
    srand (time(0));
    Sequence test(2000);
    for (int i = 0; i < 1000; i++){
        test.insert(i);
    }

    for (int i = 300; i < 600; i++){
        test.erase_from(i);
    }

    for (int i = 0; i < 400; i++){
        int a = rand() % 500;
        test.insert_at(a,i);
    }

    int temp = 0;
    for (int i = 0; i < 200; i++){
        temp+=4;
        test.erase_from(temp);
    }
    std::cout<<"counter: "<<test.counter<<std::endl;
    return 0;
}


