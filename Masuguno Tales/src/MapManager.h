#pragma once
#ifndef MapManager_h
#define MapManager_h

#include <map>
#include <vector>
#include <fstream>
#include "Game.h"
#include "Map.h"
#include "Actor.h"
#include "Event.h"
#include "Tile.h"
#include "Settings.h"

class MapManager
{
public:
    static void LoadMap(int map_id);
    static std::map<int, std::vector<std::vector<Tile>>> mapBase;
    static std::map<int, std::shared_ptr<Map>> mapDatabase;
    static void LoadMapDatabase();
private:
    static std::vector<std::vector<Tile>> setupMap(const char* msgnFile, int sizeX, int sizeY);
    static void LoadMap1();
    static void LoadMap2();
    static void LoadMap3();
};

#endif // MapManager_h
