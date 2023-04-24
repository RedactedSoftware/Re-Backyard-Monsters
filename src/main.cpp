#include <gameTick.hpp>
#include <frameRender.hpp>

#include <Game.hpp>

int main() {
    auto* game = new ReBackyardMonsters::Game();
    // Initialization before the game loop
    game->Initialize();
    game->Run();
    game->Cleanup();
    delete game;
    return 0;

    //init code here

    //std::thread frameRenderThread (frameRender);
    //std::thread gameTickThread (gameTick);
    //Do stuff on main thread here
    //frameRenderThread.join();
    //gameTickThread.join();
    //return 0;
}