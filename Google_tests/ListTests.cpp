#include "gtest/gtest.h"
#include "../List.h"

// Test constructor
TEST(testList, constructor) {
    List<int> list;
    ASSERT_EQ(list.size(), 0);
}

// Test insert
TEST(testList, insertHead) {
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertHead(i + 1);
    }
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head(), 16);
    ASSERT_EQ(list.tail(), 1);
}

TEST(testList, insertTail) {
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(i + 1);
    }
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head(), 1);
    ASSERT_EQ(list.tail(), 16);
}

// Test insert for elements with constructor
TEST(testList, insertHeadString) {
    List<std::string> list;
    for (int i = 0; i < 15; i++) {
        list.insertHead("one");
    }
    list.insertHead("two");
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head(), "two");
    ASSERT_EQ(list.tail(), "one");
}

TEST(testList, insertHeadClass) {
    class MyClass {
    public:
        int number;
        std::string text;

        MyClass() {
            number = 0;
            text = "zero";
        }

        MyClass(int key_, std::string value_) {
            number = key_;
            text = value_;
        }
    };

    List<MyClass> list;
    MyClass arrayToCheck[16];

    for (int i = 0; i < 15; i++) {
        arrayToCheck[i] = MyClass(i, "first");
        list.insertHead(MyClass(i, "first"));
    }
    arrayToCheck[15] = MyClass(15, "second");
    list.insertHead(MyClass(15, "second"));
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head().number, arrayToCheck[15].number);
    ASSERT_EQ(list.head().text, arrayToCheck[15].text);
    ASSERT_EQ(list.tail().number, arrayToCheck[0].number);
    ASSERT_EQ(list.tail().text, arrayToCheck[0].text);

    std::cout << "\n";
}

TEST(testList, insertTailString) {
    List<std::string> list;
    for (int i = 0; i < 15; i++) {
        list.insertTail("one");
    }
    list.insertTail("two");
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head(), "one");
    ASSERT_EQ(list.tail(), "two");
}

TEST(testList, insertTailClass) {
    class MyClass {
    public:
        int number;
        std::string text;

        MyClass() {
            number = 0;
            text = "zero";
        }

        MyClass(int key_, std::string value_) {
            number = key_;
            text = value_;
        }
    };

    List<MyClass> list;
    MyClass arrayToCheck[16];

    for (int i = 0; i < 15; i++) {
        arrayToCheck[i] = MyClass(i, "first");
        list.insertTail(MyClass(i, "first"));
    }
    arrayToCheck[15] = MyClass(15, "second");
    list.insertTail(MyClass(15, "second"));
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head().number, arrayToCheck[0].number);
    ASSERT_EQ(list.head().text, arrayToCheck[0].text);
    ASSERT_EQ(list.tail().number, arrayToCheck[15].number);
    ASSERT_EQ(list.tail().text, arrayToCheck[15].text);

    std::cout << "\n";
}

// Test head & removeHead
TEST(testList, removeHead) {
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertHead(i + 1);
    }
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.head(), 16);
    list.removeHead();
    ASSERT_EQ(list.head(), 15);
    list.removeHead();
    ASSERT_EQ(list.head(), 14);
}

// Test tail & removeTail
TEST(testList, removeTail) {
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(i + 1);
    }
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(list.tail(), 16);
    list.removeTail();
    ASSERT_EQ(list.tail(), 15);
    list.removeTail();
    ASSERT_EQ(list.tail(), 14);
}

// Test size
TEST(testList, size) {
    List<int> list;
    ASSERT_EQ(list.size(), 0);
    for (int i = 0; i < 30; i++) {
        list.insertTail(i + 1);
        ASSERT_EQ(list.size(), i + 1);
    }
}

// Test iterator
TEST(testList, iteratorGet) {
    List<int> list;
    for (int i = 0; i < 15; i++) {
        list.insertTail(i + 1);
    }
    // list of one chunk:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

    auto it = list.iterator();
    for (int i = 0; i < 15; i++) {
        ASSERT_EQ(it.get(), i + 1);
        if (it.hasNext())
            it.next();
    }
    ASSERT_EQ(it.get(), 15);
}

