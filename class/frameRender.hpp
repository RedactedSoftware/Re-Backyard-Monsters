#include <chrono>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>
#include "globals.hpp"

SDL_Renderer* renderer = nullptr;
SDL_Surface* textureSurface = nullptr;

void frameRender() {
    if (Globals::frameCount == 1) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        Globals::window = SDL_CreateWindow("Experiment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);
        SDL_SetWindowResizable(Globals::window,SDL_TRUE);
        if (Globals::window == nullptr) {
            std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        renderer = SDL_CreateRenderer(Globals::window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetLogicalSize(renderer, 960, 540);
        SDL_GL_SetSwapInterval(0);;
        SDL_UpdateWindowSurface(Globals::window);
        textureSurface = SDL_LoadBMP("/home/william/Documents/GitHub/Experiment/resources/image.bmp");
        if (textureSurface == nullptr) {
            textureSurface = SDL_LoadBMP("/home/william/Documents/GitHub/Experiment/resources/missingTexture.bmp");
            std::cerr << "SDL_Error: " << "Could not load image.bmp" << std::endl;
            std::cout << textureSurface << std::endl;
        }

    }
    while (!Globals::shouldQuit) {
        while (SDL_PollEvent(&Globals::event)) {
            if (Globals::event.type == SDL_QUIT)
                Globals::shouldQuit = true;

            if (Globals::event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                Globals::isInFocus = false;

            if (Globals::event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                Globals::isInFocus = true;

            if (Globals::event.type == SDL_KEYDOWN) {
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    Globals::shouldQuit = true;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_INSERT)
                    Globals::isPaused = !Globals::isPaused;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_W)
                    Globals::isWDown = true;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_A)
                    Globals::isADown = true;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_S)
                    Globals::isSDown = true;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_D)
                    Globals::isDDown = true;
            }
            if (Globals::event.type == SDL_KEYUP) {
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_W)
                    Globals::isWDown = false;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_A)
                    Globals::isADown = false;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_S)
                    Globals::isSDown = false;
                if (Globals::event.key.keysym.scancode == SDL_SCANCODE_D)
                    Globals::isDDown = false;
            }
        }
         auto start = std::chrono::high_resolution_clock::now();
        //do stuff.
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawLine(renderer,Globals::lineX1,Globals::lineY1,Globals::lineX2,Globals::lineY2);
        SDL_RenderFillRect(renderer,&Globals::localPlayer);







        SDL_RenderPresent(renderer);
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(Globals::window);
    SDL_Quit();
    exit(1);
}