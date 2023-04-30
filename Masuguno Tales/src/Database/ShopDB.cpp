#include "ShopDB.h"

std::map<int, ShopType> ShopDB::shopDatabase;

void ShopDB::LoadShopDatabase()
{
    // Shop 1
    shopDatabase[1] = ShopType("Ryn's Shop");
    shopDatabase[1].AddItemID(1);
    shopDatabase[1].AddItemID(3);
    shopDatabase[1].AddItemID(4);
    shopDatabase[1].AddItemID(5);
    shopDatabase[1].AddItemID(6);
    shopDatabase[1].AddItemID(7);
    shopDatabase[1].AddItemID(9);
    shopDatabase[1].AddItemID(8);
    shopDatabase[1].AddItemID(10);
    shopDatabase[1].AddItemID(11);
    shopDatabase[1].AddItemID(14);
    shopDatabase[1].AddItemID(12);
    shopDatabase[1].AddItemID(15);
    shopDatabase[1].AddItemID(13);
    shopDatabase[1].AddItemID(16);
    shopDatabase[1].AddItemID(17);
    shopDatabase[1].AddItemID(18);

    // Shop 2
    shopDatabase[2] = ShopType("Potion Shop");
    shopDatabase[2].AddItemID(1);
    shopDatabase[2].AddItemID(1);
    shopDatabase[2].AddItemID(1);
    shopDatabase[2].AddItemID(1);
}
