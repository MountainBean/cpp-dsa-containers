// Sam Drew ~ 2025
// Doubly Linked List implementation in C++

#include <iostream>
#include <stdatomic.h>

template <typename T>
struct DoubleNode {

    T value {};
    DoubleNode<T>* next {nullptr};
    DoubleNode<T>* prev {nullptr};

};

//! Doubly Linked List template.
/*  Big O (worst-case) time complexity of each member function described in 
 *  comments.
 */
template <typename T>
class DoublyLinkedList {
public:
    
    //! Constructor
    /* O(1)
     * Constructor takes an object (value) and puts it in the first node of
     * the linked list.
     */
    DoublyLinkedList(T value)
        : m_head    { new DoubleNode{value} }
        , m_tail    { m_head }
        , m_length  { 1 }
    {
    }

    void printList() const {
        DoubleNode<T>* temp {m_head};
        while(temp){
            std::cout << temp->value << "\n";
            temp = temp->next;
        }
    }

private:

    DoubleNode<T>* m_head {nullptr};
    DoubleNode<T>* m_tail {nullptr};
    int m_length {};

};

int main (void) {

    std::cout << "Doubly Linked Lists running...\n";
    DoublyLinkedList myDList {3};
    myDList.printList();
}
