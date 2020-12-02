#include <iomanip>

#include "Array.h"

int main() {
    Array<float> arrayFloat;
    arrayFloat.insert(5.6);

    Array<int> arrayInt(3);
    arrayInt.insert(1);
    arrayInt.insert(2);
    arrayInt.insert(3);
    arrayInt.insert(5);
    arrayInt.insert(6);
    arrayInt.insert(7);
    arrayInt.insert(3, 4);
//    arrayInt.insert(8);
//    arrayInt.insert(9);
//    arrayInt.insert(10);
//    arrayInt.insert(11);
//    arrayInt.insert(12);
//    arrayInt.insert(13);
    arrayInt.remove(4);

    arrayInt[5] = 0;
    int arr0 = arrayInt[0];
    std::cout << arr0 << "\n";

    for (int i = 0; i < arrayInt.size(); i++) {
        std::cout << arrayInt[i] << " ";
    }
    std::cout << std::endl;


    Array<int> a;
    for (int i = 0; i< 10; i++) {
        a.insert(i + 1);
    }
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < a.size(); i++) {
        a[i] *= 2;
    }
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
