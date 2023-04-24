#pragma once

#include <SDL2/SDL.h>
#include <GameScene.hpp>
#include <entity.hpp>

namespace ReBackyardMonsters
{
    class Game {
    public:
        GameScene Scene;
        Game() {}
        ~Game() {}
        void Initialize();
        // Starts Render & Gametic Threads
        void Run();
        void Cleanup();

        bool Focused;

    protected:
    private:
        void RenderThread();
        void GametickThread();

        void Render();
        void Gametick(float delta);
        bool requestQuit;
        SDL_Event event;
        SDL_Renderer *renderer;
        SDL_Window *window;

        float frameDelta;
        int frameCount;
    };

    void Game::RenderThread()
    {
        while (!requestQuit)
        {
            // TODO: Why not handle these on the GameTick thread instead...
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)
                    requestQuit = true;

                if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                    Focused = false;

                if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                    Focused = true;
            }
            auto begin = std::chrono::high_resolution_clock::now();
            this->Render();
            if (!Focused)
                std::this_thread::sleep_for(std::chrono::microseconds((62500 - Globals::minimumFrameDelta)));
            auto end = std::chrono::high_resolution_clock::now();

            frameDelta = std::abs(std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count());
            if (frameDelta < Globals::minimumFrameDelta && Focused)
                std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumFrameDelta - (int) frameDelta));
            frameCount++;
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    void Game::GametickThread()
    {

    }

    void StartGameloop()
    {
        std::thread frameRendr
    }



    void Game::Initialize() {
        Scene = GameScene();
        Scene.AddEntity( YardEntity());
        Scene.AddEntity();
    }

    void Game::Render() {

    }

    void Game::Gametick(float delta)
    {

    }
}