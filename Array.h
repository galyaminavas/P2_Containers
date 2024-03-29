#ifndef P2_CONTAINERS_ARRAY_H
#define P2_CONTAINERS_ARRAY_H

//#include <iostream>
//#include <utility>

template<typename T>
class Array final {
    void *rawMem;
    T* data_;
    int elementsCount_ = 0;
    const int initCapacity_ = 16;

public:
    class Iterator {
    private:
        Array<T>& array_;
        int currentIndex_ = 0;
        T* currentElement_ = &array_[0];
        // for hasNext & hasPrev
//        T* arrayStart_ = &array_[0];

    public:
        Iterator(Array<T>& a): array_(a) {}

        const T& get() const {
            return *currentElement_;
        }

        void set(const T& value) {
            *currentElement_ = value;
//            array_[currentIndex_] = value; // this kinda works too
        }

        void insert(const T& value) {
            array_.insert(currentIndex_, value);
        }

        void remove() {
            // if we remove the last element
            if (currentIndex_ == array_.size() - 1) {
                currentElement_--;
                array_.remove(currentIndex_);
                currentIndex_--;
            } else {
                array_.remove(currentIndex_);
            }
        }

        void next() {
            currentIndex_++;
            currentElement_++;
        }

        void prev() {
            currentIndex_--;
            currentElement_--;
        }

        void toIndex(int index) {
            currentIndex_= index;
            currentElement_ = &array_[index];
        }

        bool hasNext() const {
            // trying to update hasNext
//            return (currentElement_ != (arrayStart_ + array_.size()));
            return (currentIndex_ < array_.size() - 1);
        }

        bool hasPrev() const {
            // trying to update hasPrev
//            return (currentElement_ != (arrayStart_ - 1));
            return (currentIndex_ > 0);
        }
    };

    int currCapacity;

    Array() {
        rawMem = malloc(initCapacity_ * sizeof(T));
        data_ = (T *) rawMem;
//        data_ = new(rawMem) T[initCapacity_];
//        for (int i = 0; i < initCapacity_; i++) {
//            new(data_ + i) T;
//        }


//        data_ = (T *)malloc(initCapacity_ * sizeof(T));
//        data_ = new T[initCapacity_];
        currCapacity = initCapacity_;

        //Debug output
//        std::cout << "Array() " << currCapacity << std::endl;
        //\Debug output
    }

    Array(int capacity) {
        rawMem = malloc(capacity * sizeof(T));
        data_ = (T *) rawMem;
//        for (int i = 0; i < capacity; i++) {
//            new(data_ + i) T;
//        }


//        data_ = (T *)malloc(capacity * sizeof(T));
//        data_ = new T[capacity];
        currCapacity = capacity;

        //Debug output
//        std::cout << "Array(" << currCapacity << ")\n";
        //\Debug output
    }

    ~Array() {
        //При необходимости, при освобождении памяти
        //вызываются деструкторы хранимых элементов.
        for (int i = 0; i < elementsCount_; i++) {
            data_[i].~T();
        }
        free(rawMem);
//        free(data_);

//        delete [] data_;

        //Debug output
//        std::cout << "~Array\n";
        //\Debug output
    }

    void insert(const T& value) {
        if (currCapacity <= elementsCount_) {
            currCapacity *= 2;
            void *newRawMem = malloc(currCapacity * sizeof(T));
            T* newArrayStart = (T*) newRawMem;
//            T* newArrayStart = (T *)malloc(currCapacity * sizeof(T));

//            T* newArrayStart = new T[currCapacity];
            for (int i = 0; i < elementsCount_; i++) {\
                new(newArrayStart + i) T;
                newArrayStart[i] = std::move(data_[i]);
            }
//            newArrayStart = std::move(data_); // will not change the address - incorrect!
            //Debug output
//            for (int i = 0; i < elementsCount_; i++) {
//                std::cout << &data_[i] << " -> " << &newArrayStart[i] << std::endl;
//            }
            //\Debug output

            free(rawMem);
//            free(data_);

//            delete [] data_;

            data_ = newArrayStart;
            rawMem = newRawMem;
        }
        new(data_ + elementsCount_) T;
        data_[elementsCount_] = value;
        elementsCount_++;

        //Debug output
//        std::cout << "Capacity: " << currCapacity << ", Elements: " << elementsCount_ << std::endl;
//        for (int i = 0; i < elementsCount_; i++) {
//            std::cout << data_[i] << " ";
//        }
//        std::cout << std::endl;
        //\Debug output
    }

    void insert(int index, const T& value) {
        if (currCapacity <= elementsCount_) {
            currCapacity *= 2;
            void *newRawMem = malloc(currCapacity * sizeof(T));
            T* newArrayStart = (T*) newRawMem;
//            T* newArrayStart = (T *)malloc(currCapacity * sizeof(T));
//            T* newArrayStart = new T[currCapacity];
            for (int i = 0; i < index; i++) {
                new(newArrayStart + i) T;
                newArrayStart[i] = std::move(data_[i]);
            }
            new(newArrayStart + index) T;
            newArrayStart[index] = value;
            for (int i = index; i < elementsCount_; i++) {
                new(newArrayStart + i + 1) T;
                newArrayStart[i + 1] = std::move(data_[i]);
            }
            elementsCount_++;

            //Debug output
//            for (int i = 0; i < elementsCount_; i++) {
//                std::cout << &data_[i] << " -> " << &newArrayStart[i] << std::endl;
//            }
            //\Debug output
            free(rawMem);
//            free(data_);

//            delete [] data_;
            data_ = newArrayStart;
            rawMem = newRawMem;
        } else {
            new (data_ + elementsCount_) T;
            for (int i = elementsCount_; i > index; i--) {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[index] = value;
            elementsCount_++;
        }

        //Debug output
//        std::cout << "Capacity: " << currCapacity << ", Elements: " << elementsCount_ << std::endl;
//        for (int i = 0; i < elementsCount_; i++) {
//            std::cout << data_[i] << " ";
//        }
//        std::cout << std::endl;
        //\Debug output
    }

    void remove(int index) {
        for (int i = index; i < elementsCount_ - 1; i++) {
            data_[i] = std::move(data_[i + 1]);
        }
        data_[elementsCount_ - 1].~T();
        elementsCount_--;

        //Debug output
//        std::cout << "Capacity: " << currCapacity << ", Elements: " << elementsCount_ << std::endl;
//        for (int i = 0; i < elementsCount_; i++) {
//            std::cout << data_[i] << " ";
//        }
//        std::cout << std::endl;
        //\Debug output
    }

    const T& operator[](int index) const {
        return data_[index];
    }

    T& operator[](int index) {
        return data_[index];
    }

    int size() const {
        return elementsCount_;
    }

    Iterator iterator() {
        return Iterator(*this);
    }

    const Iterator iterator() const {
        return Iterator(*this);
    }

    //запрет копирования и присваивания
    //copy
    Array(const Array &a) = delete;
    //assignment
    Array operator=(const Array &a) = delete;
};

#endif //P2_CONTAINERS_ARRAY_H
