#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include "entity.hpp"
#include "texture.hpp"

void frameRender() {
    if (Globals::frameCount == 1) {
        //Placeholder load entities on first frame. Will eventually load the savegame here.
        Entity::storeEntity(entity{YARD,0,0,0,0,Globals::screenWidth,Globals::screenHeight,
                                   0,0,Globals::screenWidth,Globals::screenHeight});

        Entity::storeEntity(entity{PLAYER,1,0,0,0,4,4,0,0,4,4});

        Entity::storeEntity(entity{PEBBLESHINER,2,0,0,0,64,64,0,0,64,64});
        Entity::setFlag(*Entity::getEntityByID(2), DRAW);
        Entity::setFlag(*Entity::getEntityByID(2), DOANIM);

        //Menu::storeMenuObject(MenuObject{false,BACKGROUND,4,0,0,64,48});
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        Globals::window = SDL_CreateWindow("Re: Backyard Monsters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);
        SDL_SetWindowResizable(Globals::window,SDL_TRUE);
        if (Globals::window == nullptr) {
            std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
            std::cerr << "SDL_Error: " << "Couldn't init SDL_Image." << std::endl;
        Renderer::renderer = SDL_CreateRenderer(Globals::window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetLogicalSize(Renderer::renderer, 1152, 864);
        SDL_GL_SetSwapInterval(0);;
        SDL_UpdateWindowSurface(Globals::window);

        Texture::loadMedia();
        Entity::storeEntityTextures();
    }
    while (!Globals::shouldQuit) {
        while (SDL_PollEvent(&Globals::event)) {
            if (Globals::event.type == SDL_QUIT)
                Globals::shouldQuit = true;

            if (Globals::event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                Globals::isInFocus = false;

            if (Globals::event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                Globals::isInFocus = true;
            InputHandler::detectMouseDownEvent();
            InputHandler::detectMouseUpEvent();
        }
         auto start = std::chrono::high_resolution_clock::now();
        //do stuff.
        SDL_SetRenderDrawColor(Renderer::renderer,0,0,0,255);
        SDL_RenderClear(Renderer::renderer);
        SDL_SetRenderDrawColor(Renderer::renderer,255,255,255,255);
        Entity::renderEntities();

        SDL_RenderPresent(Renderer::renderer);
        //Decrease framerate when focus is lost.
        if(!Globals::isInFocus)
            std::this_thread::sleep_for(std::chrono::microseconds((62500 - Globals::minimumFrameDelta)));
        auto stop = std::chrono::high_resolution_clock::now();
        //limit framerate to 1000.
        Globals::frameDelta = abs(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
        if(Globals::frameDelta < Globals::minimumFrameDelta && Globals::isInFocus)
            std::this_thread::sleep_for(std::chrono::microseconds((Globals::minimumFrameDelta - (int) Globals::frameDelta)));
        Globals::frameCount = Globals::frameCount + 1;
    }
    SDL_DestroyRenderer(Renderer::renderer);
    SDL_DestroyWindow(Globals::window);
    SDL_Quit();
    exit(1);
}