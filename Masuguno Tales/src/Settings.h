#pragma once

#ifndef Settings_h
#define Settings_h
const char GAME_TITLE[] = "Masuguno Tales";
const char GAME_FONT[] = "font/game.ttf";
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 576;
const int GAME_PIXELS = 32;
const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 32;
const int GAME_SCALE = 1;
const int FPS = 60;
const int frameDelay = 1000 / FPS;
const int PLAYER_VELOCITY = 5;
const int MAX_INVENTORY_SLOTS = 35;
const int MAX_EQUIPMENT_SLOTS = 10;


// Enums

enum EQUIPMENT_TAG
{
    WEAPON,
    SHIELD,
    HELMET,
    ARMOR,
    GLOVE,
    SHOES,
    CAPE,
    RING,
    NECKLACE,
    MEDAL
};
#endif // Settings_h
