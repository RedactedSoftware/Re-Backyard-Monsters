
#include <Game.hpp>

namespace ReBackyardMonsters
{
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
