#pragma once
#include <SDL2/SDL.h>

namespace Globals {
    inline const int screenWidth = 1152;
    inline const int screenHeight = 864;
    inline int minimumFrameDelta = 1000; //1000 FPS to circumvent divide by zero.
    inline float frameDelta = 0;
    inline int frameCount = 1;
    inline SDL_Window *window = nullptr;
    inline bool shouldQuit = false;
    inline SDL_Event event;
    inline bool isPaused = false;
    inline int tickCount = 1;
    inline int minimumTickDelta = 15625; // 64 tick.
    inline float tickDelta = 0;
    inline bool isInFocus;
}