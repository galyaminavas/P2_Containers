#ifndef P2_CONTAINERS_ARRAY_H
#define P2_CONTAINERS_ARRAY_H

#include <iostream>
#include <utility>

template<typename T>
class Array final {
    class Iterator {
        const T& get() const;

        void set(const T& value);

        void insert(const T& value);

        void remove();

        void next();

        void prev();

        void toIndex(int index);

        bool hasNext() const;

        bool hasPrev() const;
    };

    T* arrayStart;
    int elements = 0;
    int currCapacity;
    const int initCapacity = 16;

public:
    Array() {
        arrayStart = new T[initCapacity];
        currCapacity = initCapacity;

        //Debug output
        std::cout << "Array() " << currCapacity << std::endl;
        //\Debug output
    }

    Array(int capacity) {
        arrayStart = new T[capacity];
        currCapacity = capacity;

        //Debug output
        std::cout << "Array(" << currCapacity << ")\n";
        //\Debug output
    }

    ~Array() {
        //При необходимости, при освобождении памяти
        //вызываются деструкторы хранимых элементов.
        for (int i = 0; i < elements; i++) {
            arrayStart[i].~T();
        }
        delete [] arrayStart;

        //Debug output
        std::cout << "~Array\n";
//        for (int i = 0; i < elements; i++) {
//            std::cout << arrayStart[i] << " ";
//        }
//        std::cout << "\n";
        //\Debug output
    }

    void insert(const T& value) {
        if (currCapacity <= elements) {
            currCapacity *= 2;
            T* newArrayStart = new T[currCapacity];
            for (int i = 0; i < elements; i++) {
                newArrayStart[i] = std::move(arrayStart[i]);
            }
//            newArrayStart = std::move(arrayStart); // will not change the address - incorrect!
            for (int i = 0; i < elements; i++) {
                std::cout << &arrayStart[i] << " -> " << &newArrayStart[i] << std::endl;
            }
//            std::cout << arrayStart[0] << std::endl;
//            std::cout << newArrayStart[0] << std::endl;

            delete [] arrayStart;
//            std::cout << *arrayStart << std::endl;
//            std::cout << newArrayStart[0] << std::endl;
            arrayStart = newArrayStart;
        }
        arrayStart[elements] = value;
        elements++;
        std::cout << "Capacity: " << currCapacity << ", Elements: " << elements << std::endl;
        for (int i = 0; i < elements; i++) {
            std::cout << arrayStart[i] << " ";
        }
        std::cout << std::endl;
    }

    void insert(int index, const T& value) {
        if (currCapacity <= elements) {
            currCapacity *= 2;
            T* newArrayStart = new T[currCapacity];
            for (int i = 0; i < index; i++) {
                newArrayStart[i] = std::move(arrayStart[i]);
            }
            newArrayStart[index] = value;
            for (int i = index; i < elements; i++) {
                newArrayStart[i + 1] = std::move(arrayStart[i]);
            }
            elements++;

            //Debug output
            for (int i = 0; i < elements; i++) {
                std::cout << &arrayStart[i] << " -> " << &newArrayStart[i] << std::endl;
            }
            //\Debug output

            delete [] arrayStart;
            arrayStart = newArrayStart;
//            std::swap(newArrayStart, arrayStart);
        } else {
            for (int i = elements; i > index - 1; i--) {
                arrayStart[i] = std::move(arrayStart[i - 1]);
            }
            arrayStart[index - 1] = value;
            elements++;
        }

        //Debug output
        std::cout << "Capacity: " << currCapacity << ", Elements: " << elements << std::endl;
        for (int i = 0; i < elements; i++) {
            std::cout << arrayStart[i] << " ";
        }
        std::cout << std::endl;
        //\Debug output
    }

    void remove(int index) {
        for (int i = index; i < elements - 1; i++) {
            arrayStart[i] = std::move(arrayStart[i + 1]);
        }
        arrayStart[elements - 1].~T();
        elements--;

        //Debug output
        std::cout << "Capacity: " << currCapacity << ", Elements: " << elements << std::endl;
        for (int i = 0; i < elements; i++) {
            std::cout << arrayStart[i] << " ";
        }
        std::cout << std::endl;
        //\Debug output
    }

    const T& operator[](int index) const {
        return arrayStart[index];
    }

    T& operator[](int index) {
        return arrayStart[index];
    }

    int size() const {
        return elements;
    }

    Iterator iterator() {

    }

    const Iterator iterator() const {

    }

    //запрет копирования и присваивания
    //copy
    Array(const Array<T> &a) = delete;
    //assignment
    Array<T> operator=(const Array<T> &a) = delete;
};

#endif //P2_CONTAINERS_ARRAY_H
