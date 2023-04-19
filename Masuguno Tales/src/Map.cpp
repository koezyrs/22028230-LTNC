#include "Map.h"

Map::Map(int _id)
: id(_id), width(0), height(0), sizeX(0), sizeY(0), targetX(0), targetY(0), position(), mTexture(NULL) {}

Map::~Map()
{
    ClearMap();
}

void Map::LoadMap(std::string maptex, const char* mapfile, int _sizeX, int _sizeY)
{
    mTexture = TextureManager::GetTexture(maptex);
    SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);
    srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    position.x = 0.0f;
    position.y = 0.0f;
    sizeX = _sizeX;
    sizeY = _sizeY;
    std::fstream fileContainCoordiate;
    char tile;

    tiles = new Tile*[_sizeY];
    for(int i = 0 ; i < _sizeY; i++) tiles[i] = new Tile[_sizeX];

    fileContainCoordiate.open(mapfile);
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0 ; x < sizeX; x++)
        {
            fileContainCoordiate.get(tile);
            int id = atoi(&tile);
            if(id == 1)
            {
                AddWall(x * GAME_PIXELS * GAME_SCALE, y * GAME_PIXELS * GAME_SCALE);
                tiles[y][x] = {static_cast<float>(x), static_cast<float>(y), true};
            }else
            {
                tiles[y][x] = {static_cast<float>(x), static_cast<float>(y), false};
            }
            fileContainCoordiate.ignore();
        }
    }
    fileContainCoordiate.close();
}

void Map::Refresh()
{
    walls.erase(std::remove_if(walls.begin(), walls.end(),
        [](auto& theWall){return !theWall->isActive();}), walls.end());

    /*
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](Monster* theMonster){return !theMonster->isActive();}), monsters.end());
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

    int targetXNew = static_cast<int>(Game::gPlayer->getTransformComponent()->position.x) / GAME_PIXELS;
    int targetYNew = static_cast<int>(Game::gPlayer->getTransformComponent()->position.y) / GAME_PIXELS;
    setTargetAndCalculateFlowField(targetXNew,targetYNew);

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
void Map::AddWall(int x, int y)
{
    walls.emplace_back(std::make_shared<Wall>(static_cast<float>(x), static_cast<float>(y)));
}

void Map::AddMonster(float x, float y, int monster_id)
{
    MonsterType monster = MonsterDB::monsterDatabase[monster_id];
    if(!monster.monsterSprite.empty())
    {
        monsters.emplace_back(std::make_shared<Monster>(monster.monster_id, x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE, monster.monsterName
                                          , monster.monsterSprite, monster.damage, monster.health, monster.attackSpeed,
                                          monster.attackRange, monster.stopChaseRange, monster.chaseSpeed, monster.roamSpeed));
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
    for(int i = 0; i < sizeY; i++)
    {
        if(tiles[i] != NULL) delete[] tiles[i];
    }
    if(tiles != NULL) delete[] tiles;
    /*
    for(auto& w : walls) {w->destroy();}
    for(auto& m : monsters) {m->destroy();}
    for(auto& e : events) {e->destroy();}
    for(auto& n : npcs) {n->destroy();}
    for(auto& p : projectiles) {p->destroy();}
    */
    walls.clear();
    monsters.clear();
    events.clear();
    npcs.clear();
    projectiles.clear();
    Game::gPlayer->getKeyboardController()->unsetTarget();
    mTexture = NULL;
}

void Map::setTargetAndCalculateFlowField(int targetXNew, int targetYNew) {
    //Check if the target is new.
    if (targetX != targetXNew || targetY != targetYNew) {
        targetX = targetXNew;
        targetY = targetYNew;

        //Ensure the target is in bounds.
        if ((targetX >=0) && (targetX < sizeX) &&
            (targetY >=0) && (targetY < sizeY)) {

            //Reset the tile flow data.
            for (int i = 0; i < sizeY; i++)
            {
                for(int j = 0; j < sizeX; j++)
                {
                    tiles[i][j].flowDirectionX = 0;
                    tiles[i][j].flowDirectionY = 0;
                    tiles[i][j].flowDistance = flowDistanceMax;
                }
            }

            //Calculate the flow field.
            calculateDistances();
            calculateFlowDirections();
        }
    }
}

void Map::calculateDistances() {
    //Create a queue that will contain the indices to be checked.
    std::queue<Tile> listTilesToCheck;
    //Set the target tile's flow value to 0 and add it to the queue.
    tiles[targetY][targetX].flowDistance = 0;
    listTilesToCheck.push(tiles[targetY][targetX]);

    //The offset of the neighboring tiles to be checked.
    int moveX[4] = {0,0,-1,1};
    int moveY[4] = {-1,1,0,0};

    //Loop through the queue and assign distance to each tile.
    while (listTilesToCheck.empty() == false) {
        Tile tileCurrent = listTilesToCheck.front();
        listTilesToCheck.pop();

        //Check each of the neighbors;
        for (int i = 0; i < 4; i++) {
            int neighborX = static_cast<int>(tileCurrent.position.x) + moveX[i];
            int neighborY = static_cast<int>(tileCurrent.position.y) + moveY[i];
            //Ensure that the neighbor exists and isn't a wall.
            if (neighborY >= 0 && neighborY < sizeY &&
                neighborX >= 0 && neighborX < sizeX ) {
                if(tiles[neighborY][neighborX].isWall) continue;
                //Check if the tile has been assigned a distance yet or not.
                if (tiles[neighborY][neighborX].flowDistance == flowDistanceMax) {
                    //If not the set it's distance and add it to the queue.
                    tiles[neighborY][neighborX].flowDistance = tiles[static_cast<int>(tileCurrent.position.y)][static_cast<int>(tileCurrent.position.x)].flowDistance + 1;
                    listTilesToCheck.push(tiles[neighborY][neighborX]);
                }
            }
        }
    }
}

void Map::calculateFlowDirections() {
    //The offset of the neighboring tiles to be checked.
    int moveX[8] = {0,0,-1,1};
    int moveY[8] = {-1,1,0,0};

    for(int i = 0; i < sizeY; i++)
    {
        for(int j = 0; j < sizeX; j++)
        {
            if(tiles[i][j].flowDistance == flowDistanceMax) continue;
            unsigned char flowFieldBest = tiles[i][j].flowDistance;
            for(int k = 0; k < 4; k++)
            {
                int neighborX = j + moveX[k];
                int neighborY = i + moveY[k];
                if (neighborY >= 0 && neighborY < sizeY && neighborX >= 0 && neighborX < sizeX){
                    if(tiles[neighborY][neighborX].isWall) continue;
                    if(tiles[neighborY][neighborX].flowDistance < flowFieldBest){
                        flowFieldBest = tiles[neighborY][neighborX].flowDistance;
                        tiles[i][j].flowDirectionX = moveX[k];
                        tiles[i][j].flowDirectionY = moveY[k];
                    }
                }
            }
        }
    }

}
