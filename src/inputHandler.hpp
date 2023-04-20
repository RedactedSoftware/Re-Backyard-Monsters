#include <SDL2/SDL.h>
#include "globals.hpp"
#include <vector>
#include <string>


namespace InputHandler {
    inline bool isWDown = false;
    inline bool isADown = false;
    inline bool isSDown = false;
    inline bool isDDown = false;
    inline bool isSpaceDown = false;

    inline void detectKeyDownEvent() {
        if (Globals::event.type == SDL_KEYDOWN) {
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                Globals::shouldQuit = true;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_INSERT)
                Globals::isPaused = !Globals::isPaused;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_W)
                isWDown = true;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_A)
                isADown = true;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_S)
                isSDown = true;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_D)
                isDDown = true;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                isSpaceDown = true;
        }
    }
    inline void detectKeyUpEvent() {
        if (Globals::event.type == SDL_KEYUP) {
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_W)
                isWDown = false;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_A)
                isADown = false;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_S)
                isSDown = false;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_D)
                isDDown = false;
            if (Globals::event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                isSpaceDown = false;
        }
    }

    inline std::vector<int> getMousePosition() {
        //TODO Make this function as expected if the window has been resized.
        int x, y;
        std::vector<int> vector;
        if(Globals::isInFocus)
            SDL_GetMouseState(&x,&y);
        vector.push_back(x);
        vector.push_back(y);
        return vector;
    }
}