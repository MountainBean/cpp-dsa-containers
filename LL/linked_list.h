#ifndef LINKEDLIST_H
#define LINKEDLIST_H
/* Linked List (Class Template)
 * Samuel Drew ~ 2025 
 * ---
 *  This is a simple implementation of a Linked List.
 *  Class templating is used to allow the creation of Linked Lists of any 
 *  object type. This version uses CTAD (Class Type Argument Deduction) 
 *  and doesn't provide deduction guides so will only compile with C++20 or
 *  newer.
 */

#include <iostream>

//  Member function implementations can be found below the class declaration
template <typename T>
class LinkedList {
public:

    //Templated data aggregate to hold each node in a linked list
    struct Node {

        T value     {};             // some object of any type
        Node* next  {nullptr};      // null pointer which will point to the next node

    };

    // accessors
    Node* getHead() const { return m_head; }
    Node* getTail() const { return m_tail; }
    T getLength() const { return m_length; }

    // constructor & destructor
    explicit LinkedList(const T& value);
    ~LinkedList();

    void printList() const;

    bool append(const T& value);

    void deleteLast();

    void deleteFirst();

    void prepend(const T& value);

    Node* get(int index) const;

    bool set(int index, const T& value);

    bool insert(int index, const T& value);

    void deleteNode(int index);

    void reverse();

    Node* middle();

private:

    Node* m_head {nullptr};     // pointer to the first Node in the Linked List.
    Node* m_tail {nullptr};     // pointer to the last Node in the Linked List.
    int m_length {};            // The length of the Linked List.

};



//---
/*  Implementation of member functions included as most are templated. The 
 *  compiler therefore requires the full definition included.*/
template <typename T>
LinkedList<T>::LinkedList(const T& value)
    : m_head    {new Node{value}}
    , m_tail    {m_head}
    , m_length  {1}
{
}

/* Destructor method. Iterates along the list, releasing each Node from memory.
 * O(n). This method iterates through each member of of the list making it O(n) 
 * where n = the number of Nodes in the list.*/
template <typename T>
LinkedList<T>::~LinkedList(){
    Node* temp {m_head};
    while(m_head){
        m_head = m_head->next;
        delete temp;
        temp = m_head;
    }
}

/* prints the linked list items. One item per line.
 * O(n). This method iterates through each member of of the list making it O(n) 
 * where n = the number of Nodes in the list. */
template <typename T>
void LinkedList<T>::printList() const {
    Node* temp {m_head};
    while(temp) {
        std::cout << temp->value << "\n";
        temp = temp->next;
    }
}

/* Adds the given value to the end of the List in a Node.
 * O(1). This method will use the tail pointer to alter the last Node in the
 * List. No iteration is needed so complexity is constant, regardless of the 
 * length of the List.
 */
template <typename T>
bool LinkedList<T>::append(const T& value) {
    Node* newNode = new Node {value};
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

/* Deletes the last Node in the List.
 * O(n). This method must iterate through each member of the list to find 
 * the 2nd-to-last item. Making it O(n) where n = the number of Nodes in the 
 * list. 
 */
template <typename T>
void LinkedList<T>::deleteLast(){
    if (m_length == 0 ) return;
    Node* temp {m_head};
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

/* Removes the first value from the front of the List.
 * O(1). This method will use the head pointer to alter the first Node in the
 * List. No iteration is needed so complexity is constant, regardless of the 
 * length of the List.
 */
template <typename T>
void LinkedList<T>::deleteFirst(){
    if (m_length == 0 ) return;
    Node* temp {m_head};
    if (m_length == 1 ) {
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        m_head = m_head->next;
    }
    delete temp;
    --m_length;
}

/* Adds the given value to the front of the List.
 * O(1). This method will use the head pointer to alter the first Node in the
 * List. No iteration is needed so complexity is constant, regardless of the 
 * length of the List. 
 */
template <typename T>
void LinkedList<T>::prepend(const T& value){
    Node* newNode = new Node {value};
    newNode->next = m_head;
    m_head = newNode;
    if (m_length == 0) m_tail = newNode;
    ++m_length;
}

/* Returns the Node at the position given.
 * O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
LinkedList<T>::Node* LinkedList<T>::get(int index) const {
    if (index < 0 || index >= m_length) {
        return nullptr;
    }
    Node* temp {m_head};
    for (int i {0}; i < index; i++){
        temp = temp->next;
    }
    return temp;
}

/* Change the value of the Node at the given index.
 * O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
bool LinkedList<T>::set(int index, const T& value){
    Node* temp = get(index);
    if (temp) {
        temp->value = value;
        return true;
    }
    return false;
}

/* inserts the given value in a Node before the given index in the List
 * O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
bool LinkedList<T>::insert(int index, const T& value){
    if (index < 0 || index > m_length) return false;
    if (index == 0) {
        prepend(value);
        return true;
    }
    if (index == m_length) {
        append(value);
        return true;
    }

    Node* newNode = new Node {value};
    Node* temp {get(index-1)};

    newNode->next = temp->next;
    temp->next = newNode;
    ++m_length;
    return true;
}

/* Deletes the Node at the given index.
 * O(n). Iterates through the list until it reaches the index of the requested
 * Node making it O(n) where n = index.
 */
template <typename T>
void LinkedList<T>::deleteNode(int index){
    if ( index < 0 || index >= m_length ) return;
    if ( index == 0 ) deleteFirst();
    if ( index == m_length-1 ) deleteLast();

    Node* prev {get(index-1)};
    Node* temp {prev->next};

    prev->next = temp->next;
    delete temp;
    ++m_length;
}

/* flips the List around so that head is tail and tail is head.
 * O(n). The List must be iterated down so the complexity is O(n) where 
 * n = length of the List.
 */
template <typename T>
void LinkedList<T>::reverse() {
    Node* temp {m_head};
    Node* after {m_head};
    Node* before {nullptr};
    for (int i {0}; i < m_length; i++){
        after = temp->next;
        temp->next = before;
        before = temp;
        temp = after;
    }
    m_tail = m_head;
    m_head = before;
}

// Finds and returns the middle Node in the List.
template <typename T>
LinkedList<T>::Node* LinkedList<T>::middle() {
    Node* tortoise {m_head};
    Node* hare {m_head};
    while (hare && hare->next) {
        hare = hare->next->next;
        tortoise = tortoise->next;
    }
    return tortoise;
}

#endif
