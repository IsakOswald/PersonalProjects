#pragma once

// A template so our linked list (Entity inventory), can hold different items.
template <typename T>
struct Node
{
    // The data held aby each node can hold different data, such as a value (int/float), or other data structures such as our item.
    T data;
    // A pointer to the next nodes in the linked list.
    Node<T>* next;

    // A constructor for each node (inventory slots).
    Node(T d, Node<T>* n) : data(d), next(n) {}
};
