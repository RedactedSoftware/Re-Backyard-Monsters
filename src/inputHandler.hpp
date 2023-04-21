#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "globals.hpp"

namespace InputHandler {
    inline bool isWDown = false;
    inline bool isADown = false;
    inline bool isSDown = false;
    inline bool isDDown = false;
    inline bool isSpaceDown = false;
    inline bool isMouse1Down = false;

    inline std::vector<int> getMousePosition() {
        //TODO Make this function work as expected if the window has been resized.
        int x, y;
        std::vector<int> vector;
        if(Globals::isInFocus)
            SDL_GetMouseState(&x,&y);
        vector.push_back(x);
        vector.push_back(y);
        return vector;
    }

    inline void detectMouseDownEvent() {
        if (Globals::event.type == SDL_MOUSEBUTTONDOWN)
            isMouse1Down = true;

    }
    inline void detectMouseUpEvent() {
        if(Globals::event.type == SDL_MOUSEBUTTONUP)
            isMouse1Down = false;

    }

}