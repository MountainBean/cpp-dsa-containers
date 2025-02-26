#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
/* Sam Drew ~ 2025
 * Doubly Linked List implementation in C++
 * ---
 *  This is a simple implementation of a Doubly Linked List. Written by me, 
 *  for my own edification in data structures and algorithms and C++.
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

/* Doubly Linked List template class.
 *  Holds a single object type in a doubly linked list of one or more objects
 *  (homogenous).
 *  Initialise with an object to create the first node of the list.
 *  Use the included member functions to add to, remove from and search the 
 *  list.
 *  Member function implementations can be found below the class declaration.
 *  Example:
 *      sjd::DoublyLinkedList myList {3};   // myList: [3]
 *      myList.append(4);                   // myList: [3, 4]
 *      myList.prepend(2);                  // myList: [2, 3, 4]
 *      myList.set(1, 1);                   // myList: [2, 1, 4]
 *
 *  NOTE: A Class like this is already implemented in the standard C++ library 
 *  as the std::list container. Prefer to use the standard container for all 
 *  collaborative work. 
 */
namespace sjd {
    template <typename T>
    class DoublyLinkedList {
    public:
        
        struct Node {

            T value {};
            Node* next {nullptr};
            Node* prev {nullptr};

        };

        // accessors
        Node* getHead() const { return m_head; }
        Node* getTail() const { return m_tail; }
        int getLength() const { return m_tail; }

        // constructor and destructor
        explicit DoublyLinkedList(const T& value);
        ~DoublyLinkedList();

        void printList() const;

        bool append(const T& value);

        bool prepend(const T& value);

        Node* pop();

        Node* popFirst();

        Node* get(int index);

        bool setValue(int index, const T& value);

        bool insert(int index, const T& value);

        Node* remove(int index);

        bool swapFirstLast();

        bool reverse();

        bool isPalindrome();

    private:

        Node* m_head {nullptr};
        Node* m_tail {nullptr};
        int m_length {};

    };

    template <typename T>
    DoublyLinkedList<T>::DoublyLinkedList(const T& value)
        : m_head    { new Node{value} }
        , m_tail    { m_head }
        , m_length  { 1 }
    {
    }

    template <typename T>
    DoublyLinkedList<T>::~DoublyLinkedList() {
        Node* temp {m_head};
        while(m_head) {
            m_head = m_head->next;
            delete temp;
            temp = m_head;
        }
    }

    template <typename T>
    void DoublyLinkedList<T>::printList() const {
        Node* temp {m_head};
        while(temp){
            std::cout << temp->value << "\n";
            temp = temp->next;
        }
    }

    /*  O(1)
     *  Uses the tail pointer to add the given node value to the end of the list
     */
    template <typename T>
    bool DoublyLinkedList<T>::append(const T& value) {
        Node* newNode {new Node {value}};
        if(m_length == 0){
            m_head = newNode;
        } else{
            m_tail->next = newNode;
            newNode->prev = m_tail;
        }
        m_tail = newNode;
        ++m_length;
        return true;
    }

    /*  O(1)
     *  Uses the head pointer and its prev pointer to add the new node to the 
     *  beginning of the list. */
    template <typename T>
    bool DoublyLinkedList<T>::prepend(const T& value) {
        Node* newNode {new Node {value}};
        if (m_length == 0) {
            m_head = newNode;
        } else {
            m_head -> prev = newNode;
            newNode -> next = m_head;
            m_head = newNode;
        }
        ++m_length;
        return true;
    }

    template <typename T>
    DoublyLinkedList<T>::Node* DoublyLinkedList<T>::pop(){

        if ( m_length == 0 ) {
            return nullptr;
        }
        Node* temp { m_tail };
        m_tail = m_tail -> prev;

        if ( m_length == 1 ) {
            m_head = nullptr;

        } else {
            m_tail -> next = nullptr;
            temp -> prev = nullptr;
        }
        --m_length;

        return temp;
    }

    template <typename T>
    DoublyLinkedList<T>::Node* DoublyLinkedList<T>::popFirst(){

        if ( m_length == 0 ) {
            return nullptr;
        }
        Node* temp { m_head };
        m_head = m_head -> next;
        if ( m_length == 1 ) {
            m_tail = nullptr;
        } else {
            m_head -> prev = nullptr;
            temp -> next = nullptr;
        }
        --m_length;

        return temp;
    }

    template <typename T>
    DoublyLinkedList<T>::Node* DoublyLinkedList<T>::get(int index){
        if (index < 0 || index >= m_length) {
            return nullptr;
        }
        if (index < (m_length / 2)) {
            Node* temp {m_head};
            while (index > 0) {
                temp = temp -> next;
                --index;
            }
            return temp;
        } else {
            Node* temp {m_tail};
            while (index < (m_length - 1)) {
                temp = temp -> prev;
                ++index;
            }
            return temp;
        }
    }

    template <typename T>
    bool DoublyLinkedList<T>::setValue(int index, const T& value){
        if (index < 0 || index >= m_length) {
            return false;
        }
        Node* temp {get(index)};
        if ( temp ) {
            temp -> value = value;
            return true;
        }
        return false;
    }

    template <typename T>
    bool DoublyLinkedList<T>::insert(int index, const T& value){
        if (index < 0 || index >= m_length) {
            return false;
        }
        if (index == 0) {
            return prepend(value);
        }
        if (index == m_length) {
            return append(value);
        }
        Node* temp {get(index)};
        if ( temp ) {
            Node* newNode {new Node {value, temp, temp -> prev}};
            temp -> prev -> next = newNode;
            temp -> prev = newNode;
            ++m_length;
            return true;
        }
        return false;
    }

    template <typename T>
    DoublyLinkedList<T>::Node* DoublyLinkedList<T>::remove(int index){
        Node* temp {get(index)};
        if ( temp != nullptr ) {
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            temp -> prev = nullptr;
            temp -> next = nullptr;
            --m_length;
        }
        return temp;
    }

    template <typename T>
    bool DoublyLinkedList<T>::swapFirstLast(){
        std::cout << "Not implemented\n";
    }

    template <typename T>
    bool DoublyLinkedList<T>::reverse(){
        std::cout << "Not implemented\n";
    }

    template <typename T>
    bool DoublyLinkedList<T>::isPalindrome(){
        std::cout << "Not implemented\n";
    }
}
#endif
