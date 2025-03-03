/*  quick test main.cpp to run tests on the libraries
 */
#include "../LL/linked_list.h"

int main() {

using namespace std::string_literals;

    sjd::LinkedList myStringList { "first_string"s };
    myStringList.append("another"s);
    myStringList.append("yet another"s);
    myStringList.prepend("first_first string"s);
    std::cout << "\n";
    std::cout << "myStringList: ";
    myStringList.printList();
    
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "myStringList addr: " << &myStringList << "\n";

    sjd::LinkedList copyStringList {myStringList};

    std::cout << "copyStringList: ";
    copyStringList.printList();
    std::cout << "copyStringList addr: " << &copyStringList << "\n";
}
