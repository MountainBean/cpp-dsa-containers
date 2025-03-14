#include "../LL/queue.h"

int main() {

    using namespace std::string_literals;

    sjd::Queue<std::string> myStringQueue {};
    myStringQueue.enqueue("Vermillion"s);
    myStringQueue.enqueue("rose-quartz"s);
    myStringQueue.enqueue("Purple"s);
    myStringQueue.enqueue("Vermillion"s);
    myStringQueue.printQueue();
    std::cout << "\n";
    std::cout << myStringQueue.dequeue() -> value << "\n";
    std::cout << myStringQueue.dequeue() -> value << "\n";
    std::cout << myStringQueue.dequeue() -> value << "\n";
    std::cout << myStringQueue.dequeue() -> value << "\n";
    std::cout << "\n";
    myStringQueue.printQueue();
    std::cout << "\n";

    sjd::Queue<int> myIntQueue {};
    myIntQueue.printQueue();
    std::cout << "\n";
}
