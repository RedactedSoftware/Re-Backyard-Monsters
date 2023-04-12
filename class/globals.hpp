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
    inline int lineX1 = 1;
    inline int lineY1 = 270;
    inline int lineX2 = 960;
    inline int lineY2 = 270;
    inline SDL_Rect localPlayer = {screenWidth/2,screenHeight/2,16,16};
    inline bool isInFocus = (bool) nullptr;
    inline bool isWDown = false;
    inline bool isADown = false;
    inline bool isSDown = false;
    inline bool isDDown = false;
}