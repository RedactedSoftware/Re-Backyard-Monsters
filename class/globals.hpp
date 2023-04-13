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
    inline bool isPaused = false;
    inline int tickCount = 1;
    inline int minimumTickDelta = 15625; // 64 tick.
    inline float tickDelta = 0;
    inline SDL_Rect localPlayer = {screenWidth/2,screenHeight/2,16,16};
    inline SDL_Rect floor = {0, screenHeight - 20, screenWidth, 20};
    inline bool isInFocus;
}