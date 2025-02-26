#include "queue.h"

int main() {

    using namespace std::string_literals;

    sjd::Queue myStringQueue {"Bilbo"s};
    myStringQueue.printQueue();
    std::cout << "\n";

    sjd::Queue myIntQueue {60};
    myIntQueue.printQueue();
    std::cout << "\n";
}
