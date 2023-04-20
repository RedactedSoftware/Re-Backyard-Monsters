#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
enum { PLAYER = 0, TOWNHALL = 1, TWIGSNAPPER = 2, PEBBLESHINER = 3};
struct entity {
    int type;
    bool isLocalPlayer;
    bool draw;
    int posX, posY, width, height, velocityX, velocityY;
    SDL_Rect renderedEntity;
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
}
