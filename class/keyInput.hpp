#include <SDL2/SDL.h>
#include "globals.hpp"
#include <vector>
#include <string>


namespace keyInput {
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
}