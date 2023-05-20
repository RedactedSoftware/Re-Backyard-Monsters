#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>
#include "globals.hpp"
#include "renderer.hpp"
#include "inputHandler.hpp"
#include "texture.hpp"

//entity types.
enum {ERRORENTITY = -247, PLAYER = 0, TOWNHALL = 1, TWIGSNAPPER = 2, PEBBLESHINER = 3, YARD = 4, SILO = 5};

//entity flags.
enum {SELECTED = 0, DRAW = 1, DOANIM = 2};
class entity {
public:
    int type;
    int entityID;
    int animState;
    int posX, posY, width, height;
    SDL_Rect renderedEntity;
    SDL_Texture* renderedTexture;
    std::vector<int> flags;
};
class building: public entity {
};


namespace Entity {
    inline std::vector<entity> entityList;
    inline entity ErrorEntity = {ERRORENTITY,ERRORENTITY,false};

    inline void storeEntity(entity e) {
        entityList.push_back(e);
    }

    //if flag is in entity flags.
    inline bool searchFlags(const entity &e, int FLAG) {
        if (std::find(e.flags.begin(),e.flags.end(),FLAG) != e.flags.end())
            return true;
        return false;
    }

    //set entity flag.
    inline void setFlag( entity &e, int FLAG) {
        e.flags.push_back(FLAG);
    }

    inline entity* getEntityByID(int id) {
        for (int i = 0; (size_t) i < entityList.size(); i++) {
            if (entityList[i].entityID == id)
                return &entityList[i];
        }
        return &ErrorEntity;
    }
    inline entity* getLocalPlayer() {
        for (int i = 0; (size_t) i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].type == PLAYER)
                return &entityList[i];
        }
        return &ErrorEntity;
    }
    inline bool compareByHeight(const entity &x, const entity &y)
    {
        return x.posY < y.posY;
    }

    //TODO This is a total hack.
    //Return the entity the player is intersecting with which has the lowest Y coordinate.
    inline entity* getEntityByIntersection() {
        std::vector<entity> intersectionVector;
        for (int i = 0; (size_t) i < entityList.size(); i++){
            if (SDL_HasIntersection(&Entity::getLocalPlayer()->renderedEntity, &entityList[i].renderedEntity) == SDL_TRUE) {
                if(!Entity::entityList[i].type == PLAYER) {
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
        for (int i = 0; (size_t) i < entityList.size(); i++){
            if (entityList[i].type == PLAYER && entityList[i].type == PLAYER)
                entityList[i] = e;
        }
    }

    inline void storeEntityTextures() {
        for (int i = 0; (size_t) i < Entity::entityList.size(); i++){
            if (Entity::entityList[i].type == PEBBLESHINER) {
                if (Entity::searchFlags(Entity::entityList[i], DOANIM)) {
                    entityList[i].animState++;
                    if (entityList[i].animState > Texture::pebbleShiner.size() -1)
                        entityList[i].animState = 0;
                    Entity::entityList[i].renderedTexture = Texture::pebbleShiner[entityList[i].animState];
                }
                if (!Entity::searchFlags(Entity::entityList[i], DOANIM)) {
                    entityList[i].animState = 1;
                    Entity::entityList[i].renderedTexture = Texture::pebbleShiner[entityList[i].animState];
                }
            }
            if(Entity::entityList[i].type == YARD)
                Entity::entityList[i].renderedTexture = Texture::grassTexture;
        }
    }

    //inline void setCollisionDelta() {
        //int width;
        //int height;
        //int delta;
        //for (int i = 0; (size_t) i < Entity::entityList.size(); i++){
            //SDL_QueryTexture(Entity::entityList[i].renderedTexture, NULL, NULL, &width, &height);
            //if (Entity::entityList[i].draw && Entity::entityList[i].renderedEntity.h < height) {
                //delta = (Entity::entityList[i].renderedEntity.h - height);
                //std::cout << delta << std::endl;
            //}
        //}
    //}

    //Render entities in order Y position.
    inline void renderEntities() {
    //setCollisionDelta();
        //Savant genius render the boxes used for collision *under* the grass LOL.
        std::sort(Entity::entityList.begin(), Entity::entityList.end(), compareByHeight);
        for (int i = 0; (size_t) i < Entity::entityList.size(); i++){
            if(Entity::searchFlags(Entity::entityList[i], DRAW) && Entity::entityList[i].type != PLAYER && Entity::entityList[i].type != YARD) {
                SDL_RenderFillRect(Renderer::renderer, &Entity::entityList[i].renderedEntity);
            }
        }

        //Render the grass.
        for (int i = 0; (size_t) i < Entity::entityList.size(); i++){
            if (Entity::entityList[i].type == YARD) {
                SDL_RenderFillRect(Renderer::renderer, &Entity::entityList[i].renderedEntity);
                SDL_RenderCopy(Renderer::renderer, Entity::entityList[i].renderedTexture, NULL,
                               &Entity::entityList[i].renderedEntity);
            }
        }

        //Generic
        for (int i = 0; (size_t) i < Entity::entityList.size(); i++){
            if(Entity::searchFlags(Entity::entityList[i], DRAW) && !Entity::entityList[i].type == PLAYER && Entity::entityList[i].type != YARD) {
                    SDL_RenderCopy(Renderer::renderer, Entity::entityList[i].renderedTexture, NULL,
                                   &Entity::entityList[i].renderedEntity);

            }
            //Always render the localPlayer last for now.
            SDL_RenderFillRect(Renderer::renderer,&Entity::getLocalPlayer()->renderedEntity);
        }
    }
}
