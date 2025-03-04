#ifndef SMART_LINKED_LIST_H
#define SMART_LINKED_LIST_H
/* Sam Drew ~ 2025
 * Linked List (Smart pointers) implementation in C++
 * ---
 *  This is a simple implementation of a Linked List attempting to utilise 
 *  smart pointers (C++11). Written for my own edification in data structures 
 *  and algorithms and C++.
 *
 *  WARNING: Do not use this library in projects. Instead use the standard C++
 *  std::list.
 *
 *  Class templating is used to allow the creation of Linked Lists of any 
 *  object type. This version uses CTAD (Class Type Argument Deduction) 
 *  and doesn't provide deduction guides so will only compile with C++20 or
 *  newer.
 */

#include <iostream>
#include <memory>

/* Linked List template class.
 *  
 *  Initialise with an object to create the first node of the list.
 *  Use the included member functions to add to, remove from and search the 
 *  list.
 *  Member function implementations can be found below the class declaration.
 *  Example:
 *      sjd::LinkedList myList {3};     // myList: [3]
 *      myList.append(4);               // myList: [3, 4]
 *      myList.prepend(2);              // myList: [2, 3, 4]
 *      myList.set(0, 1);               // myList: [1, 3, 4]
 *
 *  NOTE: This is already implemented in the standard C++ library as the 
 *  std::forward_list container. Prefer to use the standard container for all 
 *  collaborative work. 
 */
namespace sjd {
template <typename T>
class SmartLinkedList {
public:

    //Templated data aggregate to hold each node in a linked list
    class Node {
    public:
        T value     {};             // some object of any type
        std::shared_ptr<Node> next  {nullptr};      // null pointer which will point to the next node
        ~Node(){
            std::cout << "destroying Node: " << value << "\n";
        }
    };

    //---
    /*  Implementation of member functions included as most are templated. The 
     *  compiler therefore requires the full definition included.*/
    SmartLinkedList(const T& value)
        : m_head    {std::make_shared<Node>(value)}
        , m_tail    {m_head}
        , m_length  {1}
    {
    }

    // accessors
    std::shared_ptr<Node> begin() const { return m_head; }
    std::shared_ptr<Node> end() const { return m_tail; }
    int length() const { return m_length; }

    bool append(const T& value) {
        if (m_length == 0) {
            m_head = std::make_shared<Node>(value);
            m_tail = m_head;
        }
        else {
            m_tail -> next = std::make_shared<Node>(value);
            m_tail = m_tail -> next;
        }
        ++m_length;
        return true;
    }

    bool prepend(const T& value) {
        if (m_length == 0) {
            return append(value);
        }
        else {
            m_head = std::make_shared<Node>(value, m_head);
        }
        ++m_length;
        return true;
    }

private:

    std::shared_ptr<Node> m_head {nullptr};     // pointer to the first Node in the Linked List.
    std::shared_ptr<Node> m_tail {nullptr};     // pointer to the last Node in the Linked List.
    int m_length {};            // The length of the Linked List.

};


} // end namespace sjd
#endif
