#include "ItemDB.h"

std::map<int, ItemType> ItemDB::itemDatabase;
void ItemDB::LoadItemDatabase()
{
    itemDatabase[1] = ItemType(
        1,                                          // id (Must match database)
        "Item-HPPotion",                            // Item
        5,                                          // Max stack
        "Potion",                                   // Tag
        "Medium Potion",                            // Name
        "A medium potion that can heal you 10HP per each!", // Description
        10,
        2,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 10;
        }
    );
}

