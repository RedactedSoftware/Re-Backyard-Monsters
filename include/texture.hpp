#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "globals.hpp"
#include "renderer.hpp"
#include "menu.hpp"
namespace Texture {
    inline SDL_Texture* loadTexture(std::string path) {
        //The final texture
        SDL_Texture* newTexture;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        //SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,255,0,255));
        //Create texture from surface.
        newTexture = SDL_CreateTextureFromSurface(Renderer::renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);

        return newTexture;
    }

    inline std::vector<SDL_Texture*> pebbleShiner;
    inline SDL_Texture* grassTexture;

    void loadMedia() {
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/1.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/2.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/3.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/4.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/5.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/6.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/7.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/8.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/9.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/10.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/11.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/12.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/13.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/14.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/15.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/16.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/17.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/18.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/19.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/20.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/21.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/22.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/23.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/24.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/25.png"));
        pebbleShiner.push_back(loadTexture("../resources/pebbleShiner/26.png"));
        Texture::grassTexture = loadTexture("../resources/grassTexture.png");
        //Menu::storeMenuTexture(loadTexture("../resources/menuBackground.png"),BACKGROUND);

    }

}
