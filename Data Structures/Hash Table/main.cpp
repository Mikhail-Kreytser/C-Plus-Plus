#include <iostream>
#include "Hash Table.h"

using namespace mikhail_kreytser;

int main() {
    Hash_Node list [20];
    
    list[0].set_key(90000);
    list[1].set_key(10000);
    list[2].set_key(00000);
    list[3].set_key(40000);
    list[4].set_key(20000);
    list[5].set_key(80000);
    list[6].set_key(70000);
    list[7].set_key(50000);
    list[8].set_key(30000);
    list[9].set_key(60000);
    list[10].set_key(22000);
    list[11].set_key(42000);
    list[12].set_key(62000);
    list[13].set_key(82000);
    list[14].set_key(102000);
    list[15].set_key(2000);
    list[16].set_key(6000);
    list[17].set_key(7000);
    list[18].set_key(8000);
    list[19].set_key(9000);


    Hash_Table test(2);
    test.insert(list[0]);
    test.insert(list[1]);
    test.insert(list[2]);
    test.insert(list[3]);
    test.insert(list[4]);
    test.insert(list[5]);
    test.insert(list[6]);
    test.insert(list[7]);
    test.insert(list[8]);
    test.insert(list[9]);
    test.insert(list[10]);
    test.insert(list[11]);
    test.insert(list[12]);
    test.insert(list[13]);
    test.insert(list[14]);
    test.insert(list[15]);
    test.insert(list[16]);
    test.insert(list[17]);
    test.insert(list[18]);
    test.insert(list[19]);

    test.get_prt_of(99);
    test.get_prt_of(2000);

    return 0;
}