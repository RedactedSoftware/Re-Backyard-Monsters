#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>
#include "globals.hpp"
#include "renderer.hpp"
#include "inputHandler.hpp"

//entity types.
enum { PLAYER = 0, TOWNHALL = 1, TWIGSNAPPER = 2, PEBBLESHINER = 3, ERRORENTITY = -247};
struct entity {
    int type;
    bool isLocalPlayer;
    int entityID;
    bool draw;
    int posX, posY, width, height;
    SDL_Rect renderedEntity;
    SDL_Texture* renderedTexture;
};


namespace Entity {
    inline std::vector<entity> entityList;
    inline entity ErrorEntity = {ERRORENTITY,0,-247,false};

    inline void storeEntity(entity e) {
        entityList.push_back(e);
    }

    inline entity* getEntityByID(int id) {
        for (int i = 0; i < entityList.size(); i++) {
            if (entityList[i].entityID == id)
                return &entityList[i];
        }
    }
    inline entity* getLocalPlayer() {
        for (int i = 0; i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].isLocalPlayer)
                return &entityList[i];
        }
    }
    inline bool compareByHeight(const entity &x, const entity &y)
    {
        return x.posY < y.posY;
    }

    //TODO This is the biggest hack I've ever made.
    //Return the entity the player is intersecting with which has the lowest Y coordinate.
    inline entity* getEntityByIntersection() {
        std::vector<entity> intersectionVector;
        for (int i = 0; i < entityList.size(); i++){
            if (SDL_HasIntersection(&Entity::getLocalPlayer()->renderedEntity, &entityList[i].renderedEntity) == SDL_TRUE) {
                if(!Entity::entityList[i].isLocalPlayer) {
                    intersectionVector.push_back(Entity::entityList[i]);
                    std::sort(intersectionVector.begin(), intersectionVector.end(), compareByHeight);
                }
            }
        }
        if (intersectionVector.size() == 0)
            return &Entity::ErrorEntity;
        std::reverse(intersectionVector.begin(),intersectionVector.end());
        return Entity::getEntityByID(intersectionVector[0].entityID);
    }

    inline entity* getEntityByClick() {
        if (InputHandler::isMouse1Down) {
            return getEntityByIntersection();
        }
        return &Entity::ErrorEntity;
    }

    inline void setLocalPlayer(entity e) {
        for (int i = 0; i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].isLocalPlayer)
                entityList[i] = e;
        }
    }
    inline void storeEntityTexture(SDL_Texture* texture, int type) {
        for (int i = 0; i < Entity::entityList.size(); i++){
            if (Entity::entityList[i].type == type) {
                Entity::entityList[i].renderedTexture = texture;
            }
        }
    }

    //Render entities in order Y position.
    inline void renderEntities() {
        std::sort(Entity::entityList.begin(), Entity::entityList.end(), compareByHeight);
        for (int i = 0; i < Entity::entityList.size(); i++){
            if(Entity::entityList[i].draw && !Entity::entityList[i].isLocalPlayer) {
                SDL_RenderFillRect(Renderer::renderer, &Entity::entityList[i].renderedEntity);
                    SDL_RenderCopy(Renderer::renderer, Entity::entityList[i].renderedTexture, NULL,
                                   &Entity::entityList[i].renderedEntity);

            }
            //Always render the localPlayer last.
            SDL_RenderFillRect(Renderer::renderer,&Entity::getLocalPlayer()->renderedEntity);
            SDL_RenderCopy(Renderer::renderer, Entity::getLocalPlayer()->renderedTexture, NULL,
                           &Entity::getLocalPlayer()->renderedEntity);

        }
    }
}
