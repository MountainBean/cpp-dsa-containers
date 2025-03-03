/*  quick test main.cpp to run tests on the libraries
 */
#include <algorithm>
#include <array>
#include <cassert>
#include <random>
#include <string>
#include "../LL/linked_list.h"

using namespace std::string_literals;

/*  Linked List Validation function.
 *  Tests the passed Linked List to ensure head, tail and length members are 
 *  valid and traverses the list fully to ensure the list isn't circular.
 */
template <typename T>
bool isValidLL(const sjd::LinkedList<T>& ll) {
    assert((ll.length() >= 0) && "length must not be a negative.");
    if (ll.length() == 0) {
        assert((
            ll.begin() == nullptr && 
            ll.end() == nullptr
        ) && "begin and end must be nullptr if length is 0.");
    }
    else {
        // traverse the ll to confirm not circular
        auto tortoise {ll.begin()};
        auto hare {ll.begin() -> next};
        while (hare != ll.end() && hare != nullptr){
            assert(tortoise != hare && "Circular list. aborting");
            tortoise = tortoise -> next;
            hare = hare -> next -> next;
        }
    }
    return true;
}

template <int reps>
bool testappend() {

    static_assert(reps > 0, "You need at least 1 rep");
    int i {1};
    sjd::LinkedList ll {0};
    while (i <= reps) {
        ll.append(i);
        ++i;
    }
    if (ll.begin() -> value != 0) {return false;}
    if (ll.end() -> value != reps) {return false;}
    if (ll.length() != (reps + 1)) {return false;}

    return isValidLL(ll);
}

template <int reps>
bool testprepend() {

    static_assert(reps > 0, "You need at least 1 rep");
    int i {1};
    sjd::LinkedList ll {0};
    while (i <= reps) {
        ll.prepend(i);
        ++i;
    }
    if (ll.begin() -> value != reps) {return false;}
    if (ll.end() -> value != 0) {return false;}
    if (ll.length() != (reps + 1)) {return false;}

    return isValidLL(ll);
}

template <int reps>
bool testdeleteLast() {

    static_assert(reps > 0, "You need at least 1 rep");
    int i {1};
    sjd::LinkedList ll {0};
    while (i <= reps) {
        ll.append(i);
        ++i;
    }
    i = 1;
    while (i <= reps) {
        ll.deleteLast();
        if (ll.end() -> value != (reps - i)) {return false;}
        if (ll.length() != (reps - i + 1)) {return false;}
        ++i;
    }

    return isValidLL(ll);
}

template <int reps>
bool testdeleteFirst() {

    static_assert(reps > 0, "You need at least 1 rep");
    int i {1};
    sjd::LinkedList ll {0};
    while (i <= reps) {
        ll.append(i);
        ++i;
    }
    i = 1;
    while (i <= reps) {
        ll.deleteFirst();
        if (ll.begin() -> value != (i)) {return false;}
        if (ll.length() != (reps - i + 1)) {return false;}
        ++i;
    }

    return isValidLL(ll);
}

template <int reps>
bool testget() {

    static_assert(reps > 0, "You need at least 1 rep");
    int i {1};
    std::array<int, reps+1> getIndices {};
    sjd::LinkedList ll {0};
    while (i <= reps) {
        ll.append(i);
        getIndices.at(static_cast<std::size_t>(i)) = i;
        ++i;
    }
    std::random_device rd;
    std::mt19937 gen {rd()};
    std::ranges::shuffle(getIndices, gen);
    i = 0;
    while (i < (reps+1)) {
        if (ll.get(getIndices.at(static_cast<std::size_t>(i))) -> value 
            != getIndices.at(static_cast<size_t>(i))) {return false;}
        ++i;
    }
    
    return isValidLL(ll);
}

int main() {

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


    assert(testappend<20>() && "Failed to append correctly");
    assert(testprepend<4>() && "Failed to prepend correctly");
    assert(testdeleteLast<4>() && "Failed to deleteLast correctly");
    assert(testdeleteFirst<4>() && "Failed to deleteFirst correctly");
    assert(testget<20>() && "Failed to get correctly");

    std::cout << "All tests succeeded.\n";
}
