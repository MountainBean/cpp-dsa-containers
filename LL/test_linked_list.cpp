/*  quick test main.cpp to run tests on the libraries
 */
#include "linked_list.h"

int main() {

using namespace std::string_literals;

    LinkedList myStringList { "first_string"s };
    myStringList.append("another"s);
    myStringList.append("yet another"s);
    myStringList.prepend("first_first string"s);
    std::cout << "\n";
    myStringList.printList();

    std::cout << "\n";
    std::cout << "\n";
    LinkedList myIntList { 12 };
    myIntList.append(13);
    myIntList.append(14);
    myIntList.prepend(11);

    myIntList.printList();
    std::cout << "\n";
}
