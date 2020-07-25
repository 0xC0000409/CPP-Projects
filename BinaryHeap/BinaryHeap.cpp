#include "Header.h"
#include <iostream>
using namespace std;

int main() {
    BinaryHeap z(8);
    z.insert_val(10);
    z.insert_val(30);
    z.insert_val(20);
    z.insert_val(35);
    z.insert_val(40);
    z.insert_val(32);
    z.insert_val(25);
    z.insert_val(35);
    z.modify(41, 4);

    for (int i = 0; i < 8; i++) {
        z.triverse();
        z.extract();
        cout << endl;
   }
}

