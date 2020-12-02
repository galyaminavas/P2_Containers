#include "gtest/gtest.h"
#include "../Array.h"

// Test constructors
TEST(testArray, defaultConstructor) {
    Array<int> array;
    ASSERT_EQ(array.size(), 0);
    ASSERT_EQ(array.currCapacity, 16);
}

TEST(testArray, secondaryConstructor) {
    Array<int> array(4);
    ASSERT_EQ(array.size(), 0);
    ASSERT_EQ(array.currCapacity, 4);
}

// Test insert
TEST(testArray, insert) {
    Array<int> array(1);
    ASSERT_EQ(array.size(), 0);
    ASSERT_EQ(array.currCapacity, 1);

    array.insert(1);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array.currCapacity, 1);

    array.insert(2);
    ASSERT_EQ(array.size(), 2);
    ASSERT_EQ(array.currCapacity, 2);

    array.insert(3);
    ASSERT_EQ(array.size(), 3);
    ASSERT_EQ(array.currCapacity, 4);
}

TEST(testArray, insertIndex) {
    Array<int> array(4);
    ASSERT_EQ(array.size(), 0);
    ASSERT_EQ(array.currCapacity, 4);

    array.insert(1);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 1);

    array.insert(0, 2);
    ASSERT_EQ(array.size(), 2);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 1);

    array.insert(1,3);
    ASSERT_EQ(array.size(), 3);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 1);

    array.insert(4);
    ASSERT_EQ(array.size(), 4);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 1);
    ASSERT_EQ(array[3], 4);

    array.insert(0, 5);
    ASSERT_EQ(array.size(), 5);
    ASSERT_EQ(array.currCapacity, 8);
    ASSERT_EQ(array[0], 5);
    ASSERT_EQ(array[1], 2);
    ASSERT_EQ(array[2], 3);
    ASSERT_EQ(array[3], 1);
    ASSERT_EQ(array[4], 4);
}

// Test remove
TEST(testArray, remove) {
    Array<int> array(4);
    array.insert(0, 1);
    array.insert(0, 2);
    array.insert(0, 3);
    array.insert(0, 4);
    ASSERT_EQ(array.size(), 4);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 4);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 2);
    ASSERT_EQ(array[3], 1);

    array.remove(3);
    ASSERT_EQ(array.size(), 3);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 4);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 2);

    array.remove(0);
    ASSERT_EQ(array.size(), 2);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 3);
    ASSERT_EQ(array[1], 2);

    array.remove(0);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array.currCapacity, 4);
    ASSERT_EQ(array[0], 2);

    array.remove(0);
    ASSERT_EQ(array.size(), 0);
    ASSERT_EQ(array.currCapacity, 4);
}

// Test index
TEST(testArray, index) {
    Array<int> array(4);
    array.insert(0, 1);
    array.insert(0, 2);
    array.insert(0, 3);
    array.insert(0, 4);

    int a0 = array[0];
    int a1 = array[1];
    int a2 = array[2];
    int a3 = array[3];
    ASSERT_EQ(a0, 4);
    ASSERT_EQ(a1, 3);
    ASSERT_EQ(a2, 2);
    ASSERT_EQ(a3, 1);

    array[0] = 8;
    array[1] = 6;
    array[2] = 4;
    array[3] = 2;
    ASSERT_EQ(a0, 4);
    ASSERT_EQ(a1, 3);
    ASSERT_EQ(a2, 2);
    ASSERT_EQ(a3, 1);
    ASSERT_EQ(array[0], 8);
    ASSERT_EQ(array[1], 6);
    ASSERT_EQ(array[2], 4);
    ASSERT_EQ(array[3], 2);
}

// Test size
TEST(testArray, size) {
    Array<int> array(4);
    ASSERT_EQ(array.size(), 0);
    array.insert(1);
    ASSERT_EQ(array.size(), 1);
    array.insert(2);
    ASSERT_EQ(array.size(), 2);
    array.insert(3);
    ASSERT_EQ(array.size(), 3);
    array.insert(4);
    ASSERT_EQ(array.size(), 4);
    array.insert(5);
    ASSERT_EQ(array.size(), 5);
}

// Test iterator
TEST(testArray, iterator) {

}
