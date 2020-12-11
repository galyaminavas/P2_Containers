#include <iomanip>
#include <iostream>
#include <utility>

#include "Array.h"
#include "List.h"

void workingWithArray() {
    //    Array<float> arrayFloat;
//    arrayFloat.insert(5.6);
//
//    Array<int> arrayInt(3);
//    arrayInt.insert(1);
//    arrayInt.insert(2);
//    arrayInt.insert(3);
//    arrayInt.insert(5);
//    arrayInt.insert(6);
//    arrayInt.insert(7);
//    arrayInt.insert(3, 4);
////    arrayInt.insert(8);
////    arrayInt.insert(9);
////    arrayInt.insert(10);
////    arrayInt.insert(11);
////    arrayInt.insert(12);
////    arrayInt.insert(13);
//    arrayInt.remove(4);
//
//    arrayInt[5] = 0;
//    int arr0 = arrayInt[0];
//    std::cout << arr0 << "\n";
//
//    for (int i = 0; i < arrayInt.size(); i++) {
//        std::cout << arrayInt[i] << " ";
//    }
//    std::cout << std::endl;
//
//
//    Array<int> a;
//    for (int i = 0; i< 10; i++) {
//        a.insert(i + 1);
//    }
//    for (int i = 0; i < a.size(); i++) {
//        std::cout << a[i] << " ";
//    }
//    std::cout << std::endl;
//    for (int i = 0; i < a.size(); i++) {
//        a[i] *= 2;
//    }
//    for (int i = 0; i < a.size(); i++) {
//        std::cout << a[i] << " ";
//    }
//    std::cout << std::endl;

    Array<int> a;
    for (int i = 0; i < 10; ++i)
        a.insert(i + 1);
    for (int i = 0; i < a.size(); ++i) {
        a[i] *= 2;
    }

    auto it = a.iterator();
    while (it.hasNext()) {
        it.set(1);
        it.next();
    }
    it.set(1);

//    // for updated hasNext, otherwise, it won't print the last element
//    for (auto it = a.iterator(); it.hasNext(); it.next())
//        std::cout << it.get() << " ";
//    std::cout << std::endl;

//// for updated hasPrev, otherwise, it won't print the first element
//    auto it = a.iterator();
//    it.toIndex(a.size() - 1);
//    while (it.hasPrev()) {
//        std::cout << it.get() << " ";
//        it.prev();
//    }
//    std::cout << std::endl;

    it.toIndex(0);
    while (it.hasNext()) {
        std::cout << it.get() << " ";
        it.next();
    }
    std::cout << it.get() << std::endl;

    it.toIndex(a.size() - 1);
    while (it.hasPrev()) {
        std::cout << it.get() << " ";
        it.prev();
    }
    std::cout << it.get() << std::endl;

    it.toIndex(4);
    it.insert(5);
    it.toIndex(0);
    while (it.hasNext()) {
        std::cout << it.get() << " ";
        it.next();
    }
    std::cout << it.get() << std::endl;

    it.toIndex(4);
    it.remove();
    it.toIndex(0);
    while (it.hasNext()) {
        std::cout << it.get() << " ";
        it.next();
    }
    std::cout << it.get() << std::endl;
}

void workingWithList() {
    List<int> list;
    for (int i = 0; i < 15; i++) {
        list.insertTail(i + 1);
    }

    list.insertTail(100);
    list.stupidPrint();

    auto it = list.iterator();
//    for (int i = 0; i < 1; i++) {
//        it.next();
//    }
//    it.next();
    list.stupidPrint();
    std::cout << it.get() << "\n";

    it.remove();
    std::cout << "NEW LIST AFTER REMOVING HEAD\n";
    list.stupidPrint();
    std::cout << list.size() << "\n";
//    std::cout << it.get() << "\n";
//    list.stupidPrint();

//    while (it.hasNext()) {
//        std::cout << it.get() << " ";
//        it.next();
//    }

//    list.removeTail();



//    it.remove();
//    list.stupidPrint();

//    while (it.hasNext()) {
//        std::cout << it.get() << " ";
//        it.next();
//    }
//    std::cout << it.get() << "\n";
//
//    while (it.hasPrev()) {
//        std::cout << it.get() << " ";
//        it.prev();
//    }
//    std::cout << it.get() << "\n";
//
//    it.set(50);
//    std::cout << it.get() << "\n";
//    std::cout << it.hasPrev() << "\n";
//
//    std::cout << list.head() << " " << list.tail() << "\n";
//    std::cout << list.size() << "\n";

}

int main() {
    return 0;
}
