#ifndef P2_CONTAINERS_LIST_H
#define P2_CONTAINERS_LIST_H

//#include <iostream>

// chunk 15 elements to fit in
// the cache line of 64 bytes for T==int
#define chunkSize_ 15

template<typename T>
struct Chunk {
public:
    int elements_ = 0;
    T data_[chunkSize_];
//    T* data_ = new T[chunkSize_];
//    T* data_ = (T*)malloc(14 * sizeof(T));
    Chunk<T>* next = nullptr;
    Chunk<T>* prev = nullptr;

    void insertHead(const T& value) {
        for (int i = elements_; i > 0; i--) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[0] = value;
        elements_++;
    }

    void insertTail(const T& value) {
        data_[elements_] = value;
        elements_++;
    }

    void removeHead() {
        data_[0].~T();
        for (int i = 0; i < elements_ - 1; i++) {
            data_[i] = std::move(data_[i + 1]);
        }
        elements_--;
    }

    void removeTail() {
        data_[elements_ - 1].~T();
        elements_--;
    }

    Chunk() {
        std::cout << "Chunk()\n";
    }

    ~Chunk() {
        //При необходимости, при освобождении памяти
        //вызываются деструкторы хранимых элементов.
        for (int i = 0; i < elements_; i++) {
            data_[i].~T();
//            std::cout << "~elem\n";
        }
//        delete [] data_;
//        free(data_);
        std::cout << "~Chunk\n";
    }

    void printChunk() {
        for (int i = 0; i < elements_; i++) {
            std::cout << data_[i] << " ";
        }
        std::cout << "\n";
    }
};

template<typename T>
class List final {
private:
    Chunk<T>* head_;
    Chunk<T>* tail_;
    int size_ = 0;

public:
    class Iterator {
    private:
        List<T>& list_;
        int currentIndexInList_ = 0;
        int currentIndexInChunk_ = 0;
        Chunk<T>* currentChunk_ = list_.head_;
//        T* currentElement_ = &list_.head();
    public:
        Iterator(List<T>& a): list_(a) {}

        const T& get() const {
            return currentChunk_->data_[currentIndexInChunk_];
        }

        void set(const T& value) {
            currentChunk_->data_[currentIndexInChunk_] = value;
        }

        void insert(const T& value);


        void remove();


        void next() {
            if (currentIndexInChunk_ < currentChunk_->elements_ - 1) {
                currentIndexInChunk_++;
                currentIndexInList_++;
            } else {
                currentChunk_ = currentChunk_->next;
                currentIndexInChunk_ = 0;
                currentIndexInList_++;
            }
        }

        void prev() {
            if (currentIndexInChunk_ > 0) {
                currentIndexInChunk_--;
                currentIndexInList_--;
            } else {
                currentChunk_ = currentChunk_->prev;
                currentIndexInChunk_ = currentChunk_->elements_ - 1;
                currentIndexInList_--;
            }
        }

        bool hasNext() const {
            return (currentIndexInList_ < list_.size() - 1);
        }

        bool hasPrev() const {
            return (currentIndexInList_ > 0);
        }
    };

    List() {
        std::cout << "List() enter\n";
        head_ = new Chunk<T>();
        tail_ = head_;
        std::cout << "List() exit\n";
    }

    ~List() {
        Chunk<T>* currChunk = head_;
        Chunk<T>* nextChunk;
        while (currChunk != nullptr) {
            nextChunk = currChunk->next;
            //При необходимости, при освобождении памяти
            //вызываются деструкторы хранимых элементов.
//            currChunk->~Chunk();
            delete currChunk;
            currChunk = nextChunk;
        }
        std::cout << "~List\n";
    }

    void insertHead(const T& value) {
        if (head_->elements_ < chunkSize_) {
            head_->insertHead(value);
        } else {
            Chunk<T>* newHead_ = new Chunk<T>();
            newHead_->insertHead(value);
            newHead_->next = head_;
            head_->prev = newHead_;
            head_ = newHead_;
        }
        size_++;
    }

    void insertTail(const T& value) {
        if (tail_->elements_ < chunkSize_) {
            tail_->insertTail(value);
        } else {
            Chunk<T>* newTail_ = new Chunk<T>();
            newTail_->insertTail(value);
            newTail_->prev = tail_;
            tail_->next = newTail_;
            tail_ = newTail_;
        }
        size_++;
    }

    void stupidPrint() {
        Chunk<T>* curr = head_;
        while (curr != nullptr) {
            curr->printChunk();
            curr = curr->next;
        }
    }

    void removeHead() {
        if (head_->elements_ == 0 || size_ == 0) { // redundant condition but let it be
            return;
        } else if (head_->elements_ > 1 || size_ == 1) {
            head_->removeHead();
        } else {
            Chunk<T>* newHead_ = head_->next;
            newHead_->prev = nullptr;
            delete head_;
            head_ = newHead_;
        }
        size_--;
    }

    void removeTail() {
        if (tail_->elements_ == 0 || size_ == 0) { // redundant condition but let it be
            return;
        } else if (tail_->elements_ > 1 || size_ == 1) {
            tail_->removeTail();
        } else {
            Chunk<T>* newTail_ = tail_->prev;
            newTail_->next = nullptr;
            delete tail_;
            tail_ = newTail_;
        }
        size_--;
    }

    const T& head() const {
        return head_->data_[0];
    }

    const T& tail() const {
        return tail_->data_[tail_->elements_ - 1];
    }

    int size() const {
        return size_;
    }

    Iterator iterator() {
        return Iterator(*this);
    }

    const Iterator iterator() const {
        return Iterator(*this);
    }

    //запрет копирования и присваивания
    //copy
    List(const List<T> &a) = delete;
    //assignment
    List<T> operator=(const List<T> &a) = delete;
};

#endif //P2_CONTAINERS_LIST_H