TEST(testList, iteratorSet) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.insertTail(i + 1);
    }
    // list of one chunk:
    // 1 2 3 4 5

    auto it = list.iterator();
    for (int i = 0; i < 5; i++) {
        it.set(i + 2);
        ASSERT_EQ(it.get(), i + 2);
        if (it.hasNext())
            it.next();
    }
    // list after set operations:
    // 2 3 4 5 6

//    list.stupidPrint();
}

TEST(testList, iteratorInsert1) {
    // insert in chunk with enough space
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.insertTail(i + 1);
    }
    // list of one chunk:
    // 1 2 3 4 5

    ASSERT_EQ(list.size(), 5);
    auto it = list.iterator();
    it.insert(100);
    ASSERT_EQ(list.size(), 6);
    ASSERT_EQ(it.get(), 100);
    // list after insert operation:
    // 100 1 2 3 4 5

//    list.stupidPrint();
}

TEST(testList, iteratorInsertString1) {
    // insert in chunk with enough space
    List<std::string> list;
    for (int i = 0; i < 5; i++) {
        list.insertTail(std::to_string(i + 1));
    }
    // list of one chunk:
    // 1 2 3 4 5

    ASSERT_EQ(list.size(), 5);
    auto it = list.iterator();
    it.insert(std::to_string(100));
    ASSERT_EQ(list.size(), 6);
    ASSERT_EQ(it.get(), "100");
    // list after insert operation:
    // 100 1 2 3 4 5

//    list.stupidPrint();
}

TEST(testList, iteratorInsert2) {
    // not enough space in chunk, no next chunk, the new chunk is created
    List<int> list;
    for (int i = 0; i < 15; i++) {
        list.insertTail(i + 1);
    }
    // list of one chunk:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

    ASSERT_EQ(list.size(), 15);
    auto it = list.iterator();
    it.insert(100);
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(it.get(), 100);
    // list after insert operation:
    // 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    // 15

//    list.stupidPrint();
}

TEST(testList, iteratorInsertString2) {
    // not enough space in chunk, no next chunk, the new chunk is created
    List<std::string> list;
    for (int i = 0; i < 15; i++) {
        list.insertTail(std::to_string(i + 1));
    }
    // list of one chunk:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

    ASSERT_EQ(list.size(), 15);
    auto it = list.iterator();
    it.insert(std::to_string(100));
    ASSERT_EQ(list.size(), 16);
    ASSERT_EQ(it.get(), "100");
    // list after insert operation:
    // 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    // 15

//    list.stupidPrint();
}

TEST(testList, iteratorInsert3) {
    // not enough space in chunk, the next chunk exists and has enough space
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(i + 1);
    }
    // list of two chunks:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16

    ASSERT_EQ(list.size(), 16);
    auto it = list.iterator();
    it.insert(100);
    ASSERT_EQ(list.size(), 17);
    ASSERT_EQ(it.get(), 100);
    // list after insert operation:
    // 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    // 15 16

//    list.stupidPrint();
}

TEST(testList, iteratorInsertString3) {
    // not enough space in chunk, the next chunk exists and has enough space
    List<std::string> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(std::to_string(i + 1));
    }
    // list of two chunks:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16

    ASSERT_EQ(list.size(), 16);
    auto it = list.iterator();
    it.insert("100");
    ASSERT_EQ(list.size(), 17);
    ASSERT_EQ(it.get(), "100");
    // list after insert operation:
    // 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    // 15 16

//    list.stupidPrint();
}

TEST(testList, iteratorInsert4) {
    // not enough space in chunk, the next chunk does not have enough space, the new one created
    List<int> list;
    for (int i = 0; i < 30; i++) {
        list.insertTail(i + 1);
    }
    // list of two chunks:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

    ASSERT_EQ(list.size(), 30);
    auto it = list.iterator();
    it.insert(100);
    ASSERT_EQ(list.size(), 31);
    ASSERT_EQ(it.get(), 100);
    // list after insert operation:
    // 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    // 15
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

//    list.stupidPrint();
}

TEST(testList, iteratorInsertString4) {
    // not enough space in chunk, the next chunk does not have enough space, the new one created
    List<std::string> list;
    for (int i = 0; i < 30; i++) {
        list.insertTail(std::to_string(i + 1));
    }
    // list of two chunks:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

    ASSERT_EQ(list.size(), 30);
    auto it = list.iterator();
    it.insert("100");
    ASSERT_EQ(list.size(), 31);
    ASSERT_EQ(it.get(), "100");
    // list after insert operation:
    // 100 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    // 15
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

//    list.stupidPrint();
}

