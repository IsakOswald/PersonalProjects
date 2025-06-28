#include "splashkit.h"
#include "stdlib.h"
#include "iostream"

//! Struct node, holds a vlaue and a ptr to the next node.
template <typename T>
struct node
{
     node *next;
     T data;
};

//! defines the starting and the ending node.
template <typename T>
struct linked_list
{
     node<T> *first;
     node<T> *last;
};

//* Function declarations go here.
template <typename T>
linked_list<T> *create_linked_list();

template <typename T>
void remove_node(linked_list<T> *new_linked_list);

template <typename T>
void add_node(linked_list<T> *new_linked_list);

template <typename T>
void traverse_nodes(linked_list<T> *new_linked_list);

template <typename T>
void remove_linked_list(linked_list<T> *new_linked_list);

//*

int main()
{
     linked_list<int> *new_linked_list = create_linked_list<int>();

     // Testing.
     add_node(new_linked_list);
     add_node(new_linked_list);
     add_node(new_linked_list);
     traverse_nodes(new_linked_list);
     remove_node(new_linked_list);
     remove_node(new_linked_list);
     remove_linked_list(new_linked_list);

     delete new_linked_list;

     return 0;
}

//! Creat a linked list by creating a new instance of the linked_list struct.
template <typename T>
linked_list<T> *create_linked_list()
{
     linked_list<T> *new_linked_list = nullptr;

     // Try to allocate for the new linked list
     try
     {
          new_linked_list = new linked_list<T>;

          // When the list is first created it has no nodes.
          new_linked_list->first = nullptr;
          new_linked_list->last = nullptr;

          write_line("New list was successfully created!");

          return new_linked_list;
     }

     // If allocation fails print a message and remove.
     catch (const std::bad_alloc &)
     {
          write_line("Creation of linked list failed! The link list will not be created.");

          delete new_linked_list;
          return nullptr;
     }
}

//! A function to remove the entire list
template <typename T>
void remove_linked_list(linked_list<T> *new_linked_list)
{
     // The current node is the starting node
     node<T> *current = new_linked_list->first;

     // While this node is not a null pointer, save the upcoming node and delete the current node
     while (current != nullptr)
     {
          node<T> *next_to_delete = current->next;
          delete current;
          current = next_to_delete;
     }

     // Dont remove the list, just remove the nodes
     new_linked_list->first = nullptr;
     new_linked_list->last = nullptr;

     write_line("All nodes have been removed!");
}

//! A function to read the value of each node
template <typename T>
void traverse_nodes(linked_list<T> *new_linked_list)
{
     // Save the first node as the current node
     node<T> *current = new_linked_list->first;

     // Check if the current node is null, if it is there are no nodes.
     if (current == nullptr)
     {
          write_line("The list is empty! Nothing to iterate over.");
          return;
     }

     // If the noes are not null, follow the pointer path and prin tthe data.
     while (current != nullptr)
     {
          write_line("Current data is: " + std::to_string(current->data));

          current = current->next;
     }
}

//! A function to add the node and the end of the linked list
template <typename T>
void add_node(linked_list<T> *new_linked_list)
{
     // Dynamically create the new node that we will insert
     node<T> *new_node = new node<T>;

     // Ask the user what the want the type to be
     write("What do you want to store at the new node?: ");
     T input;
     std::cin >> input;
     new_node->data = input;
     new_node->next = nullptr;

     // If the linked list is empty, the entry is both the head and the tail.
     if (new_linked_list->first == nullptr)
     {
          new_linked_list->first = new_node;
          new_linked_list->last = new_node;
     }

     // If there is existing elements the last pointers next pointer is changed from null
     // to the new last node. Then set the last element to the new node.
     else
     {
          new_linked_list->last->next = new_node;
          new_linked_list->last = new_node;
     }

     write_line("Node was added to the end!");
}

//! A function to remove the first node of the list.
//? I think that it would be cool to search nodes based on user input and then delete the pointer and node, the reconnect the node pointers
//? however I think what ive done has demonstrated my ability to work with dynamically created objects

template <typename T>
void remove_node(linked_list<T> *new_linked_list)
{

     // If there are no elements print a message
     if (new_linked_list->first == nullptr)
     {
          write_line("The linked list is empty! Nothing to remove");
          return;
     }

     // If the list is not empty set the node to remove as the first node.
     node<T> *node_to_remove = new_linked_list->first;
     // The firsts nodes pointer becomes the second nodes pointer, they are 'shifted'
     new_linked_list->first = new_linked_list->first->next;

     // If the first node is now null, we have no elements therefor it is also the last.
     if (new_linked_list->first == nullptr)
     {
          new_linked_list->last = nullptr;
     }

     // Remove the node that we wanted to remove, preventing memory leaks.
     delete node_to_remove;
     write_line("The first element has been removed!");
}