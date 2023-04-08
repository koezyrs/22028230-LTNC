#pragma once
#ifndef AIComponent_h
#define AIComponent_h

#include <cstdlib>
#include <iostream>
#include <queue>

#include <SDL.h>

#include "../Game.h"
#include "../Actor.h"
#include "Component.h"
#include "../EventManager.h"
#include "../Tile.h"
#include "../Vector2D.h"
#include "../Settings.h"

class AIComponent
{
private:
    enum STATE{
        ROAMING,
        CHASETARGET,
        RECALL
    };

    Tile** tiles;
    TransformComponent* mTransform;
    Vector2D startPostion;
    bool* trigger;
    Uint64 nextAttackTime;

    float damage, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;

    STATE monsterState;
    Vector2D roamPosition;
    int targetX, targetY;
    Uint64 timeout;
public:
    AIComponent(TransformComponent* trans, Vector2D startPos, float _damage, float _attackSpeed,
    float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed, bool* _trigger)
    : startPostion(startPos), trigger(_trigger), damage(_damage), attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed),
    roamSpeed(_roamSpeed), attackRange(_attackRange), stopChaseRange(_stopChaseRange), monsterState(ROAMING),
    targetX(0), targetY(0)
    {
        trigger = _trigger;
        mTransform = trans;
        mTransform->speed = roamSpeed;
        roamPosition = startPostion;

        int sizeX = EventManager::GetMapSizeX();
        int sizeY = EventManager::GetMapSizeY();
        tiles = new Tile*[sizeY];
        for(int i = 0; i < sizeY; i++) tiles[i] = new Tile[sizeX];

        for(int i = 0; i < sizeY; i++)
        {
            for(int j = 0; j < sizeX; j++)
            {
                tiles[i][j].flowDirectionX = 0;
                tiles[i][j].flowDirectionY = 0;
                tiles[i][j].flowDistance = flowDistanceMax;
                tiles[i][j].position.x = EventManager::getMapTiles()[i][j].position.x;
                tiles[i][j].position.y = EventManager::getMapTiles()[i][j].position.y;
                tiles[i][j].isWall = EventManager::getMapTiles()[i][j].isWall;
            }
        }
    }

    ~AIComponent()
    {
        int sizeY = EventManager::GetMapSizeY();

        for(int i = 0; i < sizeY; i++) if(tiles[i] != NULL) delete[] tiles[i];
        if(tiles != NULL) delete[] tiles;
    }

    int getRandomRange(int n)
    {
        int res = static_cast<float> (rand()%n);
        return res;
    }

    void Update()
    {
        switch(monsterState)
        {
        case ROAMING:
            {
                // Move to destination
                mTransform->speed = roamSpeed;

                int coordinateX = (static_cast<int>(mTransform->position.x + GAME_PIXELS/2)) / GAME_PIXELS;
                int coordinateY = (static_cast<int>(mTransform->position.y + GAME_PIXELS/2)) / GAME_PIXELS;
                mTransform->velocity.x = mTransform->speed * static_cast<float>(tiles[coordinateY][coordinateX].flowDirectionX);
                mTransform->velocity.y = mTransform->speed * static_cast<float>(tiles[coordinateY][coordinateX].flowDirectionY);

                float reachedPositionDistance = 33.0f;
                if(mTransform->position.DistanceTo(roamPosition) < reachedPositionDistance)
                {
                    int rangeX = getRandomRange(4);
                    int rangeY = getRandomRange(4);
                    int startCoordX = static_cast<int>(startPostion.x) / GAME_PIXELS;
                    int startCoordY = static_cast<int>(startPostion.y) / GAME_PIXELS;
                    int nextMoveX = startCoordX + rangeX;
                    int nextMoveY = startCoordY + rangeY;
                    while(tiles[nextMoveY][nextMoveX].isWall)
                    {
                        rangeX = getRandomRange(4);
                        rangeY = getRandomRange(4);
                        startCoordX = static_cast<int>(startPostion.x) / GAME_PIXELS;
                        startCoordY = static_cast<int>(startPostion.y) / GAME_PIXELS;
                        nextMoveX = startCoordX + rangeX;
                        nextMoveY = startCoordY + rangeY;
                    }
                    roamPosition.x = nextMoveX * GAME_PIXELS;
                    roamPosition.y = nextMoveY * GAME_PIXELS;
                    setTargetAndCalculateFlowField(nextMoveX, nextMoveY);
                }

                if(*trigger) FindTarget();
                break;
            }

        case CHASETARGET:
            {
                mTransform->speed = chaseSpeed;

                int coordinateX = (static_cast<int>(mTransform->position.x + GAME_PIXELS/2)) / GAME_PIXELS;
                int coordinateY = (static_cast<int>(mTransform->position.y + GAME_PIXELS/2)) / GAME_PIXELS;
                mTransform->velocity.x = mTransform->speed * static_cast<float>(EventManager::getMapTiles()[coordinateY][coordinateX].flowDirectionX);
                mTransform->velocity.y = mTransform->speed * static_cast<float>(EventManager::getMapTiles()[coordinateY][coordinateX].flowDirectionY);


                if(mTransform->position.DistanceTo(Game::gPlayer->getTransformComponent()->position) < attackRange)
                {
                    // Attack the player in range

                    if( SDL_GetTicks64() > nextAttackTime )
                    {
                        // Attack
                        Game::gPlayer->mStats->ApplyDamage(damage);
                        nextAttackTime = SDL_GetTicks64() + attackSpeed;

                    }

                }

                if(mTransform->position.DistanceTo(Game::gPlayer->getTransformComponent()->position) > stopChaseRange)
                {
                    // Too far from the target
                    monsterState = RECALL;
                }
                break;
            }

        case RECALL:
            {
                // Set target
                int startX = static_cast<int>(startPostion.x + GAME_PIXELS/2 ) / GAME_PIXELS;
                int startY = static_cast<int>(startPostion.y + GAME_PIXELS/2) / GAME_PIXELS;
                setTargetAndCalculateFlowField(startX, startY);

                // Move to destination
                int coordinateX = (static_cast<int>(mTransform->position.x + GAME_PIXELS/2)) / GAME_PIXELS;
                int coordinateY = (static_cast<int>(mTransform->position.y + GAME_PIXELS/2)) / GAME_PIXELS;
                mTransform->velocity.x = mTransform->speed * static_cast<float>(tiles[coordinateY][coordinateX].flowDirectionX);
                mTransform->velocity.y = mTransform->speed * static_cast<float>(tiles[coordinateY][coordinateX].flowDirectionY);

                float reachedPositionDistance = 33.0f;
                if(mTransform->position.DistanceTo(startPostion) < reachedPositionDistance)
                {
                    roamPosition.x = startPostion.x;
                    roamPosition.y = startPostion.y;
                    monsterState = ROAMING;
                }
                if(*trigger) FindTarget();
                break;
            }

        }
    }

    void FindTarget()
    {
        float targetRange = 96.0f;
        if(mTransform->position.DistanceTo(Game::gPlayer->getTransformComponent()->position) < targetRange)
        {
            nextAttackTime = SDL_GetTicks64() + attackSpeed;
            monsterState = CHASETARGET;
        }
    }

    void setTargetAndCalculateFlowField(int targetNewX, int targetNewY) {
        if(targetX != targetNewX || targetY != targetNewY)
        {
            targetX = targetNewX;
            targetY = targetNewY;
            // Get Map size
            int sizeX = EventManager::GetMapSizeX();
            int sizeY = EventManager::GetMapSizeY();

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
                calculateDistances(targetX, targetY);
                calculateFlowDirections();
            }
        }
    }

    void calculateDistances(int targetX, int targetY) {
        // Get map size
        int sizeX = EventManager::GetMapSizeX();
        int sizeY = EventManager::GetMapSizeY();

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
            int currentX = static_cast<int>(tileCurrent.position.x);
            int currentY = static_cast<int>(tileCurrent.position.y);

            //Check each of the neighbors;
            for (int i = 0; i < 4; i++) {
                int neighborX = currentX + moveX[i];
                int neighborY = currentY + moveY[i];
                //Ensure that the neighbor exists and isn't a wall.
                if (neighborY >= 0 && neighborY < sizeY &&
                    neighborX >= 0 && neighborX < sizeX ) {
                    if(tiles[neighborY][neighborX].isWall) continue;
                    //Check if the tile has been assigned a distance yet or not.
                    if (tiles[neighborY][neighborX].flowDistance == flowDistanceMax) {
                        //If not the set it's distance and add it to the queue.
                        tiles[neighborY][neighborX].flowDistance = tiles[currentY][currentX].flowDistance + 1;
                        listTilesToCheck.push(tiles[neighborY][neighborX]);
                    }
                }
            }
        }
    }

    void calculateFlowDirections() {
        // Get map size
        int sizeX = EventManager::GetMapSizeX();
        int sizeY = EventManager::GetMapSizeY();

        //The offset of the neighboring tiles to be checked.
        int moveX[4] = {0,0,-1,1};
        int moveY[4] = {-1,1,0,0};

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




};

#endif // AIComponent_h
