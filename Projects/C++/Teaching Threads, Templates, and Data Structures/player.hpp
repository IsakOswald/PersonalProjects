#pragma once

// You should probably know what these two are if you are reading this....
#include <iostream>
#include <string>
// The next three includes are thread related.
// Allow us to lock threads (avoid race conditions)
#include <mutex>
// Allow us to sleep threads for a certian ammout of time.
#include <chrono>
#include <thread>
// Inclue our node.hpp
#include "node.hpp"

// We will have our struct templated so we can construct Entity objects with differnt inventories.
template <typename T>
// Our entity struct.
struct Entity
{
    // The entities name.
    std::string name;
    // The entities health.
    int hp;
    // The entities gold that they have.
    int gold;
    // The start of the linked list.
    // This will be the first element of the lined list (also know as the "head")
    // This is templated as they can have a linked list of anything, ints, floats, or even other structs (such as nodes)
    Node<T>* first;
    // A mutex variable called mtx, we can lock mtx to allow only one thread to access any variable at one time.
    std::mutex mtx;

    // A constructor to create entites objects (like player or enemies).
    Entity(std::string n, int h, int g, Node<T>* f) : name(n), hp(h), gold(g), first(f) {}

    // A function to pickpocket (a way to passivly add gold)
    void autoPickPocket(int goldStolen, int iterations) noexcept
    {
        // Let the user know that they have started pick pocket.
        std::cout << "You have started to pick pocket!" << '\n';

        // A loop on how may pickpockets the user (Entity/Player) should do. based on iterations paramater.
        for (int i = 0; i < iterations; i++)
        {
            // Sleep the thread that pick pickpocks to avoid instant pickpock sessions.
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // Lock gold from other threads before updating, ensure not conflicts arise.
            std::lock_guard<std::mutex> lock(mtx);
            // Increase the player gold by how much they have stolen each iteration.
            gold += goldStolen;
        }
        // Let the user know that they have finished their pick poctet action.
        std::cout << "Pick pocketing finish!" << '\n';
    }

    // A function where you can fight another Entity object (a enemy), and steal their gold on win.
    void fight(Entity<T>& enemy) noexcept
    {
        // Print out a message to the user saying that battle has started.
        std::cout << "Battle has started!" << '\n';

        while (enemy.hp > 0 && hp > 0)
        {
            // Sleep the thead for 2 seconds, avoid the battle finishing instantly.
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            std::lock_guard<std::mutex> lock(mtx);
            // Decrease enemy hp by the ammount of damage you deal.
            enemy.hp -= first->data.damage;

            // Decrease the player hp by the ammount of damage taken by the enemy.
            hp -= enemy.first->data.damage;
        }

        // Check if you won the fight... (your hp > 0 after the fight)
        if (hp > 0)
        {
            // Print out you won.
            std::cout << "You win!" << '\n';
            // Increase player gold by the ammount the enemy had (you steal gold after you kill them)
            // Lock gold, avoid the pick Pocket thread and fight thread modifying gold at the same time.
            std::lock_guard<std::mutex> lock(mtx);
            gold += enemy.gold;
        }
        // Else, the player hp is < 0.....
        else
        {
            // Print out who killed you
            std::cout << enemy.name << " slayed you!" << '\n';
            // Return to called
            return;
        }
    }
};
