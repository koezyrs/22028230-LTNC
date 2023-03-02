#pragma once

#ifndef Map_h
#define Map_h

#include<string>
#include "Component/Component.h"

class Map
{
public:
    Map();
    static void LoadMap(std::string path, int sizeX, int sizeY);
    void Update();
    void Render();
    ~Map();
private:


};

#endif // Map_h
