/*  quick test main.cpp to run tests on the libraries
 */
#include <cassert>
#include <string>
#include "../LL/smart_linked_list.h"

using namespace std::string_literals;

/*  Linked List Validation function.
 *  Tests the passed Linked List to ensure head, tail and length members are 
 *  valid and traverses the list fully to ensure the list isn't circular.
 */
template <typename T>
bool isValidLL(const sjd::SmartLinkedList<T>& ll) {
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
    sjd::SmartLinkedList ll {0};
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
    sjd::SmartLinkedList ll {0};
    while (i <= reps) {
        ll.prepend(i);
        ++i;
    }
    if (ll.begin() -> value != reps) {return false;}
    if (ll.end() -> value != 0) {return false;}
    if (ll.length() != (reps + 1)) {return false;}

    return isValidLL(ll);
}

int main() {

    sjd::SmartLinkedList myStringList { "first_string"s };
    
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "myStringList addr: " << &myStringList << "\n";

    
    assert(testappend<12>() && "test append failed.");
    assert(testprepend<8>() && "test prepend failed.");
    std::cout << "All tests succeeded.\n";
}
