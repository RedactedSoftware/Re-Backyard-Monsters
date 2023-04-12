#include <chrono>
#include <thread>
#include <iostream>
#include "globals.hpp"

void gameTick() {
    while (true) {
        if (!Globals::isPaused) {
            auto start = std::chrono::high_resolution_clock::now();
            //Do stuff.
            Globals::lineX1 = Globals::lineX1 + 2;
            Globals::lineX2 = Globals::lineX2 - 2;
            if (Globals::lineX1 > Globals::screenWidth) {
                Globals::lineX1 = 0;
                Globals::lineX2 = Globals::screenWidth;
            }

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