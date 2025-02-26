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
 *      myQueue.pop(2);             // myList: [4]
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

    Queue(const T& value)
        : m_head {new Node {value}}
        , m_tail {m_head}
        , m_length {1}
    {
    }

    ~Queue() {
        Node* temp {m_head};
        while (temp) {
            temp = temp -> next;
            delete m_head;
            m_head = temp;
        }
    }

    Node* begin() { return m_head; }
    Node* end() { return m_tail; }
    int length() { return m_length; }

    void printQueue() {
        Node* temp {m_head};
        while (temp) {
            std::cout << temp -> value << "\n";
            temp = temp -> next;
        }
    }

private:
    Node* m_head {nullptr};
    Node* m_tail {nullptr};
    int m_length {};
};
} // end namespace sjd
#endif
