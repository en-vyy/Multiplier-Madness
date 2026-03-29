#pragma once

class ShopSystem {
public:
    // Mengembalikan pilihan item (1-3), 0 jika keluar, dan -1 jika uang tidak cukup
    int browseShop(int& playerGold);
};