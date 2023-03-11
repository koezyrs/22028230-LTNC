#include "src/Game.h"

Game* game = nullptr;

int main(int argc, char* args[]){

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->loadMedia();

    while(game->running()){
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}
