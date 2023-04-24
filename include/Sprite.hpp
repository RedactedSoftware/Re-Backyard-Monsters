#pragma once

#include <vector>
#include <Vector2.hpp>
#include <Rectangle.hpp>
#include <SDL2/SDL.h>

namespace ReBackyardMonsters {

    struct Quad
    {
        Rectangle Rect;
        SDL_Texture* Image;
    };



    class Sprite {
    public:
        Sprite() {}
        void SetFrame(int index);
        int NextFrame();
        int PrevFrame();

    private:
        std::vector<Quad> Frames;
    };
}