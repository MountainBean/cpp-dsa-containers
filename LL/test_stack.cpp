#include <string>
#include "stack.h"

int main(void) {

    using namespace std::string_literals;
    sjd::Stack myStringStack {"Gilbert"s};
    myStringStack.push("Rosencrantz"s);
    myStringStack.push("Gildenstern"s);
    myStringStack.printStack();
    auto poppedNode {myStringStack.pop()};
    std::cout << "popped Node: " << poppedNode -> value << "\n";
    std::cout << "\n";
    myStringStack.printStack();
    std::cout << "\n";

    sjd::Stack myIntStack {9};
    myIntStack.push(8);
    myIntStack.push(0);
    myIntStack.printStack();
    auto poppedIntNode {myIntStack.pop()};
    std::cout << "popped Node: " << poppedIntNode -> value << "\n";
    std::cout << "\n";
    myIntStack.printStack();
    std::cout << "\n";

}
