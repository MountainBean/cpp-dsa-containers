#ifndef QUEUE_H
#define QUEUE_H
/* Sam Drew ~ 2025
 * Queue (data structure) implementation in C++
 * ---
 *  This is a simple implementation of a queue. Written by me, 
 *  for my own edification in data structures and algorithms and C++.
 *
 *  WARNING: Do not use this library in projects. This library is fully 
 *  functional but may lead to confusion with existing C++ standard containers.
 *  Instead use the standard C++ std::list.
 *
 *  Class templating is used to allow the creation of queues of any 
 *  object type. This version doesn't provide deduction guides so will only 
 *  compile with C++20 or newer.
 *  ---
 */

#include <iostream>
#include <new>

namespace sjd {

/* Queue template class.
 *  Holds a single object type in a queue of one or more objects
 *  (homogenous). Only takes from the front of the queue and always appends
 *  to the end.
 *  Initialise with an object to create the first node of the queue.
 *  Use the included member functions to add to and remove from the queue.
 *  Member function implementations can be found below the class declaration.
 *  Example:
 *      sjd::Queue myQueue {3};     // myList: [3]
 *      myQueue.enqueue(4);         // myList: [3, 4]
 *      myQueue.dequeue(2);         // myList: [4]
 *
 *  NOTE: A Class like this is already implemented in the standard C++ library 
 *  as the std::list container. Prefer to use the standard container for all 
 *  collaborative work. 
 */
template <typename T>
class Queue {

    struct Node {
        T value {};
        Node* next {nullptr};
    };

public:

    // constructor + destructor
    Queue(const T& value);
    ~Queue();

    // Copy constructor
    void deepCopy(const Queue& source);
    Queue(const Queue& source) { deepCopy(source); }

    // accessors
    Node* begin() { return m_head; }
    Node* end() { return m_tail; }
    int length() { return m_length; }

    void printQueue();

    bool enqueue(const T& value);

    Node* dequeue();

    Queue& operator=(const Queue& source);

private:
    Node* m_head {nullptr};
    Node* m_tail {nullptr};
    int m_length {};
};

template <typename T>
Queue<T>::Queue(const T& value)
    : m_head {new (std::nothrow) Node {value}}
    , m_tail {m_head}
    , m_length {1}
{
    if (!m_head) {
        m_length = 0;
        std::cout << "Could not allocate memory!\n";
    }
}

template <typename T>
Queue<T>::~Queue() {
    Node* temp {m_head};
    while (temp) {
        temp = temp -> next;
        delete m_head;
        m_head = temp;
    }
}

template <typename T>
void Queue<T>::deepCopy(const Queue& source){

    delete m_head;
    delete m_tail;

    m_length = source.m_length;

    if (source.m_head) {

        m_head = new Node{source.m_head -> value};
        m_tail = m_head;
        Node* sourceTemp {source.m_head -> next};

        while (sourceTemp) {
            m_tail -> next = new Node {sourceTemp -> value};
            sourceTemp = sourceTemp -> next;
            m_tail = m_tail -> next;
        }
    }
    else {
        m_head = nullptr;
        m_tail = nullptr;
    }
}

template <typename T>
void Queue<T>::printQueue() {
    Node* temp {m_head};
    while (temp) {
        std::cout << temp -> value << "\n";
        temp = temp -> next;
    }
}

template <typename T>
bool Queue<T>::enqueue(const T& value) {
    Node* newNode {new (std::nothrow) Node {value}};
    if (!newNode) {
        std::cout << "Could not allocate memory!\n";
        return false;
    }
    if (m_length == 0) {
        m_head = newNode;
        m_tail = newNode;
    } else {
        m_tail -> next = newNode;
        m_tail = newNode;
    }
    ++m_length;
    return true;
}

template <typename T>
Queue<T>::Node* Queue<T>::dequeue() {
    if (m_length == 0) {
        return nullptr;
    }
    Node* temp {m_head};
    if (m_length == 1) {
        m_tail = nullptr;
    }
    m_head = m_head -> next;
    temp -> next = nullptr;
    --m_length;
    return temp;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& source){
    if (this != &source) {
        deepCopy(source);
    }
    return *this;
}


} // end namespace sjd
#endif
