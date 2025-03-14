#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
/* Sam Drew ~ 2025
 * Binary Search Tree implementation in C++
 * ---
 *  This is a simple implementation of a Binary Search tree. Written by me, 
 *  for my own edification in data structures and algorithms and C++.
 *  Class templating is used to allow the creation of Linked Lists of any 
 *  object type. This version uses CTAD (Class Type Argument Deduction) 
 *  and doesn't provide deduction guides so will only compile with C++20 or
 *  newer.
 */

#include <iostream>
#include <memory>
#include <vector>
#include "../LL/queue.h"

/* Binary Search Tree template class.
 *  
 *  Initialise with an object to create the first node of the tree.
 *  Use the included member functions to add to, remove from and search the 
 *  tree.
 *  Objects must be of a type that is comparable (Can use the comparison 
 *  operators <, >, ==, != etc...) or you will recieve a compiler error.
 *  Example:
 *
 */
namespace sjd {
template <typename T>
class BinarySearchTree {
public:
    struct Node {
        T value {};
        std::shared_ptr<Node> left {nullptr};
        std::shared_ptr<Node> right {nullptr};
    };

    BinarySearchTree()
    : m_root {}
    , m_size  {0}
    {
    }

    std::shared_ptr<Node> begin() const { return m_root; }

    bool insert(const T& value) {
        auto newNode {std::make_shared<Node>(value)};
        if (!m_root) {
            // empty tree
            m_root = newNode;
            ++m_size;
            return true;
        }
        std::shared_ptr<Node> temp {m_root};
        while (true) {
            if (newNode -> value == temp -> value) {return false;}  // duplicate
            if (newNode -> value < temp -> value) { // start at root
                if (!(temp -> left)) {              // if less than, move left
                    temp -> left = newNode;
                    ++m_size;
                    return true;
                }
                temp = temp -> left;
            }
            else {
                if (!(temp -> right)) {             // if more than, move right
                    temp -> right = newNode;
                    ++m_size;
                    return true;
                }
                temp = temp -> right;
            }
        }
    }

    bool contains(const T& value) const {
        std::shared_ptr<Node> temp {m_root};
        while (temp) {
            if (value < temp -> value) {temp = temp -> left;}
            else if (value > temp -> value) {temp = temp -> right;}
            else {return true;}
            return false;
        }
    }

    T min(std::shared_ptr<Node> currNode) {
        while (currNode -> left){
            currNode = currNode -> left;
        }
        return currNode -> value;
    }

    std::shared_ptr<Node> __r_removeNode(std::shared_ptr<Node> currNode, T value){
        if (!currNode) {return nullptr;}
        else if (value < currNode -> value) {
            currNode -> left = __r_removeNode(currNode -> left, value);
        }
        else if (value > currNode -> value) {
            currNode -> right = __r_removeNode(currNode -> right, value);
        }
        else {
            if (!(currNode -> left) && !(currNode -> right)) {return nullptr;}
            else if (!(currNode -> right)) {return currNode -> left;}
            else if (!(currNode -> left)) {return currNode -> right;}
            else {
                currNode -> value = min(currNode -> right);
                currNode -> right = __r_removeNode(currNode -> right, currNode -> value);
            }
        }
        return currNode;
    }

    void remove(T value){
        m_root = __r_removeNode(m_root, value);
    }

    /* Performs a breadth-first search using a queue to keep track of the order
     * of the Nodes.
     */
    std::vector<std::shared_ptr<Node>> elementsTopDown() const {
        std::vector<std::shared_ptr<Node>> results {};
        if (m_size == 0) {return results;}
        std::shared_ptr<Node> currNode {nullptr};
        sjd::Queue<std::shared_ptr<Node>> queue {};
        queue.enqueue(m_root);

        while (queue.length() > 0) {
            currNode = (queue.dequeue() -> value);
            results.push_back(currNode);
            if (currNode -> left) {queue.enqueue(currNode -> left);}
            if (currNode -> right) {queue.enqueue(currNode -> right);}
        }

        return results;
    }

    // Recursively steps through the bst
    void __r_traverseDfsInOrder(std::shared_ptr<Node> currNode, std::vector<T>& arrayOut) const {
        if (currNode -> left) {__r_traverseDfsInOrder(currNode -> left, arrayOut);}
        arrayOut.push_back(currNode -> value);
        if (currNode -> right) {__r_traverseDfsInOrder(currNode -> right, arrayOut);}
    }

    std::vector<T> dfsInOrder() const {
        std::vector<T> results{};
        __r_traverseDfsInOrder(m_root, results);
        return results;
    }


    friend std::ostream& operator<< (std::ostream& out, const BinarySearchTree<T>& bst) {
        out << "BST[ ";
        std::vector elements {bst.elementsTopDown()};
        for (std::shared_ptr<Node> node : elements){
            out << node -> value << " ";
        }
        out << "]";
        return out;
    }

private:
    std::shared_ptr<Node> m_root {nullptr};
    std::size_t m_size {};
    
    void __r_traverseDfsInOrder(std::shared_ptr<Node> currNode, std::vector<std::shared_ptr<Node>>& arrayOut) {
        if (currNode -> left) {__r_traverseDfsInOrder(currNode -> left);}
        arrayOut.push_back(currNode);
        if (currNode -> right) {__r_traverseDfsInOrder(currNode -> right);}
    }
};


} // end namespace sjd
#endif
