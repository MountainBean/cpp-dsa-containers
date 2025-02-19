/* Linked List (Class Template)
 * Samuel Drew ~ 2025 
 * ---
 *  This is a simple implementation of a Linked List.
 *  Class templating is used to allow the creation of Linked Lists of any 
 *  object type. This version used CTAD (Class Type Argument Deduction) 
 *  and doesn't provide deduction guides so will only compile with C++20 or
 *  newer.
 */

#include <iostream>
#include <string>

//! (Singly) Linked list node struct
/*! Templated data aggregate to hold each node in a linked list
*/
template <typename T>
struct Node {

    T value     {};             // some object of any type
    Node* next  {nullptr};   // null pointer which will point to the next node

};

//! Templated implementation of a linked list using standard C++

template <typename T>
class LinkedList {
public:
    //! Constructor method. 
    /* Initialises the list using member initialisation list with the given 
     * object (value) as the 1st item.
     */
    LinkedList(T value) 
        : m_head    {new Node{value}}
        , m_tail    {m_head}
        , m_length  {1}
    {
    }

    //! Destructor method. Iterates along the list, releasing each Node from memory.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    ~LinkedList(){
        Node<T>* temp {m_head};
        while(m_head){
            m_head = m_head->next;
            delete temp;
            temp = m_head;
        }
    }

    //! prints the linked list items. One item per line.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    void printList() const {
        Node<T>* temp {m_head};
        while(temp) {
            std::cout << temp->value << "\n";
            temp = temp->next;
        }
    }

    //! Returns the Node at the head of the List.
    Node<T>* getHead() const {
        return m_head;
    }

    //! Returns the Node at the tail of the List.
    Node<T>* getTail() const {
        return m_tail;
    }

    //! Returns the total number of Nodes in the List.
    T getLength() const {
        return m_length;
    }

    //! Adds the given value to the end of the List in a Node.
    /*! O(1). This method will use the tail pointer to alter the last Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List.
     */
    bool append(T value) {
        Node<T>* newNode = new Node {value};
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
        Node<T>* temp {m_head};
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
        Node<T>* temp {m_head};
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
    void prepend(T value){
        Node<T>* newNode = new Node {value};
        newNode->next = m_head;
        m_head = newNode;
        if (m_length == 0) m_tail = newNode;
        ++m_length;
    }

    //! Returns the Node at the position given.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    Node<T>* get(int index) const {
        if (index < 0 || index >= m_length) {
            return nullptr;
        }
        Node<T>* temp {m_head};
        for (int i {0}; i < index; i++){
            temp = temp->next;
        }
        return temp;
    }

    //! Change the value of the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index.
     */
    bool set(int index, T value){
        Node<T>* temp = get(index);
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
    bool insert(int index, T value){
        if (index < 0 || index > m_length) return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == m_length) {
            append(value);
            return true;
        }

        Node<T>* newNode = new Node {value};
        Node<T>* temp {get(index-1)};

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

        Node<T>* prev {get(index-1)};
        Node<T>* temp {prev->next};

        prev->next = temp->next;
        delete temp;
        ++m_length;
    }

    //! flips the List around so that head is tail and tail is head.
    /*! O(n). The List must be iterated down so the complexity is O(n) where 
     * n = length of the List.
     */
    void reverse() {
        Node<T>* temp {m_head};
        Node<T>* after {m_head};
        Node<T>* before {nullptr};
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
    Node<T>* middle() {
        Node<T>* tortoise {m_head};
        Node<T>* hare {m_head};
        while (hare && hare->next) {
            hare = hare->next->next;
            tortoise = tortoise->next;
        }
        return tortoise;
    }

private:
    Node<T>* m_head {nullptr};      // pointer to the first Node in the Linked List.
    Node<T>* m_tail {nullptr};      // pointer to the last Node in the Linked List.
    int m_length {};                   // The length of the Linked List.

};


int main(void) {

    using namespace std::string_literals; // easy access to the s suffix

    LinkedList listOfStrings {"first string"s};
    listOfStrings.append("this is another"s);
    listOfStrings.append("more"s);
    listOfStrings.append("implicit from c-style");
    listOfStrings.append("Lots of strings"s);
    listOfStrings.append("just so many"s);
    listOfStrings.append("final string"s);
    
    listOfStrings.printList();
    std::cout << "\n";
    std::cout << "middle: " << listOfStrings.middle()->value << "\n";
    std::cout << "\n";
    std::cout << "\n";


    LinkedList listOfInts {80};
    listOfInts.append(81);
    listOfInts.prepend(82);
    listOfInts.prepend(83);
    listOfInts.insert(3, 84);
    listOfInts.append(85);
    listOfInts.append(86);
    listOfInts.insert(7, 87);

    listOfInts.printList();
    std::cout << "\n";
    std::cout << "middle: " << listOfInts.middle()->value << "\n";


    return(0);
    
}
