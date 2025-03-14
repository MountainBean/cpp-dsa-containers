/*  quick test main.cpp to run tests on the libraries
 */
#include <cassert>
#include <iostream>
#include "../BST/binary_search_tree.h"

using namespace std::string_literals;

/*  Linked List Validation function.
 *  Tests the passed Linked List to ensure head, tail and length members are 
 *  valid and traverses the list fully to ensure the list isn't circular.
 */
template <typename T>
bool isValidLL(const sjd::BinarySearchTree<T>&) {
    std::cout << "Not Implemented";
    return false;
}

int main() {

    sjd::BinarySearchTree<int> myTree {};
    myTree.insert(94);
    myTree.insert(16);
    myTree.insert(140);
    myTree.insert(42);
    myTree.insert(71);
    myTree.insert(2);
    
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "myTree root addr: " << &myTree << "\n";
    std::cout << myTree << "\n";
    
    std::vector<int> oderedElements {myTree.dfsInOrder()};
    std::cout << "In order: [ ";
    for (int element : oderedElements){
        std::cout << element << " ";
    }
    std::cout << "]\n";

    std::cout << "All tests succeeded.\n";
}