TEST(testList, iteratorRemove1) {
    // chunk has only 1 element, next and previous chunks exist
    List<int> list;
    for (int i = 0; i < 30; i++) {
        list.insertTail(i + 1);
    }
    auto it = list.iterator();
    for (int i = 0; i < 14; i++) {
        it.next();
    }
    it.insert(100);
    // list:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 100
    // 15
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
    ASSERT_EQ(list.size(), 31);
    it.next();
    // current iterator position:
    // 15
    it.remove();
    ASSERT_EQ(it.get(), 16);
    ASSERT_EQ(list.size(), 30);
    // list after remove:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 100
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30

//    list.stupidPrint();
}

TEST(testList, iteratorRemove2) {
    // chunk has only 1 element, next chunk exists, no previous chunk
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertHead(i + 1);
    }
    // list:
    // 16
    // 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

    auto it = list.iterator();
    ASSERT_EQ(it.get(), 16);
    ASSERT_EQ(list.size(), 16);
    it.remove();
    ASSERT_EQ(it.get(), 15);
    ASSERT_EQ(list.size(), 15);
    // list after remove:
    // 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

//    list.stupidPrint();
}

TEST(testList, iteratorRemove3) {
    // chunk has only 1 element, previous chunk exists, no next chunk
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(i + 1);
    }
    // list:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16

    auto it = list.iterator();
    while (it.hasNext()) {
        it.next();
    }
    ASSERT_EQ(it.get(), 16);
    ASSERT_EQ(list.size(), 16);
    it.remove();
    ASSERT_EQ(it.get(), 15);
    ASSERT_EQ(list.size(), 15);
    // list after remove:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

//    list.stupidPrint();
}

TEST(testList, iteratorRemove4) {
    // list has only one element
    List<int> list;
    list.insertTail(1);
    // list:
    // 1

    auto it = list.iterator();
    ASSERT_EQ(it.get(), 1);
    ASSERT_EQ(list.size(), 1);
    it.remove();
    ASSERT_EQ(list.size(), 0);
}

TEST(testList, iteratorRemove5) {
    // chunk has more than one element
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.insertTail(i + 1);
    }
    // list:
    // 1 2 3 4 5

    auto it = list.iterator();
    // remove first element
    ASSERT_EQ(it.get(), 1);
    ASSERT_EQ(list.size(), 5);
    it.remove();
    ASSERT_EQ(it.get(), 2);
    ASSERT_EQ(list.size(), 4);
    // list after remove:
    // 2 3 4 5

    // remove middle element
    it.next();
    ASSERT_EQ(it.get(), 3);
    it.remove();
    ASSERT_EQ(it.get(), 4);
    ASSERT_EQ(list.size(), 3);
    // list after remove:
    // 2 4 5

    // remove last element
    it.next();
    ASSERT_EQ(it.get(), 5);
    it.remove();
    ASSERT_EQ(it.get(), 4);
    ASSERT_EQ(list.size(), 2);
    // list after remove:
    // 2 4

//    list.stupidPrint();
}

// Test next & hasNext
TEST(testList, iteratorNext) {
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(i + 1);
    }
    // list of two chunks:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16

    auto it = list.iterator();
    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(it.get(), i + 1);
        if (it.hasNext())
            it.next();
    }
    ASSERT_EQ(it.get(), 16);
    ASSERT_FALSE(it.hasNext());
}

// Test prev & hasPrev
TEST(testList, iteratorPrev) {
    List<int> list;
    for (int i = 0; i < 16; i++) {
        list.insertTail(i + 1);
    }
    // list of two chunks:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // 16

    auto it = list.iterator();
    while (it.hasNext()) {
        it.next();
    }
    ASSERT_EQ(it.get(), 16);
    ASSERT_FALSE(it.hasNext());

    for (int i = 15; i >= 0; i--) {
        ASSERT_EQ(it.get(), i + 1);
        if (it.hasPrev())
            it.prev();
    }
    ASSERT_EQ(it.get(), 1);
    ASSERT_FALSE(it.hasPrev());

//    list.stupidPrint();
}
