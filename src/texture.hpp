#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "globals.hpp"
#include "texture.hpp"
#include "renderer.hpp"
namespace Texture {
    inline SDL_Texture* loadTexture(std::string path) {
        //The final texture
        SDL_Texture* newTexture;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());

        //Create texture from surface.
        newTexture = SDL_CreateTextureFromSurface(Renderer::renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);

        return newTexture;
    }

    void loadMedia() {
        Entity::storeEntityTexture(loadTexture("../resources/missingTexture.png"), PEBBLESHINER);

    }

}
