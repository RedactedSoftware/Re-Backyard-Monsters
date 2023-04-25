#pragma once

#include <SDL2/SDL.h>
#include <GameScene.hpp>
#include <entity.hpp>
#include <thread>
#include <iostream>

#include <SDLGame.h>

namespace ReBackyardMonsters
{
    // Actual Game Implementation
    // Keep "Engine-esque" stuff in SDLGame
    class Game: public SDLGame {
    public:
        GameScene Scene;
        Game() {}
        ~Game() {}


        void Initialize() override;
        void Cleanup() override;
        void Render() override;
        void Update(float delta) override;
    protected:
    private:
    };
   
}
