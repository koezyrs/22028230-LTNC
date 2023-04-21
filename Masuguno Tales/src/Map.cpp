#include "Map.h"

Map::Map(int _id)
: id(_id), width(0), height(0), sizeX(0), sizeY(0), targetX(0), targetY(0), position(), mTexture(NULL) {}

Map::~Map()
{
    walls.clear();
    monsters.clear();
    events.clear();
    npcs.clear();
    projectiles.clear();
    Game::gPlayer->getKeyboardController()->unsetTarget();
    mTexture = NULL;
}

void Map::LoadMap(std::string maptex, std::vector<std::vector<Tile>> mapBase)
{
    mTexture = TextureManager::GetTexture(maptex);
    SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);
    srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    position.x = 0.0f;
    position.y = 0.0f;
    if(mapBase.empty()){
        std::cerr << "Mapbase is empty! Please check Map Manager!" << std::endl;
        return;
    }
    sizeX = mapBase[0].size();
    sizeY = mapBase.size();

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0 ; x < sizeX; x++)
        {
            if(mapBase[y][x].isWall)
                AddWall(mapBase[y][x].position.x * GAME_PIXELS * GAME_SCALE, mapBase[y][x].position.y * GAME_PIXELS * GAME_SCALE);
        }
    }
}

void Map::Refresh()
{
    walls.erase(std::remove_if(walls.begin(), walls.end(),
        [](auto& theWall){return !theWall->isActive();}), walls.end());

    /*
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](auto& theMonster){return !theMonster->isActive();}), monsters.end());
    */
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](auto& theNPC) {return !theNPC->isActive();}), npcs.end());

    events.erase(std::remove_if(events.begin(), events.end(),
        [](auto& theEvent){return !theEvent->isActive();}), events.end());

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](auto& theProjectile){return !theProjectile->isActive();}), projectiles.end());

}

void Map::Update()
{
    destRect.x = position.x - Game::gCamera.x;
    destRect.y = position.y - Game::gCamera.y;

    for(auto& w : walls)
    {
        w->Update();
    }

    for(auto& m : monsters)
    {
        m->Update();
    }

    for(auto& n : npcs)
    {
        n->Update();
    }

    for(auto& e : events)
    {
        e->Update();
    }

    for(auto& p : projectiles)
    {
        p->Update();
    }
}

void Map::RenderBottomLayer()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
}

void Map::RenderUpperLayer()
{
    for(auto& m : monsters)
    {
        m->Render();
    }

    for(auto& n : npcs)
    {
        n->Render();
    }

    for(auto& p : projectiles)
    {
        p->Render();
    }
}
void Map::AddWall(float x, float y)
{
    walls.emplace_back(std::make_shared<Wall>(x,y));
}

void Map::AddMonster(float x, float y, int monster_id, std::vector<std::vector<Tile>> mapBase)
{
    MonsterType monster = MonsterDB::monsterDatabase[monster_id];
    if(!monster.monsterSprite.empty())
    {
        monsters.emplace_back(std::make_shared<Monster>(monster.monster_id, x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE, monster.monsterName
                                          , monster.monsterSprite, monster.damage, monster.health, monster.attackSpeed,
                                          monster.attackRange, monster.stopChaseRange, monster.chaseSpeed, monster.roamSpeed,mapBase));
    }
    else
    {
        std::cerr << "Can not find monster id " << monster_id << "! Please check Monster Database!";
    }
}

void Map::AddEvent(float x, float y, std::function<void()> func)
{
    events.emplace_back(std::make_shared<Event>(x,y, func));
}

void Map::AddNPC(float x, float y, const char* filepath, std::string name)
{
    npcs.emplace_back(std::make_shared<NPC>(x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE, filepath, name));
}

void Map::AddProjectile(float x, float y, int frames, std::string skillSprite, float _damage)
{
    projectiles.emplace_back(std::make_shared<Projectile>(x, y, frames, 100, "Player", skillSprite, _damage));
}

int Map::getWidth()
{
    return width;
}
int Map::getHeight()
{
    return height;
}
int Map::getSizeX()
{
    return sizeX;
}
int Map::getSizeY()
{
    return sizeY;
}
void Map::ClearMap()
{
    walls.clear();
    monsters.clear();
    events.clear();
    npcs.clear();
    projectiles.clear();
    Game::gPlayer->getKeyboardController()->unsetTarget();
    mTexture = NULL;
}
