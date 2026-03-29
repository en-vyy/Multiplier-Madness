#include "ShopSystem.h"
#include <iostream>

int ShopSystem::browseShop(int& playerGold) {
    std::cout << "\n--- MODIFIER SHOP (Your Gold: " << playerGold << ") ---\n";
    std::cout << "1. Buy Flat Bonus (+500)     - Cost: 10 Gold\n";
    std::cout << "2. Buy Double Score (x2)     - Cost: 25 Gold\n";
    std::cout << "3. Buy Square Score (^2)     - Cost: 50 Gold\n";
    std::cout << "0. Leave Shop\n";
    
    int choice;
    std::cout << "Choose an option: ";
    std::cin >> choice;

    int cost = 0;
    if (choice == 1) cost = 10;
    else if (choice == 2) cost = 25;
    else if (choice == 3) cost = 50;

    if (choice >= 1 && choice <= 3) {
        if (playerGold >= cost) {
            playerGold -= cost;
            std::cout << ">>> Purchase successful! Remaining Gold: " << playerGold << " <<<\n";
            return choice;
        } else {
            std::cout << ">>> Not enough Gold! Please choose another item or leave. <<<\n";
            return -1; 
        }
    }
    return 0; // Pemain menekan 0 untuk keluar
}