#include <iostream>
// Vecotors are like dynamic arrays.
// They handle the painful dynamic memory operations for us.
#include <vector>
// This is so we can create threads.
#include <thread>
// Include our other .hpp files.
#include "item.hpp"
#include "node.hpp"
#include "player.hpp"

// Program entry point
int main(int argc, char** argv)
{
    // Create a vecotr object which whil hold type Items.
    std::vector<Item> items;

    // Push some items onto the vector (like filling an array). We can do this using the constructor we made for our Item struct.
    items.push_back(Item("Potion", 0, 50, 2));
    items.push_back(Item("Arrows", 15, 0, 30));
    items.push_back(Item("Sword", 35, 0, 1));

    // Create the Nodes (or inventory slots for our entity).
    // We name each node "item", representing each inventory slot the player has.
    // Each invetory slot (node), also has a pointer to the next inventory slot(node).
    Node<Item> item3(items[1], nullptr);
    Node<Item> item2(items[0], &item3);
    Node<Item> item1(items[2], &item2);

    // Create some entites.
    // We first create a player, give it a name, intial HP, starting gold (the currency), and set the first item of their
    // inventory. This is the "head" of the linked list (inventory)
    Entity<Item> player("Isak", 100, 0, &item1);
    Entity<Item> slime("Slime", 60, 15, &item1);

    // What is a thread?
    //  As you know, a program is a sequence of statements, meaning we start from our entry point, and run line by line.
    //  Threads give us a way to run multiple lines of code at the SAME time. For example, we could be adding 5 to a number x,
    //  while at the EXACT SAME time, subtracting 5 from y. This is very powerful as it allows us to do many things at one during our program execution.
    //  For example, we could have a thread constantly grabbing data from a API (like a weather API), and then updating our app.
    //  This avoids the overhead of updating the weather, calling the API, and then waiting for a respone before updating the weather data again.
    //  We can constantly update the weather as the backround thread is calling the API behind the scenes, the data is always ready for us.

    // Create a new thread called "battleT". This allows us to battle other entities while they are pick pocketing for example.
    // The first argument (&Entity<Item>::fight) is the function we would like the thread to exectute.
    // The second argument (&player) is what object we would like to execute it on.
    // The third argument (std::ref(slime)), is the argument of the function fight();
    std::thread battleT(&Entity<Item>::fight, &player, std::ref(slime));

    // Notice how all thread arguments are passed by refrence, this is becuase, the thread is a differnt process to our actual program. It dosnt have access
    // to the code as other fumnctions do. We need to pass by refrence (or pointer), so the new thread knows exactly where everything is in memeory
    // and what to do with it.

    // Here we do the same thing, just for our autoPickPocket function and different arguments for the function.
    std::thread pickPocketT(&Entity<Item>::autoPickPocket, &player, 5, 15);

    // .join() means we are waiting for the thread to finish its exectutions.
    battleT.join();
    pickPocketT.join();

    // As you may of noticed, we start the battle thread before the pickpocket thread, but we are wating for the battle thread to finish first.
    // We are executing the two functions concurrently.

    // Print the player gold to see if it updated when we killed the enemy (slime), and while we were pickpocketing at the same time.

    std::cout << player.gold << '\n';

    return 0;
}
