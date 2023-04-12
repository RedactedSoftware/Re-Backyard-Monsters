#pragma once
#include <SDL2/SDL.h>
namespace Globals {
    inline const int screenWidth = 960;
    inline const int screenHeight = 540;
    inline int minimumFrameDelta = 1000;
    inline float frameDelta = 0;
    inline int frameCount = 1;
    inline SDL_Window *window = nullptr;
    inline SDL_Event event;
    inline bool shouldQuit = false;
    inline bool shouldTick = true;
    inline int tickCount = 1;
    inline int minimumTickDelta = 15625; // 64 tick.
    inline float tickDelta = 0;
    inline int lineX1 = 1;
    inline int lineY1 = 270;
    inline int lineX2 = 960;
    inline int lineY2 = 270;
}