#include <iostream>

//! (Singly) Linked list node struct
/*! Simple data aggregate to hold each node in a linked list
 */
struct Node {

    int value {};           // an integer value
    Node* next {nullptr};   // null pointer which will point to the next node

};

//! Simple implementation of a linked list using standard C++

class LinkedList {

private:
    Node* m_head {nullptr};       /*! pointer to the first Node in the Linked List. */
    Node* m_tail {nullptr};       /*! pointer to the last Node in the Linked List. */
    int m_length;                 /*! The length of the Linked List. DON'T FORGET TO UPDATE
                                    THIS IN MEMBER FUNCTIONS. */

public:
    //! Constructor method. Initialises the List with a Node containing the given integer.
    LinkedList(int value){
        Node* newNode = new Node {value};
        m_head = newNode;
        m_tail = newNode;
        m_length = 1;
    }

    //! Destructor method. Iterates along the list, releasing each Node from memory.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    ~LinkedList(){
        Node* temp {m_head};
        while(m_head){
            m_head = m_head->next;
            delete temp;
            temp = m_head;
        }
    }

    //! prints the linked list items. One item per line.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    void printList() {
        Node* temp {m_head};
        while(temp) {
            std::cout << temp->value << "\n";
            temp = temp->next;
        }
    }

    //! Returns the int value of the Node at the head of the List.
    int getHead() {
        return m_head->value;
    }

    //! Returns the int value of the Node at the tail of the List.
    int getTail() {
        return m_tail->value;
    }

    //! Returns the total number of Nodes in the List.
    int getLength() {
        return m_length;
    }

    //! Adds the given value to the end of the List in a Node.
    /*! O(1). This method will use the tail pointer to alter the last Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List.
     */
    bool append(int value) {
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

    //! Deletes the last Node in the List.
    /*! O(n). This method must iterate through each member of the list to find 
     * the 2nd-to-last item. Making it O(n) where n = the number of Nodes in the 
     * list. 
     */
    void deleteLast(){
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

    //! Removes the first value from the front of the List.
    /*! O(1). This method will use the head pointer to alter the first Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List.
     */
    void deleteFirst(){
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

    //! Adds the given value to the front of the List.
    /*! O(1). This method will use the head pointer to alter the first Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List. 
     */
    void prepend(int value){
        Node* newNode = new Node {value};
        newNode->next = m_head;
        m_head = newNode;
        if (m_length == 0) m_tail = newNode;
        ++m_length;
    }

    //! Returns the Node at the position given.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    Node* get(int index){
        if (index < 0 || index >= m_length) {
            return nullptr;
        }
        Node* temp {m_head};
        for (int i {0}; i < index; i++){
            temp = temp->next;
        }
        return temp;
    }

    //! Change the value of the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    bool set(int index, int value){
        Node* temp = get(index);
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
    bool insert(int index, int value){
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

    //! Deletes the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    void deleteNode(int index){
        if ( index < 0 || index >= m_length ) return;
        if ( index == 0 ) deleteFirst();
        if ( index == m_length-1 ) deleteLast();

        Node* prev {get(index-1)};
        Node* temp {prev->next};

        prev->next = temp->next;
        delete temp;
        ++m_length;
    }

    //! flips the List around so that head is tail and tail is head.
    /*! O(n). The List must be iterated down so the complexity is O(n) where 
     * n = length of the List.
     */
    void reverse() {
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

    //! Finds and returns the middle Node in the List.
    Node* middle() {
        Node* tortoise {m_head};
        Node* hare {m_head};
        while (hare && hare->next) {
            hare = hare->next->next;
            tortoise = tortoise->next;
        }
        return tortoise;
    }
};


int main(void) {
    
    LinkedList* myLinkedList = new LinkedList(4);
    myLinkedList->append(5);
    myLinkedList->append(6);
    myLinkedList->append(7);
    myLinkedList->append(8);
    myLinkedList->append(9);
    myLinkedList->append(10);
    myLinkedList->append(11);
    myLinkedList->append(12);
    
    
    myLinkedList->printList();
    std::cout << "\n";
    std::cout << "middle: " << myLinkedList->middle()->value << "\n";
    return(0);
    
}
