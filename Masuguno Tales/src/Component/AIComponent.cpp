#include "AIComponent.h"
AIComponent::AIComponent(TransformComponent* trans, Vector2D startPos, float _damage, float _attackSpeed,
    float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed, bool* _trigger, std::vector<std::vector<Tile>> mapBase)
    : startPostion(startPos), trigger(_trigger), damage(_damage), attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed),
    roamSpeed(_roamSpeed), attackRange(_attackRange), stopChaseRange(_stopChaseRange), monsterState(ROAMING),
    targetX(0), targetY(0), tiles(mapBase)
{
    trigger = _trigger;
    mTransform = trans;
    mTransform->speed = roamSpeed;
    roamPosition = startPostion;

    if(tiles.empty())
    {
        std::cout << "Invalid map! Please check Map Manager! (AI Component Error!)" << std::endl;
        return;
    }
}

AIComponent::~AIComponent(){}

int AIComponent::getRandomRange(int n)
{
    int res = static_cast<float> (rand()%n);
    return res;
}

void AIComponent::Update()
{
    if(tiles.empty())
    {
        std::cout << "Invalid map! Please check Map Manager! (AI Component Error!)" << std::endl;
        return;
    }
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
            // Set target
            int playerPosX = static_cast<int>(Game::gPlayer->getTransformComponent()->position.x + GAME_PIXELS/2) / GAME_PIXELS;
            int playerPosY = static_cast<int>(Game::gPlayer->getTransformComponent()->position.y + GAME_PIXELS/2) / GAME_PIXELS;
            setTargetAndCalculateFlowField(playerPosX, playerPosY);

            mTransform->speed = chaseSpeed;

            int coordinateX = (static_cast<int>(mTransform->position.x + GAME_PIXELS/2)) / GAME_PIXELS;
            int coordinateY = (static_cast<int>(mTransform->position.y + GAME_PIXELS/2)) / GAME_PIXELS;
            mTransform->velocity.x = mTransform->speed * static_cast<float>(tiles[coordinateY][coordinateX].flowDirectionX);
            mTransform->velocity.y = mTransform->speed * static_cast<float>(tiles[coordinateY][coordinateX].flowDirectionY);


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

void AIComponent::FindTarget()
{
    float targetRange = 96.0f;
    if(mTransform->position.DistanceTo(Game::gPlayer->getTransformComponent()->position) < targetRange)
    {
        nextAttackTime = SDL_GetTicks64() + attackSpeed;
        monsterState = CHASETARGET;
    }
}

void AIComponent::setTargetAndCalculateFlowField(int targetNewX, int targetNewY) {
    if(tiles.empty())
    {
        std::cout << "Invalid map! Please check Map Manager! (AI Component Error!)" << std::endl;
        return;
    }

    // Get Map size
    int sizeX = tiles[0].size();
    int sizeY = tiles.size();

    if(targetX != targetNewX || targetY != targetNewY)
    {
        targetX = targetNewX;
        targetY = targetNewY;

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

void AIComponent::calculateDistances(int targetX, int targetY) {

    if(tiles.empty())
    {
        std::cout << "Invalid map! Please check Map Manager! (AI Component Error!)" << std::endl;
        return;
    }

    // Get Map size
    int sizeX = tiles[0].size();
    int sizeY = tiles.size();

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

void AIComponent::calculateFlowDirections() {
    if(tiles.empty())
    {
        std::cout << "Invalid map! Please check Map Manager! (AI Component Error!)" << std::endl;
        return;
    }

    // Get Map size
    int sizeX = tiles[0].size();
    int sizeY = tiles.size();

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
