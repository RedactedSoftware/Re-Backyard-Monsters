#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "globals.hpp"

namespace ReBackyardMonsters {

    

    class InputHelper : Singleton
    {
        void HandleInputEvent(SDL_Event e)
        {
            if (e.type == SDL_KEYDOWN)
                onKeyDown(e);
            if (e.type == SDL_KEYUP)
                onKeyUp(e);
        }
        
    }
    
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
