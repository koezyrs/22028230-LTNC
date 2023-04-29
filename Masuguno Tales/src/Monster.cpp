#include "Monster.h"

Monster::Monster(int _monster_id,float _x, float _y, int _width, int _height, int _scale,  std::string _monsterName,
                 std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                 float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed, std::vector<std::vector<Tile>> mapBase)
: monster_id(_monster_id),startPosition(_x,_y), monsterName(_monsterName), monsterSprite(_monsterSprite), damage(_damage), health(_health), maxhealth(_health),
    attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed), roamSpeed(_roamSpeed), attackRange(_attackRange),
    stopChaseRange(_stopChaseRange) ,timeSpawn(0)
{
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(monsterSprite, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Monster", true);
    mName = new NameComponent(mTransform, monsterName, GAME_FONT, 10, SDL_Color{255,0,0});
    mAI = new AIComponent(mTransform, mCollider, startPosition, damage, attackSpeed, attackRange, stopChaseRange, chaseSpeed, roamSpeed, &trigger, mapBase);

    // HP Bar
    HPBarTexture = TextureManager::GetTexture("HPBar");
    hpSourceRectBack = {0,0,32,4};
    hpDestRectBack = {static_cast<int>(_x + (_width - 32)/2), static_cast<int>(_y + _height) + 3, 32,4};
    hpSourceRectOver = {0,12,32,4};
    hpDestRectOver = {static_cast<int>(_x + (_width - 32)/2), static_cast<int>(_y + _height) + 3, 32,4};

    // Targeted Texture
    targetedTexture = TextureManager::GetTexture("Target");
    targetedSrcRect = {0,0,28,28};
    targetedDestRect = {static_cast<int>(_x) + 28, static_cast<int>(_y) - 3, 28,28};
}

void Monster::ApplyDamage(float _damage)
{
    float LO = 0.5f;
    float HI = 1.5f;
    float D = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    int healthLose = _damage * D;

    if(healthLose <= 0) return;
    if(health - healthLose <= 0) health = 0;
    else health -= healthLose;
}

void Monster::Update()
{
    // Wait for spawn
    if(!active)
    {
        if(SDL_GetTicks64() > timeSpawn)
        {
            setPosition(startPosition.x, startPosition.y);
            mTransform->Update();
            mCollider->Update();
            mSprite->Update();
            mName->Update();
            health = maxhealth;
            active = true;
        }
        return;
    }

    // Check if HP <= 0
    if(health <= 0) {
        active = false;
        Game::gPlayer->mStats->Experience += 20;
        Game::gPlayer->getKeyboardController()->unsetTarget();
        targeted = false;
        trigger = false;
        float spawnWaitTime = 10000;
        timeSpawn = SDL_GetTicks64() + spawnWaitTime;
        mTransform->position = Vector2D(0,0); // The deadzone
        mTransform->Update();
        mCollider->Update();
        mSprite->Update();
        mName->Update();
        Game::gQuestLog->totalMonsterKilled[monster_id] = Game::gQuestLog->totalMonsterKilled[monster_id] + 1;
        return;
    }

    // Update component
    mAI->Update();
    mTransform->Update();
    mCollider->Update();
    mSprite->Update();
    mName->Update();

    // HP Bar
        hpDestRectBack.x = static_cast<int>(mTransform->position.x + (mTransform->width - 32)/2 - Game::gCamera.x);
        hpDestRectBack.y = static_cast<int>(mTransform->position.y + mTransform->height + 3 - Game::gCamera.y);
        hpDestRectOver.x = static_cast<int>(mTransform->position.x + (mTransform->width - 32)/2 - Game::gCamera.x);
        hpDestRectOver.y = static_cast<int>(mTransform->position.y + mTransform->height + 3 - Game::gCamera.y);
        hpDestRectOver.w = static_cast<int>(32 * health/maxhealth);

    // Targeted dest rect
        targetedDestRect.x = static_cast<int>(mTransform->position.x + mTransform->width - Game::gCamera.x);
        targetedDestRect.y = static_cast<int>(mTransform->position.y - 3  - Game::gCamera.y);

}
void Monster::Render()
{
    if(!active) return;
    mSprite->Render();
    mName->Render();
    if(trigger)
    {
        TextureManager::Draw(HPBarTexture, hpSourceRectBack, hpDestRectBack);
        TextureManager::Draw(HPBarTexture, hpSourceRectOver, hpDestRectOver);
    }

    if(targeted)
    {
        TextureManager::Draw(targetedTexture, targetedSrcRect, targetedDestRect);
    }
}

TransformComponent* Monster::getTransformComponent() {return mTransform;}
ColliderComponent* Monster::getColliderComponent() {return mCollider;}
SpriteComponent* Monster::getSpriteComponent() {return mSprite;}
bool Monster::isActive() const {return active;}
void Monster::setTrigger() {trigger = true;}
void Monster::destroy() {active = false;}
void Monster::ApplyDamage(float _damage);
float Monster::getHP() {return health;}
float Monster::getMaxHP() {return maxhealth;}
void Monster::setTargeted() {targeted = true;}
void Monster::unTargeted() {targeted = false;}
bool Monster::isTargeted() {return targeted;}
std::string Monster::getMonsterName() {return monsterName;}
void Monster::setPosition(float x, float y) {mTransform->position = Vector2D(x,y);}
Monster::~Monster()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
//    delete mAI;
}
