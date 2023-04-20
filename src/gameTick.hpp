#include <chrono>
#include <thread>
#include <iostream>
#include "globals.hpp"
#include "inputHandler.hpp"
#include "entity.hpp"

void gameTick() {
    while (true) {
        //The first tick *must* be after the first frame has completed
        if (Globals::frameCount == 1)
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if (!Globals::isPaused) {
            entity localPlayer = Entity::getLocalPlayer();
            auto start = std::chrono::high_resolution_clock::now();
            //Do stuff.
            localPlayer.posX = InputHandler::getMousePosition()[0];
            localPlayer.posY = InputHandler::getMousePosition()[1];

            //keep player in bounds
            if(localPlayer.posY > Globals::screenHeight - localPlayer.height)
                localPlayer.posY = Globals::screenHeight - localPlayer.height;
            if(localPlayer.posY < 0)
                localPlayer.posY = 0;
            if(localPlayer.posX > Globals::screenWidth - localPlayer.width)
                localPlayer.posX = Globals::screenWidth - localPlayer.width;
            if(localPlayer.height < 0)
                localPlayer.height = 0;

            //if player collides with the floor.
            //TODO Check for collision myself to avoid having to use the rendered entity as it causes colliding entities to clip into each-other breifly.
            if(SDL_HasIntersection(&localPlayer.renderedEntity,&Globals::floor)) {
                localPlayer.posY = Globals::floor.y - localPlayer.height;
            }
            //gravity.
            if(!SDL_HasIntersection(&localPlayer.renderedEntity,&Globals::floor)) {
                localPlayer.posY = localPlayer.posY + 2;

            }

            //execute once per second
            if (Globals::tickCount % 64 == 0) {
                std::cout << "Last tick completed in: " << (Globals::tickDelta / 1000) << "ms, " << "sleeping "
                << ((Globals::minimumTickDelta - Globals::tickDelta) / 1000) << "ms." << std::endl;
                    std::cout << "Last frame rendered in: " << (Globals::frameDelta / 1000) << "ms." << std::endl;
                    std::cout << Globals::frameCount << " frames have elapsed." << std::endl;
            }

            //TODO assign this in the frameRender thread right before drawing so we can interpolate it.
            localPlayer.renderedEntity.x = localPlayer.posX;
            localPlayer.renderedEntity.y = localPlayer.posY;
            localPlayer.renderedEntity.w = localPlayer.width;
            localPlayer.renderedEntity.h = localPlayer.height;
            Entity::setLocalPlayer(localPlayer);
            Globals::tickCount = Globals::tickCount + 1;
            auto stop = std::chrono::high_resolution_clock::now();
            //limit to 64 ticks per second.
            if ((int) Globals::tickDelta < Globals::minimumTickDelta)
                std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumTickDelta - (int) Globals::tickDelta));
                //Pause without potential deSync issues.
            Globals::tickDelta = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        } else {std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumTickDelta)); Globals::tickCount = Globals::tickCount + 1;}
    }
}