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
        bool Paused;

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

    Vector2 Game::getWindowSize() {
        int* x;
        int* y;
        SDL_GetWindowSize(window, x, y);
        return {*x, *y};
    }
    void Game::setWindowSize(int x, int y) {
        SDL_SetWindowSize(window, x, y);
    }

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

        Menu::storeMenuObject(MenuObject{false, BACKGROUND, 4, 0, 0, 64, 48});


        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;


        window = SDL_CreateWindow("Re: Backyard Monsters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1152, 864, SDL_WINDOW_SHOWN);
        SDL_SetWindowResizable(window, SDL_TRUE);
        if (window == nullptr) {
            std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
            std::cerr << "SDL_Error: " << "Couldn't init SDL_Image." << std::endl;
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetLogicalSize(renderer, 1152, 864);
        SDL_GL_SetSwapInterval(0);
        SDL_UpdateWindowSurface(window);

        Texture::loadMedia();
        Entity::storeEntityTextures();
    }

    void Game::Render() {

    }

    void Game::Gametick(float delta)
    {
        if (Paused)
            return;
    }
}