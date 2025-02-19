// Sam Drew ~ 2025
// Doubly Linked List implementation in C++

#include <iostream>
#include <string>

template <typename T>
struct DoubleNode {

    T value {};
    DoubleNode<T>* next {nullptr};
    DoubleNode<T>* prev {nullptr};

};

//! Doubly Linked List template.
/*  Holds a single object type in a doubly linked list of one or more objects.
 *  Initialise with an object to create the first node of the list.
 *  Use the included member functions to add to, remove from and search the 
 *  list.
 *  Example:
 *      DoublyLinkedList myList {3};    // myList: [3]
 *      myList.append(4);               // myList: [3, 4]
 *      myList.prepend(2);              // myList: [2, 3, 4]
 *      myList.set(0, 1);               // myList: {1, 3, 4]
 */
template <typename T>
class DoublyLinkedList {
public:
    
    explicit DoublyLinkedList(T value)
        : m_head    { new DoubleNode{value} }
        , m_tail    { m_head }
        , m_length  { 1 }
    {
    }

    ~DoublyLinkedList() {
        DoubleNode<T>* temp {m_head};
        while(m_head) {
            m_head = m_head->next;
            delete temp;
            temp = m_head;
        }
    }

    void printList() const {
        DoubleNode<T>* temp {m_head};
        while(temp){
            std::cout << temp->value << "\n";
            temp = temp->next;
        }
    }

    /*  O(1)
     *  Uses the tail pointer to add the given node value to the end of the list
     */
    bool append(T value) {
        DoubleNode<T>* newNode {new DoubleNode {value}};
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

private:

    DoubleNode<T>* m_head {nullptr};
    DoubleNode<T>* m_tail {nullptr};
    int m_length {};

};

int main (void) {

    using namespace std::string_literals; // easy access to the s suffix

    DoublyLinkedList myIntList {3};
    myIntList.append(8);
    myIntList.printList();

    DoublyLinkedList myStringList {"hombre"s};
    myStringList.append("verdegris"s);

    myStringList.printList();
}
