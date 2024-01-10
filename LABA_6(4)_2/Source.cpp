#include <iostream>
#include <new>


using namespace std;

template <typename T>
class QueueBasedOnBidirectionalCircularList {
private:
    template <typename T>
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;

        Node(T data = T(), Node* next = nullptr, Node* prev = nullptr) {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    Node<T>* front;
    Node<T>* rear;
    int size;

public:

    int GetSize() const {
        return size;
    };
    void clear();
    //bool Enqueue(const T& element);
    //bool Dequeue(T& element);
    bool Peek(T& element) const;
    bool Push(const T& element);
    bool Pop(T& element);
    QueueBasedOnBidirectionalCircularList();
    QueueBasedOnBidirectionalCircularList(const QueueBasedOnBidirectionalCircularList<T>& other);
    QueueBasedOnBidirectionalCircularList(QueueBasedOnBidirectionalCircularList<T>&& other);
    QueueBasedOnBidirectionalCircularList(std::initializer_list<T> ilist);
    ~QueueBasedOnBidirectionalCircularList();
    QueueBasedOnBidirectionalCircularList<T>& operator=(const QueueBasedOnBidirectionalCircularList<T>& other);
    QueueBasedOnBidirectionalCircularList<T>& operator=(QueueBasedOnBidirectionalCircularList<T>&& other);
    QueueBasedOnBidirectionalCircularList<T>& operator=(std::initializer_list<T> ilist);
};

template<typename T>
QueueBasedOnBidirectionalCircularList<T>::QueueBasedOnBidirectionalCircularList()
{
    size = 0;
    front = nullptr;
    rear = nullptr;
}

template<typename T>
QueueBasedOnBidirectionalCircularList<T>::~QueueBasedOnBidirectionalCircularList() {
    clear();
}

template <typename T>
QueueBasedOnBidirectionalCircularList<T>::QueueBasedOnBidirectionalCircularList(const QueueBasedOnBidirectionalCircularList<T>& other) : front(nullptr), rear(nullptr), size(0) {
    *this = other;
}

template <typename T>
QueueBasedOnBidirectionalCircularList<T>::QueueBasedOnBidirectionalCircularList(QueueBasedOnBidirectionalCircularList<T>&& other) : front(nullptr), rear(nullptr), size(0) {
    *this = std::move(other);
}

template <typename T>
QueueBasedOnBidirectionalCircularList<T>::QueueBasedOnBidirectionalCircularList(std::initializer_list<T> ilist) : front(nullptr), rear(nullptr), size(0) {
    *this = ilist;
}

template <typename T>
QueueBasedOnBidirectionalCircularList<T>& QueueBasedOnBidirectionalCircularList<T>::operator=(const QueueBasedOnBidirectionalCircularList<T>& other) {
    if (this != &other) {
        clear();
        if (other.front != nullptr) {
            Node<T>* currentOther = other.front->next;
            do {
                if (!Enqueue(currentOther->data)) {
                    clear();
                    throw std::bad_alloc();
                }
                currentOther = currentOther->next;
            } while (currentOther != other.front->next);
        }
    }

    return *this;
}

template <typename T>
QueueBasedOnBidirectionalCircularList<T>& QueueBasedOnBidirectionalCircularList<T>::operator=(QueueBasedOnBidirectionalCircularList<T>&& other) {
    if (this != &other) {
        clear();
        front = other.front;
        rear = other.rear;
        size = other.size;
        other.front = nullptr;
        other.rear = nullptr;
        other.size = 0;
    }

    return *this;
}

template <typename T>
QueueBasedOnBidirectionalCircularList<T>& QueueBasedOnBidirectionalCircularList<T>::operator=(std::initializer_list<T> ilist) {
    clear();
    for (const T& item : ilist) {
        Enqueue(item);
    }
    return *this;
}

template<typename T>
void QueueBasedOnBidirectionalCircularList<T>::clear() {
    Node<T>* nextNode;
    while (size > 0) {
        nextNode = front->next;
        delete front;
        front = nextNode;
        --size;
    }
    front = nullptr;
    rear = nullptr;
}


template<typename T>
bool QueueBasedOnBidirectionalCircularList<T>::Push(const T& element) {
    Node<T>* newNode = new(std::nothrow) Node<T>(element);
    if (newNode == nullptr) {
        return false;
    }
    if (size > 0) {
        rear->next = newNode;
        newNode->prev = rear;
    }
    rear = newNode;
    if (size == 0) {
        front = newNode;
    }
    size++;
    return true;
}

template<typename T>
bool QueueBasedOnBidirectionalCircularList<T>::Pop(T& element) {
    if (front == nullptr) {
        return false;
    }
    element = front->data;
    Node<T>* toDelete = front;
    if (size == 1) {
        front = nullptr;
        rear = nullptr;
    }
    else {
        front = front->next;
        front->prev = rear;
        rear->next = front;
    }
    delete toDelete;
    --size;
    return true;
}

template<typename T>
bool QueueBasedOnBidirectionalCircularList<T>::Peek(T& element) const {
    if (front == nullptr) {
        return false;
    }
    element = front->data;
    return true;
}