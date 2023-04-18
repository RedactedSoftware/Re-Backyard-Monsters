#pragma once
#include <SDL2/SDL.h>
#include <string>
enum {LOCALPLAYER = 0, PLAYER = 1};
struct entity {
    int type;
    bool draw;
    int posX, posY, width, height, velocityX, velocityY;
    SDL_Rect renderedEntity;
};
