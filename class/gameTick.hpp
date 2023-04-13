#include <chrono>
#include <thread>
#include <iostream>
#include "globals.hpp"
#include "keyInput.hpp"

void gameTick() {
    while (true) {
        if (!Globals::isPaused) {
            auto start = std::chrono::high_resolution_clock::now();
            //Do stuff.
            if(keyInput::isWDown)
                Globals::localPlayer.y = Globals::localPlayer.y -4;
            if(keyInput::isSDown)
                Globals::localPlayer.y = Globals::localPlayer.y +4;
            if(keyInput::isADown)
                Globals::localPlayer.x = Globals::localPlayer.x -4;
            if(keyInput::isDDown)
                Globals::localPlayer.x = Globals::localPlayer.x +4;

            if(Globals::localPlayer.y > Globals::screenHeight - Globals::localPlayer.h)
                Globals::localPlayer.y = Globals::screenHeight - Globals::localPlayer.h;
            if(Globals::localPlayer.y < 0)
                Globals::localPlayer.y = 0;
            if(Globals::localPlayer.x > Globals::screenWidth - Globals::localPlayer.w)
                Globals::localPlayer.x = Globals::screenWidth - Globals::localPlayer.w;
            if(Globals::localPlayer.x < 0)
                Globals::localPlayer.x = 0;
            if(SDL_HasIntersection(&Globals::localPlayer,&Globals::floor)) {
                Globals::localPlayer.y = Globals::floor.y - Globals::localPlayer.h;
            }
            if(!SDL_HasIntersection(&Globals::localPlayer,&Globals::floor))
                Globals::localPlayer.y = Globals::localPlayer.y +2;

            //execute once per second
            if (Globals::tickCount % 64 == 0) {
                std::cout << "Last tick completed in: " << (Globals::tickDelta / 1000) << "ms, " << "sleeping "
                << ((Globals::minimumTickDelta - Globals::tickDelta) / 1000) << "ms." << std::endl;
                    std::cout << "Last frame rendered in: " << (Globals::frameDelta / 1000) << "ms." << std::endl;
                    std::cout << Globals::frameCount << " frames have elapsed." << std::endl;
            }
            Globals::tickCount = Globals::tickCount + 1;
            auto stop = std::chrono::high_resolution_clock::now();

            //limit to 64 ticks per second.
            Globals::tickDelta = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
            if ((int) Globals::tickDelta < Globals::minimumTickDelta)
                std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumTickDelta - (int) Globals::tickDelta));
                //Pause without potential deSync issues.
        } else {std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumTickDelta)); Globals::tickCount = Globals::tickCount + 1;}
    }
}