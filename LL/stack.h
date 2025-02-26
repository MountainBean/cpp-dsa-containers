#ifndef STACK_H
#define STACK_H
/* Sam Drew ~ 2025
 * Stack (data structure) implementation in C++
 * ---
 *  This is a simple implementation of a stack. Written by me, 
 *  for my own edification in data structures and algorithms and C++.
 *
 *  WARNING: Do not use this library in projects. This library is fully 
 *  functional but may lead to confusion with existing C++ standard containers.
 *  Instead use the standard C++ std::list.
 *
 *  Class templating is used to allow the creation of stacks of any 
 *  object type. This version doesn't provide deduction guides so will only 
 *  compile with C++20 or newer.
 */

#include <iostream>

/* Stack template class.
 *  Holds a single object type in a stack of one or more objects
 *  (homogenous).
 *  Initialise with an object to create the first node of the list.
 *  Use the included member functions to add to, remove from and search the 
 *  list.
 *  Member function implementations can be found below the class declaration.
 *  Example:
 *      sjd::Stack myStack {3};     // myList: [3]
 *      myStack.push(4);            // myList: [4, 3]
 *      myStack.pop(2);             // myList: [3]
 *
 *  NOTE: A Class like this is already implemented in the standard C++ library 
 *  as the std::list container. Prefer to use the standard container for all 
 *  collaborative work. 
 */

namespace sjd {

template <typename T>
class Stack {

    struct Node {
        T value {};
        Node* next {nullptr};
    };
public:

    // constructor and destructor
    Stack(const T& value);
    ~Stack();

    // accessors
    Node* peek() { return m_top; }
    int getHeight() { return m_height; }

    void printStack();

    bool push(T value);

    Node* pop();

private:
    Node* m_top {nullptr};
    int m_height {};
};

template <typename T>
Stack<T>::Stack(const T& value)
: m_top { new Node {value}}
, m_height {1}
{
}

template <typename T>
Stack<T>::~Stack() {
    Node* temp {m_top};
    while (temp) {
        temp = temp -> next;
        delete m_top;
        m_top = temp;
    }
}

template <typename T>
void Stack<T>::printStack() {
    Node* temp {m_top};
    while (temp) {
        std::cout << temp->value << "\n";
        temp = temp -> next;
    }
}

template <typename T>
bool Stack<T>::push(T value) {
    Node* newNode {new Node {value, m_top}};
    m_top = newNode;
    ++m_height;
    return true;
}

template <typename T>
Stack<T>::Node* Stack<T>::pop() {
    Node* temp {m_top};
    m_top = m_top -> next;
    temp -> next = nullptr;
    --m_height;
    return temp;
}
} // end namespace sjd
#endif
