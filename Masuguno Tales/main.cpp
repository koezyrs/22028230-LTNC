#include "include/Game.h"

Game* game = nullptr;

int main(int argc, char* args[]){
    game = new Game();
    game->init("Masuguno Tales", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    return 0;
}
