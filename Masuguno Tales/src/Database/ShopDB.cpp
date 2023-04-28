#include "ShopDB.h"

std::map<int, ShopType> ShopDB::shopDatabase;

void ShopDB::LoadShopDatabase()
{
    // Shop 1
    shopDatabase[1] = ShopType("Weapon Shop");
    shopDatabase[1].AddItemID(1);
    shopDatabase[1].AddEquipmentID(1);
    shopDatabase[1].AddItemID(1);
    shopDatabase[1].AddEquipmentID(1);
    shopDatabase[1].AddItemID(1);
    shopDatabase[1].AddEquipmentID(1);
    shopDatabase[1].AddItemID(1);
    shopDatabase[1].AddEquipmentID(1);
    // Shop 2
    shopDatabase[2] = ShopType("Potion Shop");
    shopDatabase[2].AddItemID(1);
    shopDatabase[2].AddItemID(1);
    shopDatabase[2].AddItemID(1);
    shopDatabase[2].AddItemID(1);
}
