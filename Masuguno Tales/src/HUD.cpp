#include "HUD.h"

HUD::HUD() : target(nullptr)
{
    HUDBase = TextureManager::GetTexture("HUDBase");
    HUDBars = TextureManager::GetTexture("HUDBars");
    TargetHP = TextureManager::GetTexture("TargetHPBar");
    playerName = new Label(GAME_FONT, Game::gPlayer->getNameComponent()->mName.c_str()  ,10,370, 485, White, 120, false, []{});
    playerLevel = new Label(GAME_FONT, " ",10,550,485, White, 120, false, []{});
    playerHP = new Label(GAME_FONT, " ",10,370,503, White, 120, false, []{});
    playerMP = new Label(GAME_FONT, " ",10,570,503, White, 120, false, []{});
    playerExperience = new Label(GAME_FONT, " ",10,495,495, White, 120, false, []{});
    targetName = new Label(GAME_FONT, " ", 10, 420, 47, White, 120, false, []{});
    targetHP = new Label(GAME_FONT, " ", 10, 440, 53, White, 120, false, []{});
    systemMessage = new Label(GAME_FONT, " ", 10, 460, 80, Black, 360, false, []{});

    BaseSrcRect = {0,0,365,48};
    BaseDestRect = {329,478,365,48};

    HPSrcRect = {0,0,172,22};
    HPDestRect = {329,501,172,22};

    MPSrcRect = {0,26,172,22};
    MPDestRect = {524,501,172,22};

    TargetHPSrcRectBack = {0,0,210,18};
    TargetHPDestRectBack = {407, 50,210,18};
    TargetHPSrcRectOver = {0,22,210,18};
    TargetHPDestRectOver = {407, 50,210,18};
}

HUD::~HUD()
{
    delete playerName;
    delete playerLevel;
    delete playerHP;
    delete playerMP;
    delete playerExperience;

    HUDBars = NULL;
    HUDBase = NULL;
}

void HUD::Update()
{
    // Reset label
        playerLevel->Reset();
        playerHP->Reset();
        playerMP->Reset();
        playerExperience->Reset();
        targetName->Reset();
        targetHP->Reset();
        std::string LevelStr = "Level " + to_string(Game::gPlayer->mStats->Level);
        std::string HPStr = to_string(Game::gPlayer->mStats->Health) + "/" + to_string(Game::gPlayer->mStats->MaxHealth);
        std::string MPStr = to_string(Game::gPlayer->mStats->Mana) + "/" + to_string(Game::gPlayer->mStats->MaxMana);
        std::string EXPStr = to_string(Game::gPlayer->mStats->Experience) + "/" + to_string(Game::gPlayer->mStats->ExperienceToNextLevel);

    //Update player status here
        playerLevel = new Label("data files/font/game.ttf", LevelStr.c_str(),10,550,485, White, 120, false, []{});
        playerHP = new Label("data files/font/game.ttf", HPStr.c_str(),10,370,503, White, 120, false, []{});
        playerMP = new Label("data files/font/game.ttf", MPStr.c_str(),10,570,503, White, 120, false, []{});
        playerExperience = new Label("data files/font/game.ttf", EXPStr.c_str(),10,495,495, White, 120, false, []{});

    //HPBar
        HPSrcRect.w = static_cast<int>(172 * static_cast<float>(Game::gPlayer->mStats->Health) / static_cast<float>(Game::gPlayer->mStats->MaxHealth));
        HPDestRect.w = HPSrcRect.w;

    //MPBar
        MPDestRect.w = MPSrcRect.w = static_cast<int>(172 * static_cast<float>(Game::gPlayer->mStats->Mana) / static_cast<float>(Game::gPlayer->mStats->MaxMana));
        MPSrcRect.x = 172 - MPSrcRect.w;
        MPDestRect.x = 524 + MPSrcRect.x;

    // Target HP Bar
        target = Game::gPlayer->getKeyboardController()->getTarget();
        if(target != nullptr)
        {
            TargetHPDestRectOver.w = static_cast<int> (210* target->getHP() / target->getMaxHP());
        }

    // Target label
        if(target != nullptr)
        {
            std::string TargName = target->getMonsterName();
            std::string TargHP = to_string((int)target->getHP()) + "/" + to_string((int)target->getMaxHP());
            targetName = new Label("data files/font/game.ttf", TargName.c_str(), 10, 420, 38, Black, 120, false, []{});
            targetHP = new Label("data files/font/game.ttf", TargHP.c_str(), 10, 440, 53, White, 120, false, []{});
        }

    // System Message Label
        if(SDL_GetTicks64() > systemMessageTimeout)
        {
            systemMessage->Reset();
            systemMessage = new Label("data files/font/game.ttf", " ", 10, 460, 50, Black, 360, false, []{});
        }
}
void HUD::Render()
{
    TextureManager::Draw(HUDBase, BaseSrcRect,BaseDestRect);
    TextureManager::Draw(HUDBars, HPSrcRect, HPDestRect);
    TextureManager::Draw(HUDBars, MPSrcRect, MPDestRect);
    if(target != nullptr)
    {
        TextureManager::Draw(TargetHP, TargetHPSrcRectBack, TargetHPDestRectBack);
        TextureManager::Draw(TargetHP, TargetHPSrcRectOver, TargetHPDestRectOver);
        targetName->Render();
        targetHP->Render();
    }

    // Render character label
    playerLevel->Render();
    playerName->Render();
    playerHP->Render();
    playerMP->Render();
    playerExperience->Render();

    // Render system message
    systemMessage->Render();
}

void HUD::setSystemMessage(std::string _message, Uint64 timeout)
{
    systemMessage->Reset();
    systemMessage = new Label("data files/font/game.ttf", _message.c_str(), 10, 460, 80, Black, 360, false, []{});
    systemMessageTimeout = SDL_GetTicks64() + timeout;
}
