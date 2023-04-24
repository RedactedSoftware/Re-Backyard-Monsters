#include <Game.hpp>

int main() {
    auto* game = new ReBackyardMonsters::Game();
    game->Initialize(); // Setup Content, Assets, Game Objects
    game->Run();        // Gameloop
    game->Cleanup();    // Unload and free memory
    delete game;
    return 0;
}