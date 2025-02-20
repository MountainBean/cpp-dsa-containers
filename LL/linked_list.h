/* Linked List (Class Template)
 * Samuel Drew ~ 2025 
 * ---
 *  This is a simple implementation of a Linked List.
 *  Class templating is used to allow the creation of Linked Lists of any 
 *  object type. This version used CTAD (Class Type Argument Deduction) 
 *  and doesn't provide deduction guides so will only compile with C++20 or
 *  newer.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

//  Member function implementations can be found below the class declaration
template <typename T>
class LinkedList {
public:

    /* (Singly) Linked list node struct
     * Templated data aggregate to hold each node in a linked list
     */
    struct Node {

        T value     {};             // some object of any type
        Node* next  {nullptr};      // null pointer which will point to the next node

    };

    Node* getHead() const { return m_head; }
    Node* getTail() const { return m_tail; }
    T getLength() const { return m_length; }

    //! Constructor method. 
    /* Initialises the list using member initialisation list with the given 
     * object (value) as the 1st item.
     */
    explicit LinkedList(T value);

    //! Destructor method. Iterates along the list, releasing each Node from memory.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    ~LinkedList();

    //! prints the linked list items. One item per line.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    void printList() const;

    //! Adds the given value to the end of the List in a Node.
    /*! O(1). This method will use the tail pointer to alter the last Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List.
     */
    bool append(T value);

    //! Deletes the last Node in the List.
    /*! O(n). This method must iterate through each member of the list to find 
     * the 2nd-to-last item. Making it O(n) where n = the number of Nodes in the 
     * list. 
     */
    void deleteLast();

    //! Removes the first value from the front of the List.
    /*! O(1). This method will use the head pointer to alter the first Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List.
     */
    void deleteFirst();

    //! Adds the given value to the front of the List.
    /*! O(1). This method will use the head pointer to alter the first Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List. 
     */
    void prepend(T value);

    //! Returns the Node at the position given.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    Node* get(int index) const;

    //! Change the value of the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    bool set(int index, T value);

    //! inserts the given value in a Node before the given index in the List
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    bool insert(int index, T value);

    //! Deletes the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    void deleteNode(int index);

    //! flips the List around so that head is tail and tail is head.
    /*! O(n). The List must be iterated down so the complexity is O(n) where 
     * n = length of the List.
     */
    void reverse();

    //! Finds and returns the middle Node in the List.
    Node* middle();

private:

    Node* m_head {nullptr};      // pointer to the first Node in the Linked List.
    Node* m_tail {nullptr};      // pointer to the last Node in the Linked List.
    int m_length {};                   // The length of the Linked List.

};



//---
/*  Implementation of member functions included as most are templated. The 
 *  compiler therefore requires the full definition included.
 */
template <typename T>
inline LinkedList<T>::LinkedList(T value)
    : m_head    {new LinkedList<T>::Node{value}}
    , m_tail    {m_head}
    , m_length  {1}
{
}

//! Destructor method. Iterates along the list, releasing each Node from memory.
/*! O(n). This method iterates through each member of of the list making it O(n) 
 * where n = the number of Nodes in the list. */
template <typename T>
inline LinkedList<T>::~LinkedList(){
    LinkedList<T>::Node* temp {m_head};
    while(m_head){
        m_head = m_head->next;
        delete temp;
        temp = m_head;
    }
}

//! prints the linked list items. One item per line.
/*! O(n). This method iterates through each member of of the list making it O(n) 
 * where n = the number of Nodes in the list. */
template <typename T>
inline void LinkedList<T>::printList() const {
    LinkedList<T>::Node* temp {m_head};
    while(temp) {
        std::cout << temp->value << "\n";
        temp = temp->next;
    }
}

//! Adds the given value to the end of the List in a Node.
/*! O(1). This method will use the tail pointer to alter the last Node in the
 * List. No iteration is needed so complexity is constant, regardless of the 
 * length of the List.
 */
template <typename T>
inline bool LinkedList<T>::append(T value) {
    LinkedList<T>::Node* newNode = new LinkedList<T>::Node {value};
    if (m_length == 0){
        m_head = newNode;
        m_tail = newNode;
    }
    else {
        m_tail->next = newNode;
        m_tail = newNode;
    }
    ++m_length;
    return(true);
}

