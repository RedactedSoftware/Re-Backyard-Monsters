#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "globals.hpp"
#include "renderer.hpp"
enum { PLAYER = 0, TOWNHALL = 1, TWIGSNAPPER = 2, PEBBLESHINER = 3};
struct entity {
    int type;
    bool isLocalPlayer;
    bool entityID;
    bool draw;
    int posX, posY, width, height;
    SDL_Rect renderedEntity;
    SDL_Texture* renderedTexture;
};

namespace Entity {
    inline std::vector<entity> entityList;

    void storeEntity(entity e) {
        entityList.push_back(e);
    }
    entity getLocalPlayer() {
        for (int i = 0; i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].isLocalPlayer)
                return entityList[i];
        }
    }

    void setLocalPlayer(entity e) {
        for (int i = 0; i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].isLocalPlayer)
                entityList[i] = e;
        }
    }
    void storeEntityTexture(SDL_Texture* texture, int type) {
        for (int i = 0; i < Entity::entityList.size(); i++){
            if (Entity::entityList[i].type == type) {
                Entity::entityList[i].renderedTexture = texture;
            }
        }
    }

    inline void renderTexturedEntity(entity e) {
        SDL_RenderFillRect(Renderer::renderer,&e.renderedEntity);
        SDL_RenderCopy( Renderer::renderer, e.renderedTexture, NULL, &e.renderedEntity);
    }
}
