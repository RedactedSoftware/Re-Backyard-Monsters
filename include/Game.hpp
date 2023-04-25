#pragma once

#include <SDL2/SDL.h>
#include <GameScene.hpp>
#include <entity.hpp>
#include <thread>
#include <iostream>

namespace ReBackyardMonsters
{

    class SDLGame {
    public:
        virtual void Initialize();
        virtual void Cleanup();
        virtual void Update(float delta);
        virtual void Render();

        // Starts Render & Gametic Threads
        void Run();
        void Gameloop();
        void RunFrame();

        bool Focused;
        bool Paused;

        Vector2 GetWindowSize();
        void SetWindowSize(int x, int y);
        void SetWindowSize(Vector2 const&v);

    protected:
        bool requestQuit;
        float frameDelta;
        float tickDelta;
        int frameCount;

        SDL_Event event;
        SDL_Renderer *renderer;
        SDL_Window *window;

    };

    Vector2 SDLGame::GetWindowSize() {
        int* x;
        int* y;
        SDL_GetWindowSize(window, x, y);
        return {*x, *y};
    }
    void SDLGame::SetWindowSize(int x, int y) {
        SDL_SetWindowSize(window, x, y);
    }
    void SDLGame::SetWindowSize(Vector2 const&v) {
        SDL_SetWindowSize(window, v.GetX(), v.GetY());
    }

    void SDLGame::Render() { }
    void SDLGame::Update(float delta) { }

	void SDLGame::handleEvents() {
		while (SDL_PollEvent(&event)) {
		    if (event.type == SDL_QUIT)
		        requestQuit = true;
		
		    if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		    	Focused = false;

			if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
				Focused = true;
		}
	}    

    void SDLGame::Run()
    {
        Gameloop();
    }

    void SDLGame::Gameloop() {
        while (!requestQuit) {
            RunFrame();
        }
    }

    void SDLGame::RunFrame()
    {
		this->handleEvents(); // Include this in timing?
        
        auto start = std::chrono::high_resolution_clock::now();

        this->Update(frameDelta);
        this->Render();

        // TODO: Refactor time tracking to seconds, so we can actually use it in Gametick() sanely
        if (!Focused)
            std::this_thread::sleep_for(std::chrono::microseconds((62500 - Globals::minimumFrameDelta)));
        auto stop = std::chrono::high_resolution_clock::now();

        frameDelta = std::chrono::duration_cast<std::chrono::microseconds>(start-stop).count();
        if (frameDelta < Globals::minimumFrameDelta && Focused)
            std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumFrameDelta - (int) frameDelta));
        frameCount++;
    }

    void SDLGame::Cleanup()  {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    void SDLGame::Initialize() {
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
    }

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


    void Game::Cleanup() {
        // Do cleanup here

        // Cleanup SDL stuff
        SDLGame::Cleanup();
    }

    void Game::Initialize() {
        SDLGame::Initialize();

        Scene = GameScene();
        //Scene.AddEntity( YardEntity());
        //Scene.AddEntity();

        Menu::storeMenuObject(MenuObject{false, BACKGROUND, 4, 0, 0, 64, 48});
        Texture::loadMedia();
        //Entity::storeEntityTextures();
    }

    void Game::Render() {
        SDLGame::Render();
    }

    void Game::Update(float delta)
    {
        SDLGame::Update(delta);
        if (Paused)
            return;
        // Add Game Logic Here
    }

}