//! Deletes the last Node in the List.
/*! O(n). This method must iterate through each member of the list to find 
 * the 2nd-to-last item. Making it O(n) where n = the number of Nodes in the 
 * list. 
 */
template <typename T>
inline void LinkedList<T>::deleteLast(){
    if (m_length == 0 ) return;
    LinkedList<T>::Node* temp {m_head};
    if (m_length == 1 ) {
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        while(temp->next != m_tail){
            temp = temp->next;
        }
        m_tail = temp;
        temp = m_tail->next;
        m_tail->next = nullptr;
    }
    delete temp;
    --m_length;
}

//! Removes the first value from the front of the List.
/*! O(1). This method will use the head pointer to alter the first Node in the
 * List. No iteration is needed so complexity is constant, regardless of the 
 * length of the List.
 */
template <typename T>
inline void LinkedList<T>::deleteFirst(){
    if (m_length == 0 ) return;
    LinkedList<T>::Node* temp {m_head};
    if (m_length == 1 ) {
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        m_head = m_head->next;
    }
    delete temp;
    --m_length;
}

//! Adds the given value to the front of the List.
/*! O(1). This method will use the head pointer to alter the first Node in the
 * List. No iteration is needed so complexity is constant, regardless of the 
 * length of the List. 
 */
template <typename T>
inline void LinkedList<T>::prepend(T value){
    LinkedList<T>::Node* newNode = new LinkedList<T>::Node {value};
    newNode->next = m_head;
    m_head = newNode;
    if (m_length == 0) m_tail = newNode;
    ++m_length;
}

//! Returns the Node at the position given.
/*! O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
inline LinkedList<T>::Node* LinkedList<T>::get(int index) const {
    if (index < 0 || index >= m_length) {
        return nullptr;
    }
    LinkedList<T>::Node* temp {m_head};
    for (int i {0}; i < index; i++){
        temp = temp->next;
    }
    return temp;
}

//! Change the value of the Node at the given index.
/*! O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
inline bool LinkedList<T>::set(int index, T value){
    LinkedList<T>::Node* temp = get(index);
    if (temp) {
        temp->value = value;
        return true;
    }
    return false;
}

//! inserts the given value in a Node before the given index in the List
/*! O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
inline bool LinkedList<T>::insert(int index, T value){
    if (index < 0 || index > m_length) return false;
    if (index == 0) {
        prepend(value);
        return true;
    }
    if (index == m_length) {
        append(value);
        return true;
    }

    LinkedList<T>::Node* newNode = new LinkedList<T>::Node {value};
    LinkedList<T>::Node* temp {get(index-1)};

    newNode->next = temp->next;
    temp->next = newNode;
    ++m_length;
    return true;
}

//! Deletes the Node at the given index.
/*! O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
inline void LinkedList<T>::deleteNode(int index){
    if ( index < 0 || index >= m_length ) return;
    if ( index == 0 ) deleteFirst();
    if ( index == m_length-1 ) deleteLast();

    LinkedList<T>::Node* prev {get(index-1)};
    LinkedList<T>::Node* temp {prev->next};

    prev->next = temp->next;
    delete temp;
    ++m_length;
}

//! flips the List around so that head is tail and tail is head.
/*! O(n). The List must be iterated down so the complexity is O(n) where 
 * n = length of the List.
 */
template <typename T>
inline void LinkedList<T>::reverse() {
    LinkedList<T>::Node* temp {m_head};
    LinkedList<T>::Node* after {m_head};
    LinkedList<T>::Node* before {nullptr};
    for (int i {0}; i < m_length; i++){
        after = temp->next;
        temp->next = before;
        before = temp;
        temp = after;
    }
    m_tail = m_head;
    m_head = before;
}

//! Finds and returns the middle Node in the List.
template <typename T>
inline LinkedList<T>::Node* LinkedList<T>::middle() {
    LinkedList<T>::Node* tortoise {m_head};
    LinkedList<T>::Node* hare {m_head};
    while (hare && hare->next) {
        hare = hare->next->next;
        tortoise = tortoise->next;
    }
    return tortoise;
}

#endif
