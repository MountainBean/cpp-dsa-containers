/*  quick test main.cpp to run tests on the libraries
 */
#include "../LL/doubly_linked_list.h"

int main() {

using namespace std::string_literals;

    sjd::DoublyLinkedList myStringList { "first_string"s };
    myStringList.append("another"s);
    myStringList.append("yet another"s);
    myStringList.append("more"s);
    myStringList.append("more strings"s);
    myStringList.append("MORE"s);
    myStringList.append("final"s);
    myStringList.prepend("first_first string"s);
    std::cout << "\n";
    myStringList.printList();
    std::cout << "\n";
    auto poppedNode { myStringList.pop() };
    std::cout << "popped node: " << poppedNode -> value << "\n";
    std::cout << "\n";
    auto prePoppedNode { myStringList.popFirst() };
    std::cout << "popped node: " << prePoppedNode -> value << "\n";
    myStringList.printList();
    std::cout << "\n";
    std::cout << "get node 3: " << myStringList.get(3) -> value << "\n";
    std::cout << "\n";
    std::cout << "set node 3 to \"bricks\"\n";
    myStringList.setValue(3, "bricks"s);
    myStringList.printList();
    std::cout << "\n";
    std::cout << "insert node \"boils\" at 2\n";
    myStringList.insert(2, "boils");
    myStringList.printList();


    std::cout << "\n";
    std::cout << "\n";
    sjd::DoublyLinkedList myIntList { 12 };
    myIntList.append(13);
    myIntList.append(14);
    myIntList.prepend(11);

    myIntList.printList();
    std::cout << "\n";
}
