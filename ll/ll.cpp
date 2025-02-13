#include <iostream>

//! (Singly) Linked List Node Class.

class Node {
public:

    int value;          /*! an integer value */
    Node* next;         /*! null pointer which will point to the next node */

    //! Constructor class. Initialises the Node value to the given integer.
    Node(int value){
        this->value = value;
        next = nullptr;
    };
};

//! Simple implementation of a linked list using standard C++

class LinkedList {

private:
    Node* head {nullptr};       /*! pointer to the first Node in the Linked List. */
    Node* tail {nullptr};       /*! pointer to the last Node in the Linked List. */
    int length;                 /*! The length of the Linked List. DON'T FORGET TO UPDATE
                                    THIS IN CLASS METHODS. */

public:
    //! Constructor method. Initialises the List with a Node containing the given integer.
    LinkedList(int value){
        Node* newNode = new Node(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    //! Destructor method. Iterates along the list, releasing each Node from memory.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    ~LinkedList(){
        Node* temp {head};
        while(head){
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    //! prints the linked list items. One item per line.
    /*! O(n). This method iterates through each member of of the list making it O(n) 
     * where n = the number of Nodes in the list. */
    void printList() {
        Node* temp {head};
        while(temp) {
            std::cout << temp->value << "\n";
            temp = temp->next;
        }
    }

    //! Returns the int value of the Node at the head of the List.
    void getHead() {
        std::cout << "Head: " << head->value << "\n";
    }

    //! Returns the int value of the Node at the tail of the List.
    void getTail() {
        std::cout << "Tail: " << tail->value <<  "\n";
    }

    //! Returns the total number of Nodes in the List.
    void getLength() {
        std::cout << "Length: " << length << "\n";
    }

    //! Adds the given value to the end of the List in a Node.
    /*! O(1). This method will use the tail pointer to alter the last Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List. */
    bool append(int value) {
        Node* newNode = new Node(value);
        if (length == 0){
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
        return(true);
    }

    //! Deletes the last Node in the List.
    /*! O(n). This method must iterate through each member of the list to find 
     * the 2nd-to-last item. Making it O(n) where n = the number of Nodes in the 
     * list. */
    void deleteLast(){
        if (length == 0 ) return;
        Node* temp {head};
        if (length == 1 ) {
            head = nullptr;
            tail = nullptr;
        } else {
            while(temp->next != tail){
                temp = temp->next;
            }
            tail = temp;
            temp = tail->next;
            tail->next = nullptr;
        }
        delete temp;
        length--;
    }

    //! Removes the first value from the front of the List.
    /*! O(1). This method will use the head pointer to alter the first Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List. */
    void deleteFirst(){
        if (length == 0 ) return;
        Node* temp {head};
        if (length == 1 ) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
        }
        delete temp;
        length--;
    }

    //! Adds the given value to the front of the List.
    /*! O(1). This method will use the head pointer to alter the first Node in the
     * List. No iteration is needed so complexity is constant, regardless of the 
     * length of the List. */
    void prepend(int value){
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (length == 0) tail = newNode;
        length++;
    }

    //! Returns the Node at the position given.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index */
    Node* get(int index){
        if (index < 0 || index >= length) {
            return nullptr;
        }
        Node* temp {head};
        for (int i {0}; i < index; i++){
            temp = temp->next;
        }
        return temp;
    }

    //! Change the value of the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index */
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
     * Node making it O(n) where n = index */
    bool insert(int index, int value){
        if (index < 0 || index > length) return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }

        Node* newNode = new Node(value);
        Node* temp {get(index-1)};

        newNode->next = temp->next;
        temp->next = newNode;
        length++;
        return true;
    }

    //! Deletes the Node at the given index.
    /*! O(n). Iterates through the list until it reaches the index of the requested
     * Node making it O(n) where n = index */
    void deleteNode(int index){
        if ( index < 0 || index >= length ) return;
        if ( index == 0 ) deleteFirst();
        if ( index == length-1 ) deleteLast();

        Node* prev {get(index-1)};
        Node* temp {prev->next};

        prev->next = temp->next;
        delete temp;
        length--;
    }

    //! flips the List around so that head is tail and tail is head.
    /*! O(n). The List must be iterated down so the complexity is O(n) where 
     * n = length of the List.*/
    void reverse() {
        Node* temp {head};
        Node* after {head};
        Node* before {nullptr};
        for (int i {0}; i < length; i++){
            after = temp->next;
            temp->next = before;
            before = temp;
            temp = after;
        }
        tail = head;
        head = before;
    }

    //! Finds and returns the middle Node in the List.
    Node* middle() {
        Node* tortoise {head};
        Node* hare {head};
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
